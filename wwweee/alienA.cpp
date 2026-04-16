#include "alienA.h"
#include <raylib.h>


Texture2D alienA::alienAImages[3] = {};

alienA::alienA(int edge, int type, Vector2 position, Vector2 velocity)
    : Alien(edge,type,position,velocity) {
    if (alienAImages[edge - 1].id == 0) {

        switch (edge) {
        case 1:
            alienAImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        case 2:
            alienAImages[1] = LoadTexture("Graphics/alien_1.2.png");
            break;
        case 3:
            alienAImages[2] = LoadTexture("Graphics/alien_1.1.png");
            break;
        default:
            alienAImages[0] = LoadTexture("Graphics/alien_1.png");
            break;
        }
    }
}

void alienA::Update() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void alienA::Draw() {
    DrawTextureV(alienAImages[edge - 1], position, WHITE);

}

void alienA::LoadImages() {
    alienAImages[0] = LoadTexture("Graphics/alien_1.png");
    alienAImages[1] = LoadTexture("Graphics/alien_1.2.png");
    alienAImages[2] = LoadTexture("Graphics/alien_1.1.png");
}

void alienA::UnloadImages() {
    for (int i = 0; i < 3; ++i) {
        if (alienAImages[i].id != 0)
            UnloadTexture(alienAImages[i]);
    }
}

Rectangle alienA::getRect() const {
    return { position.x, position.y,
                 float(alienAImages[edge - 1].width),
                 float(alienAImages[edge - 1].height) };
}

bool alienA::IsOffScreen() const {
    return (position.y > GetScreenHeight() - alienAImages[edge - 1].height || position.x < -50 || position.x > GetScreenWidth() + 50);
}

Texture2D& alienA::GetImage(int edge) {
    return alienAImages[edge - 1];
}