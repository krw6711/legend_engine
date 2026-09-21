#include "audio.h"
#include "SDL3/SDL_audio.h"
#include "SDL3/SDL_stdinc.h"

int init_stearms(){

    /* Create our audio stream in the same format as the .wav file. It'll convert to what the audio hardware wants. */
    music = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wav_data[0].spec, NULL, NULL);
    if (!music) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return 1;
    }

    sfx = SDL_OpenAudioDeviceStream(SDL_AUDIO_DEVICE_DEFAULT_PLAYBACK, &wav_data[1].spec, NULL, NULL);
    if (!sfx) {
        SDL_Log("Couldn't create audio stream: %s", SDL_GetError());
        return 1;
    }

    /* SDL_OpenAudioDeviceStream starts the device paused. You have to tell it to start! */
    SDL_ResumeAudioStreamDevice(music);
    SDL_ResumeAudioStreamDevice(sfx);

    return 0;
}

int init_audio_files()
{
    char *paths[32] = {
        "assets/music.wav", 
        "assets/sfx/equip.wav", 
        "assets/sfx/inventory.wav", 
        "assets/sfx/select.wav"
    };

    wav_data = SDL_calloc(4, sizeof(Wav_file_t));

    if(!wav_data) return 1;

    for (int i = 0; i < 4; i++)
    {
        char *wav_path = get_full_path(paths[i]);

        /* Load the .wav file from wherever the app is being run from. */
        bool load = SDL_LoadWAV(wav_path, &wav_data[i].spec, &wav_data[i].wav_data, &wav_data[i].wav_data_len);
        SDL_free(wav_path);  /* done with this string. */
        if (!load) {
            SDL_Log("Couldn't load %s: %s", paths[i], SDL_GetError());
            return 1;
        }
    }

    return 0;
}

void cleanup_audio()
{
    for(int i = 0; i < 4; i++){
        SDL_free(wav_data[i].wav_data);
    }
    SDL_free(wav_data);
    wav_data = NULL;

    if(music) SDL_DestroyAudioStream(music);
    music = NULL;
    if(sfx) SDL_DestroyAudioStream(sfx);
    sfx = NULL;

}

void play_music(int id)
{
    if (SDL_GetAudioStreamQueued(music) < (int)wav_data[id].wav_data_len) {
        /* feed more data to the stream. It will queue at the end, and trickle out as the hardware needs more data. */
        // SDL_SetAudioStreamFormat(music, &wav_data[id].spec, NULL);
        SDL_PutAudioStreamData(music, wav_data[id].wav_data, wav_data[id].wav_data_len);
    }
}

void stop_music()    
{
    SDL_ClearAudioStream(music);
}

void play_sfx(int id)
{
    SDL_ClearAudioStream(sfx);
    SDL_SetAudioStreamFormat(sfx, &wav_data[id].spec, NULL);
    SDL_PutAudioStreamData(sfx, wav_data[id].wav_data, wav_data[id].wav_data_len);

}