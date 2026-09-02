#include "velocity.h"
#include "../entities/entity.h"
#include "SDL3/SDL_log.h"
#include "SDL3/SDL_stdinc.h"

float calc_new_distance(float velocity, float *last_time) {
  float now = (float)SDL_GetTicks() / 1000;
  float delta_time = now - *last_time;

  *last_time = now;

  return velocity * (float)delta_time;
}

void start_moving(Player_t *object, Coordinates_t new_coord) {
    if(!object->move.moving){
        object->move.moving = true;
        object->move.passed = 0;
        object->move.last_time = (float)SDL_GetTicks() / 1000;
        
        object->move.new_x = new_coord.x;
        object->move.new_y = new_coord.y;
        object->sprite.coordinates.x = 0;
    }
}

void stop_moving(Player_t *object)
{
    if(object->move.moving){
        object->move.moving = false;
        object->move.passed = 0;
        object->move.last_time = 0;

        object->x = object->move.new_x;
        object->y = object->move.new_y;

        object->tile = (SDL_FRect){ 
            object->x * MAP_CELL_SIZE,
            object->y * MAP_CELL_SIZE,
            MAP_CELL_SIZE,
            MAP_CELL_SIZE    
        };

        object->move.new_x = 0;
        object->move.new_y = 0;
        object->sprite.coordinates.x = 0;
    }
}

void update_sprite(Player_t *object)
{
    if(object->move.moving)
    {
        object->sprite.coordinates.x = ((int)(SDL_GetTicks()/100) % (int)object->sprite.count) * MAP_SPRITE_SIZE;
        // SDL_Log("new sprite x %f", object->sprite.coordinates.x);
    }
}

void move(Player_t *object) {
    if(player->move.moving){
        float delta_distance = calc_new_distance(MAP_CELL_SIZE*2, &player->move.last_time);
    
        if(player->move.passed + delta_distance >= MAP_CELL_SIZE)
        {
            delta_distance = MAP_CELL_SIZE - player->move.passed;
        }
        player->move.passed += delta_distance;
        switch(player->face){
            case UP:
                player->tile.y -= delta_distance; break;
            case DOWN:
                player->tile.y += delta_distance; break;
            case RIGHT:
                player->tile.x += delta_distance; break;
            case LEFT:
                player->tile.x -= delta_distance; break;
            case NONE: break;
        }
        update_sprite(player);
        if(player->move.passed >= MAP_CELL_SIZE)
        {
            stop_moving(object);
        }
    }
}