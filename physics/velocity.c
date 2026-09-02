#include "velocity.h"
#include "../entities/entity.h"

float calc_new_distance(float velocity, float *last_time) {
  float now = (float)SDL_GetTicks() / 1000;
  float delta_time = now - *last_time;

  *last_time = now;

  return velocity * (float)delta_time;
}

void start_moving(Player_t *object, float velocity, float delta_distance) {
  if (!object->move.moving) {
    object->move.moving = true;
    object->move.velocity = velocity;
    object->move.last_time = (float)SDL_GetTicks() / 1000;
    switch (object->face) {
    case UP:
      object->move.target = object->tile.y - delta_distance;
      break;
    case DOWN:
      object->move.target = object->tile.y + delta_distance;
      break;
    case RIGHT:
      object->move.target = object->tile.x + delta_distance;
      break;
    case LEFT:
      object->move.target = object->tile.x - delta_distance;
      break;
    case NONE:
      break;
    }
  }
}

void stop_moving(Player_t *object) {
  object->move.last_time = 0;
  object->move.moving = false;
  object->move.target = 0;
  object->move.velocity = 0;

  object->tile = (SDL_FRect){ 
    player->x * MAP_CELL_SIZE,
    player->y * MAP_CELL_SIZE,
    MAP_CELL_SIZE,
    MAP_CELL_SIZE    
  };
}

void move(Player_t *object) {
  if (object->move.moving) {
    float delta_distance = calc_new_distance(object->move.velocity, &object->move.last_time);
    switch (object->face) {
        case UP:
            if ((object->tile.y - delta_distance) > object->move.target) {
                object->tile.y = object->move.target;
                stop_moving(object);
            } else {
                object->tile.y -= delta_distance;
            }
            break;
        case DOWN:
            if ((object->tile.y + delta_distance) > object->move.target) {
                object->tile.y = object->move.target;
                stop_moving(object);
            } else {
                object->tile.y += delta_distance;
            }
            break;
        case RIGHT:
            if ((object->tile.x + delta_distance) > object->move.target) {
                object->tile.x = object->move.target;
                stop_moving(object);
            } else {
                object->tile.x += delta_distance;
            }
            break;
        case LEFT:
            if ((object->tile.x - delta_distance) > object->move.target) {
                object->tile.x = object->move.target;
                stop_moving(object);
            } else {
                object->tile.x -= delta_distance;
            }
            break;
        case NONE:
        break;
    }
  }
}