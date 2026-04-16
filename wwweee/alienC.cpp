#include "alienC.h"
#include <raylib.h>

Texture2D alienC::alienCImages[3] = {};

alienC::alienC(int edge, int type, Vector2 position, Vector2 velocity)
    : Alien(edge, type, position, velocity) {
    if (alienCImages[edge - 1].id == 0) {

        switch (edge) {
        case 1:
            alienCImages[0] = LoadTexture("Graphics/alien_3.png");
            break;
        case 2:
            alienCImages[1] = LoadTexture("Graphics/alien_3.2.png");
            break;
        case 3:
            alienCImages[2] = LoadTexture("Graphics/alien_3.1.png");
            break;
        default:
            alienCImages[0] = LoadTexture("Graphics/alien_3.png");
            break;
        }
    }
}

void alienC::Update() {
    position.x += velocity.x;
    position.y += velocity.y;
}

void alienC::Draw() {
    DrawTextureV(alienCImages[edge - 1], position, WHITE);

}

void alienC::LoadImages() {
    alienCImages[0] = LoadTexture("Graphics/alien_3.png");
    alienCImages[1] = LoadTexture("Graphics/alien_3.2.png");
    alienCImages[2] = LoadTexture("Graphics/alien_3.1.png");
}

void alienC::UnloadImages() {
    for (int i = 0; i < 3; ++i) {
        if (alienCImages[i].id != 0)
            UnloadTexture(alienCImages[i]);
    }
}
Rectangle alienC::getRect() const {
    return { position.x, position.y,
                 float(alienCImages[edge - 1].width),
                 float(alienCImages[edge - 1].height) };
}
bool alienC::IsOffScreen() const {
    return (position.y > GetScreenHeight() - alienCImages[edge - 1].height  || position.x < -50 || position.x > GetScreenWidth() + 50);
}

Texture2D& alienC::GetImage(int edge) {
    return alienCImages[edge - 1];
}