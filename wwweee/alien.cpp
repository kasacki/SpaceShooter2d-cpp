#include "alien.h"
#include <raylib.h>


Texture2D Alien::alienImages[3] = {};



Alien::Alien(int edge, int type, Vector2 position, Vector2 velocity)
    : edge(edge), type(type), position(position), velocity(velocity) {}





