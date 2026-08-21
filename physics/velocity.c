#include "velocity.h"

float calc_new_distance(float velocity, Uint64 *last_time) {
  Uint64 now = SDL_GetTicks() / 1000;
  Uint64 delta_time = now - *last_time;

  *last_time = now;

  return velocity * (float) delta_time;
}

void start_moving(Object_t *object, float velocity, float delta_distance, Face_t face)
{
    if(!object->move.moving){
        object->move.moving = true;
        switch (face) {
            case UP:
                object->move.target = object->y + delta_distance; break; 
            case DOWN:
                object->move.target = object->y - delta_distance; break; 
            case RIGHT:
                object->move.target = object->x + delta_distance; break;
            case LEFT:
                object->move.target = object->x - delta_distance; break;
        }
        object->move.velocity = velocity;
        object->move.face = face;
        object->move.last_time = SDL_GetTicks() / 1000;
    }
}

void stop_moving(Object_t *object)
{
    object->move.last_time = 0;
    object->move.moving = false;
    object->move.target = 0;
    object->move.velocity = 0;
}

void move(Object_t *object) {
    if (object->move.moving) {
        float delta_distance = calc_new_distance(object->move.velocity, &object->move.last_time);

        switch (object->move.face) {
            case UP:
                if((object->y + delta_distance) > object->move.target){
                    object->y = object->move.target;
                    stop_moving(object);
                }else{
                    object->y += delta_distance;
                }
                break;
            case DOWN:
                if((object->y - delta_distance) > object->move.target){             
                    object->y = object->move.target;
                    stop_moving(object);
                }else{
                    object->y -= delta_distance;
                }
                break;
            case RIGHT:
                if((object->x + delta_distance) > object->move.target){                    
                    object->x = object->move.target;
                    stop_moving(object);
                }else{
                    object->x += delta_distance;
                }
                break;
            case LEFT:
                if((object->x - delta_distance) > object->move.target){
                    object->x = object->move.target;
                    stop_moving(object);
                }else{
                    object->x -= delta_distance;
                }
                break;
        }
    }
}