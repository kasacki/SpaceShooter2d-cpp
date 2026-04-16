#include "laser.h"
#include "alien.h"
#include <raylib.h>

Laser::Laser(Vector2 position, Vector2 velocity)
{
    this->position = position;
    this->velocity = velocity;
    active = true;
}

void Laser::Draw() {
    if (active) {
        if (abs(velocity.y) > 0) {
            // Laser pionowy (gracz lub alien z góry)
            DrawRectangle(position.x, position.y, 4, 15, { 255, 20, 20, 255 });
        }
        else if (abs(velocity.x) > 0) {
            // Laser poziomy (alien z lewej/prawej)
            DrawRectangle(position.x, position.y, 15, 4, { 255, 20, 20, 255 });
        }
    }
}

Rectangle Laser::getRect()
{
    if (abs(velocity.y) > 0) {
        // Laser pionowy
        return { position.x, position.y, 4, 15 };
    }
    else {
        // Laser poziomy
        return { position.x, position.y, 15, 4 };
    }
}


void Laser::Update() {
    if (!active) return;

    position.x += velocity.x;
    position.y += velocity.y;

    // Dezaktywacja gdy laser opuœci ekran
    if (position.x < -10 || position.x > GetScreenWidth() + 10 ||
        position.y < -20 || position.y > GetScreenHeight() -110) {
        active = false;
    }
}