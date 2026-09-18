# Legend Engine
A lightweight Engine made using [C](https://en.wikipedia.org/wiki/C_(programming_language)) and [SDL3](https://wiki.libsdl.org/SDL3/FrontPage). This Engine made for [RPG Games](https://en.wikipedia.org/wiki/Role-playing_game) and [Action Adventure](https://en.wikipedia.org/wiki/Action-adventure_game) later with [Tile Map style](https://en.wikipedia.org/wiki/Tile-based_video_game) and [Turn based fights](https://en.wikipedia.org/wiki/Turn-based_role-playing_game). This Game  Engine inspired by **Nintendo's Classic Library** like [The Legend of Zelda](https://en.wikipedia.org/wiki/The_Legend_of_Zelda), [Pokemon](https://en.wikipedia.org/wiki/Pok%C3%A9mon) and [Final Fantsy I](https://en.wikipedia.org/wiki/Pok%C3%A9mon)

This Engine Relay on Data-Driven Approche, the engine is a binary files to read the assets, but the info of the game wont be just json, this json will be parsed into a "format". this way will make the loading quick and might be hard for modding, unless you know how the parser is working :)

**To learn more about the Engine you can read the [Documentation](./docs/readme.md)**

Do not forget to join our discord server! https://discord.gg/gXJZXGCbX

## Components
- **Game Engine**: the core of the game.
- **Game Editor**: design the game and assits.
- **Parser**: convert *JSON* files from the **Game Editor** into *binary files* that **Game Engine** can read. 

## How to build
- Install dependencies: 
    - C Compiler (GCC, Clang, MSVC)
    - CMake
    - Git
    - Build Essentials (make, ninja, etc...)
- clone this project and run cmake in the repo's directory
```sh
cmake -S . -B build && cmake --build build
```
- you can find the build in `build/Debug/main`

## resources
- map srpitesheet: I really forgot where I got them but I appreciat these artists work, they did really greate! I pulled them from itcho.io and another one I can not remember XD

## Licensing & Assets
* **Engine License:** The engine source code is licensed under the **GNU General Public License v3.0 (GPL-3.0)**. Any modifications to the engine code must remain open-source under GPL-3.0.
* **Game Assets & Ownership:** Games, textures, audio, and custom game logic created using this engine are the **sole property of their respective creators**. Using this engine to create games does not force your game assets to be open-source.

## Contributions
By submitting this PR, you agree that your contribution is licensed under GPL-3.0 and that you are the original author (or properly declaring AI assistance if used).

## Dependancies
- SDL3
- SDL3_ttf