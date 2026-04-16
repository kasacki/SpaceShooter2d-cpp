#include "mysteryship.h"
#include "laser.h"
#include <raylib.h>

MysteryShip::MysteryShip()
{
    laserSound = LoadSound("Sounds/laser.ogg");
    image = LoadTexture("Graphics/mystery.png");
    alive = false;

}

MysteryShip::~MysteryShip() {
    UnloadTexture(image);
}

void MysteryShip::Spawn() {
    position.y = 90;
    int side = GetRandomValue(0, 1);

    if (side == 0) {
        position.x = 25;
        speed = 3;
    }
    else {
        position.x = GetScreenWidth() - image.width - 25;
        speed = -3;
    }
    alive = true;
}

Rectangle MysteryShip::getRect()
{
    if (alive) {
        return { position.x, position.y, float(image.width), float(image.height) };
    }
    else {
        return { position.x, position.y, 0, 0 };
    }
}

void MysteryShip::Update() {
    if (alive) {
        position.x += speed;
        if (position.x > GetScreenWidth() - image.width - 25 || position.x < 25) {
            alive = false;
        }
    }
}

void MysteryShip::Draw() {
    if (alive) {
        DrawTextureV(image, position, WHITE);
    }
}

void MysteryShip::FireLasers() {
    if (alive && GetTime() - lastFireTime >= 0.5) { // strza³ co 1 sekunda
        // Laser z lewego skrzyd³a
        Vector2 leftWing = { position.x + 5, position.y + image.height };
        // Laser z prawego skrzyd³a
        Vector2 rightWing = { position.x + image.width - 9, position.y + image.height };

        Vector2 laserDirection = { 0, 9 };

        mlasers.push_back(Laser(leftWing, laserDirection)); 
        PlaySound(laserSound);
        mlasers.push_back(Laser(rightWing, laserDirection)); 
        PlaySound(laserSound);
        lastFireTime = GetTime();



        
    }
}