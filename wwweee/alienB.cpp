#include "alienB.h"
#include <raylib.h>


Texture2D alienB::alienBImages[3] = {};

alienB::alienB(int edge, int type, Vector2 position, Vector2 velocity)
    : Alien(edge, type, position, velocity) {
    if (alienBImages[edge - 1].id == 0) {

        switch (edge) {
        case 1:
            alienBImages[0] = LoadTexture("Graphics/alien_2.png");
            break;
        case 2:
            alienBImages[1] = LoadTexture("Graphics/alien_2.2.png");
            break;
        case 3:
            alienBImages[2] = LoadTexture("Graphics/alien_2.1.png");
            break;
        default:
            alienBImages[0] = LoadTexture("Graphics/alien_2.png");
            break;
        }
    }
}

void alienB::Update() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void alienB::Draw() {
    DrawTextureV(alienBImages[edge - 1], position, WHITE);

}

void alienB::LoadImages() {
    alienBImages[0] = LoadTexture("Graphics/alien_2.png");
    alienBImages[1] = LoadTexture("Graphics/alien_2.2.png");
    alienBImages[2] = LoadTexture("Graphics/alien_2.1.png");
}

void alienB::UnloadImages() {
    for (int i = 0; i < 3; ++i) {
        if (alienBImages[i].id != 0)
            UnloadTexture(alienBImages[i]);
    }
}

Rectangle alienB::getRect() const {
    return { position.x, position.y,
                 float(alienBImages[edge - 1].width),
                 float(alienBImages[edge - 1].height) };
}

bool alienB::IsOffScreen() const {
    return (position.y > GetScreenHeight() - alienBImages[edge - 1].height || position.x < -50 || position.x > GetScreenWidth() + 50);
}

Texture2D& alienB::GetImage(int edge) {
    return alienBImages[edge - 1];
}