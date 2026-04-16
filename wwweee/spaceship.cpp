#include "spaceship.h"
#include <raylib.h>

Spaceship::Spaceship()
{
    image = LoadTexture("Graphics/spaceship.png");
    position.x = (GetScreenWidth() - image.width) / 2;
    position.y = GetScreenHeight() - image.height - 100;
 
    lastFireTime = 0.0;
    laserSound = LoadSound("Sounds/laser.ogg");
}

Spaceship::~Spaceship() {
    UnloadTexture(image);
    UnloadSound(laserSound);
}


void Spaceship::MoveLeft() {
    image = LoadTexture("Graphics/spaceship2.png");
    movementDirection = { -1, 0 };
    position.x -= 7;
    if (position.x < 25) {
        position.x = 25;
    }
}

void Spaceship::MoveRight() {
    image = LoadTexture("Graphics/spaceship3.png");
    movementDirection = { 1, 0 };
    position.x += 7;
    if (position.x > GetScreenWidth() - image.width - 25) {
        position.x = GetScreenWidth() - image.width - 25;
    }
}
void Spaceship::MoveUp() {
    image = LoadTexture("Graphics/spaceship.png");
    movementDirection = { 0, -1 };
    position.y -= 7;
    if (position.y < 25) {
        position.y = 25;
    }
}

void Spaceship::MoveDown() {
    image = LoadTexture("Graphics/spaceship1.png");
    movementDirection = { 0, 1 };
    position.y += 7;
    if (position.y > GetScreenHeight() - image.height - 100) {
        position.y = GetScreenHeight() - image.height - 100;
    }
}
void Spaceship::FireLaser()
{
    if (GetTime() - lastFireTime >= 0.35) {

        // domyslnie z dolu w gore
        Vector2 direction;
        if (movementDirection.x == 0 && movementDirection.y == 0)
            direction = { 0, -1 };  // idŸ do góry
        else
            direction = movementDirection;  // idŸ tam, gdzie wskazuje ruch

        Vector2 laserVel = { direction.x * 9, direction.y * 9 };

        Vector2 laserPos = {
            position.x + image.width / 2 - 2,
            position.y
        };
        if (direction.x > 0) {
            laserPos = {
               position.x + 2  +image.width ,
               position.y + image.height / 2 };
            laserVel = { 9, 0 };
        }   // z lewej w prawo
        else if (direction.x < 0) {
            laserPos = {
               position.x - 40 + image.width / 2,
               position.y + image.height / 2 };
            laserVel = { -9, 0 };
        } // z prawej w lewo
        else if(direction.y>0){
            laserPos = {
               position.x + image.width / 2,
               position.y + 40 + image.height / 2 };
            laserVel = { 0, 9 };
        }   // z gory w dol
        else if (direction.y < 0) {
            laserPos = {
               position.x + image.width / 2,
               position.y - 40 + image.height / 2 };
            laserVel = { 0, -9 };

        }   // z dolu w gore i domyslnie
        lasers.push_back(Laser(laserPos, laserVel));
        lastFireTime = GetTime();
        PlaySound(laserSound);
        }
}


Rectangle Spaceship::getRect()
{
    return { position.x, position.y, float(image.width), float(image.height) };
}

void Spaceship::Reset()
{
    position.x = (GetScreenWidth() - image.width) / 2.0f;
    position.y = GetScreenHeight() - image.height - 100;
    MoveUp();
    lasers.clear();
}