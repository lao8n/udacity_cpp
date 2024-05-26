#include "sdl.h"

bool operator <(const SDL_Point& lhs, const SDL_Point& rhs){
    if (lhs.x == rhs.x){
        return lhs.y < rhs.y;
    }
    return lhs.x < rhs.x;
}