#include "game.h"
#include <raylib.h>
#include <array>
#include <thread>
#include <mutex>
#include <queue>
#include <chrono>
#include <vector>
#include <regex>
#include <filesystem>
#include <functional>
#include "alien.h"
#include "alienA.h"
#include "spaceship.h"
#include "obstacle.h"
#include "mysteryship.h"

//CONCEPT//
template <AlienLike AlienType>
void Game::AlienShootLaserFrom(std::vector<AlienType>& aliens, double& timeLastShot, std::vector<Laser>& laserList, double interval)
{
    double currentTime = GetTime();
    if (currentTime - timeLastShot >= interval && !aliens.empty()) {
        int randomIndex = GetRandomValue(0, aliens.size() - 1);
        AlienType& alien = aliens[randomIndex];

        const Texture2D& texture = AlienType::GetImage(alien.edge);  

        Vector2 laserPos = {
            alien.position.x + texture.width / 2,
            alien.position.y + 15 + texture.height / 2
        };

        Vector2 laserVel = { 0, 9 };

        if (alien.velocity.x > 0) {
            laserPos = {
                alien.position.x + 15 + texture.width / 2,
                alien.position.y + texture.height / 2
            };
            laserVel = { 9, 0 };
        }
        else if (alien.velocity.x < 0) {
            laserPos = {
                alien.position.x - 30 + texture.width / 2,
                alien.position.y + texture.height / 2
            };
            laserVel = { -9, 0 };
        }

        laserList.push_back(Laser(laserPos, laserVel));
        timeLastShot = currentTime;
        PlaySound(laserSound);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//
/*

CONCEPT
RANGES

*/
template <AlienLike AlienType>
void Game::HandleAlienObstacleCollision(std::vector<AlienType>& aliens)
{
    for (auto alienIt = aliens.begin(); alienIt != aliens.end(); ) {
        bool collided = false;

        for (auto& obstacle : obstacles) {
            //RANGES
            auto blockIt = std::ranges::find_if(obstacle.blocks, [&](auto& block) {
                return CheckCollisionRecs(block.getRect(), alienIt->getRect());
                });

            if (blockIt != obstacle.blocks.end()) {
                PlaySound(explosionSound);
                obstacle.blocks.erase(blockIt);
                alienIt = aliens.erase(alienIt);
                collided = true;
                break;
            }
        }

        if (!collided)
            ++alienIt;
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

//CONCEPT//
template<AlienLike AlienType>
void Game::SpawnAlien(std::vector<AlienType>& container)
{
    int edge = GetRandomValue(1, 3);
    int type = GetRandomValue(1, 3);
    Vector2 position, velocity;

    if (edge == 1) {
        position = { float(GetRandomValue(0, GetScreenWidth() - 50)), -50 };
        velocity = { 0, float(GetRandomValue(1, 3)) };
    }
    else if (edge == 2) {
        position = { -50, float(GetRandomValue(100, GetScreenHeight() - 150)) };
        velocity = { float(GetRandomValue(1, 3)), 0 };
    }
    else if (edge == 3) {
        position = { float(GetScreenWidth() + 50), float(GetRandomValue(100, GetScreenHeight() - 150)) };
        velocity = { float(-GetRandomValue(1, 3)), 0 };
    }

    container.emplace_back(edge, type, position, velocity);
}

//---------------------------------------------------------------------------------------------------------------------------------//

Game::Game()
{
    music = LoadMusicStream("Sounds/music.ogg");
    explosionSound = LoadSound("Sounds/explosion.ogg");
    laserSound = LoadSound("Sounds/laser.ogg");
    PlayMusicStream(music);
    SetMusicVolume(music, 0.15f);
    InitGame();
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::HandleInput() {
    if (run) {
        if (IsKeyDown(KEY_A)) {
            spaceship.MoveLeft();
        }
        if (IsKeyDown(KEY_D)) {
            spaceship.MoveRight();
        }
        if (IsKeyDown(KEY_W)) {
            spaceship.MoveUp();
        }
        if (IsKeyDown(KEY_S)) {
            spaceship.MoveDown();
        }
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
            spaceship.FireLaser();
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::Update() {
   
    if (run) {

        double currentTime = GetTime();
        if (currentTime - timeLastSpawn > mysteryShipSpawnInterval and score>1000) {
            mysteryship.Spawn();
            timeLastSpawn = GetTime();
            mysteryShipSpawnInterval = GetRandomValue(10, 20);
        }

        for (auto& laser : spaceship.lasers) {
            laser.Update();
        }
        for (auto& laser : mysteryship.mlasers) {
            laser.Update();
        }

        if (currentTime - alienSpawnTimer >= alienSpawnInterval) {
         

            switch (randomType) {
            case 0:
                SpawnAlien(aliensA);
                randomType = 1;
                break;
            case 1:
                SpawnAlien(aliensB);
                randomType = 2;
                break;
            case 2:
                SpawnAlien(aliensC);
                randomType = 0;
                break;

            }
           

            alienSpawnTimer = currentTime;
        }

       
        for (auto& aliena : aliensA) {
            aliena.Update();
        }
        for (auto& alienb : aliensB) {
            alienb.Update();
        }
        for (auto& alienc : aliensC) {
            alienc.Update();
        }
        DeleteOffScreenAliens();

        AlienShootLaserFrom(aliensA, timeLastAlienFiredA, alienLasers, alienLaserShootInterval);
        AlienShootLaserFrom(aliensB, timeLastAlienFiredB, alienLasers, alienLaserShootInterval);
        AlienShootLaserFrom(aliensC, timeLastAlienFiredC, alienLasers, alienLaserShootInterval);


        for (auto& laser : alienLasers) {
            laser.Update();
        }

        DeleteInactiveLasers();

        mysteryship.Update();

        mysteryship.FireLasers();
        

        CheckForCollisions();
    }
    else {
        if (IsKeyDown(KEY_ENTER)) {
            Reset();
            InitGame();
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

Game::~Game() {
   
    alienA::UnloadImages();
    alienB::UnloadImages();
    alienC::UnloadImages();
    UnloadMusicStream(music);
    UnloadSound(explosionSound);
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::Draw() {
    //poolaczony wektor wskaznikow 
    std::vector<Alien*> allAliens;
    allAliens.reserve(aliensA.size() + aliensB.size() + aliensC.size());

    for (auto& a : aliensA) allAliens.push_back(&a);
    for (auto& b : aliensB) allAliens.push_back(&b);
    for (auto& c : aliensC) allAliens.push_back(&c);

    spaceship.Draw();

    for (auto& laser : spaceship.lasers) {
        laser.Draw();
    }
    for (auto& laser : mysteryship.mlasers) {
        laser.Draw();
    }

    for (auto& obstacle : obstacles) {
        obstacle.Draw();
    }
    //polimorfizm
    for (auto alien : allAliens) {
        alien->Draw();
    }

    for (auto& laser : alienLasers) {
        laser.Draw();
    }

    mysteryship.Draw();
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::DeleteInactiveLasers()
{
    for (auto it = spaceship.lasers.begin(); it != spaceship.lasers.end();) {
        if (!it->active) {
            it = spaceship.lasers.erase(it);
        }
        else {
            ++it;
        }
    }

    for (auto it = alienLasers.begin(); it != alienLasers.end();) {
        if (!it->active) {
            it = alienLasers.erase(it);
        }
        else {
            ++it;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

std::vector<Obstacle> Game::CreateObstacles()
{
    int obstacleWidth = Obstacle::grid[0].size() * 2;
    float gap = (GetScreenWidth() - (3 * obstacleWidth)) / 4;
    
        for (int i = 0; i < 5; i++) {
            float offsetX = (i + 1) * gap + i * obstacleWidth;
            obstacles.push_back(Obstacle({ offsetX, float(GetScreenHeight() - 200) }));
        }

    return obstacles;
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::CheckForCollisions()
{

    //poolaczony wektor wskaznikow 
    std::vector<Alien*> allAliens;
    allAliens.reserve(aliensA.size() + aliensB.size() + aliensC.size());

    for (auto& a : aliensA) allAliens.push_back(&a);
    for (auto& b : aliensB) allAliens.push_back(&b);
    for (auto& c : aliensC) allAliens.push_back(&c);
 


    for (auto& laser : spaceship.lasers) {
        auto it = aliensA.begin();
        while (it != aliensA.end()) {
            if (CheckCollisionRecs(it->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if (it->type == 1) {
                    score += 101;
                }
                else if (it->type == 2) {
                    score += 202;
                }
                else if (it->type == 3) {
                    score += 303;
                }
                checkForHighscore();

                it = aliensA.erase(it);
                laser.active = false;
            }
            else {
                ++it;
            }
        }
        auto itb = aliensB.begin();
        while (itb != aliensB.end()) {
            if (CheckCollisionRecs(itb->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if (itb->type == 1) {
                    score += 101;
                }
                else if (itb->type == 2) {
                    score += 202;
                }
                else if (itb->type == 3) {
                    score += 303;
                }
                checkForHighscore();

                itb = aliensB.erase(itb);
                laser.active = false;
            }
            else {
                ++itb;
            }
        }
        auto itc = aliensC.begin();
        while (itc != aliensC.end()) {
            if (CheckCollisionRecs(itc->getRect(), laser.getRect()))
            {
                PlaySound(explosionSound);
                if (itc->type == 1) {
                    score += 101;
                }
                else if (itc->type == 2) {
                    score += 202;
                }
                else if (itc->type == 3) {
                    score += 303;
                }
                checkForHighscore();

                itc = aliensC.erase(itc);
                laser.active = false;
            }
            else {
                ++itc;
            }
        }

        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }

        if (CheckCollisionRecs(mysteryship.getRect(), laser.getRect())) {
            mysteryship.alive = false;
            laser.active = false;
            score += 1001;
            checkForHighscore();
            PlaySound(explosionSound);
        }
    }

    for (auto& laser : mysteryship.mlasers) {
        if (!laser.active == true) continue;
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }
        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }
    }

    for (auto& laser : alienLasers) {
        if (CheckCollisionRecs(laser.getRect(), spaceship.getRect())) {
            laser.active = false;
            lives--;
            if (lives == 0) {
                GameOver();
            }
        }

        for (auto& obstacle : obstacles) {
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), laser.getRect())) {
                    it = obstacle.blocks.erase(it);
                    laser.active = false;
                }
                else {
                    ++it;
                }
            }
        }
    }
    HandleAlienObstacleCollision(aliensA);
    HandleAlienObstacleCollision(aliensB);
    HandleAlienObstacleCollision(aliensC);
    
        if (CheckCollisionRecs(mysteryship.getRect(), spaceship.getRect())) {
            GameOver();
        }
    
        for (auto& obstacle : obstacles)
        {
            
            auto it = obstacle.blocks.begin();
            while (it != obstacle.blocks.end()) {
                if (CheckCollisionRecs(it->getRect(), spaceship.getRect())) {
                    GameOver();
                    break; 
                }
                else {
                    ++it;
                }
            }
        }

        //polimorfizm
        for (auto alien : allAliens) {
            if (CheckCollisionRecs(alien->getRect(), spaceship.getRect())) {
                GameOver();
            }
        }
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::GameOver()
{
   
    run = false;
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::InitGame()
{
    obstacles.clear();
    obstacles = CreateObstacles();
    alienSpawnTimer = 0.0f;
    alienSpawnInterval = 3.0f;
    aliensDirection = 1;
    timeLastAlienFired = 0.0;
    timeLastSpawn = 0.0;
    lives = 3;
    score = 0;
    highscore = loadHighscoreFromFile();
    run = true;
    mysteryShipSpawnInterval = GetRandomValue(10, 20);

}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::checkForHighscore()
{
    if (score > highscore) {
        highscore = score;
        saveHighscoreToFile(highscore);
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

//FILESYSTEM//

void Game::saveHighscoreToFile(int highscore)
{
    //FILESYSTEM
    fs::path saveDir = "saves";
    fs::create_directory(saveDir);  

    fs::path highscorePath = saveDir / "highscore.txt";

 

    std::ofstream highscoreFile(highscorePath);
    if (highscoreFile.is_open()) {
        highscoreFile << highscore;
        highscoreFile.close();
        std::cout << "Highscore saved to: " << fs::absolute(highscorePath) << "\n";
    }
    else {
        std::cerr << "Failed to save highscore to file: " << highscorePath << "\n";
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

/* 

FILESYSTEM
REGEX

*/
int Game::loadHighscoreFromFile()
{
    //FILESYSTEM
    fs::path highscorePath = "saves/highscore.txt";

    if (!fs::exists(highscorePath)) {
        std::cerr << "Highscore file not found: " << fs::absolute(highscorePath) << "\n";
        return 0;
    }

    int loadedHighscore = 0;
    std::ifstream highscoreFile(highscorePath);
    if (highscoreFile.is_open()) {
        std::string line;
        std::getline(highscoreFile, line);
        //REGEX
        std::regex intRegex(R"(^\d+$)");
        if (std::regex_match(line, intRegex)) {
            loadedHighscore = std::stoi(line);
        }
        else {
            std::cerr << "Invalid highscore format in file: " << highscorePath << "\n";
        }

        highscoreFile.close();
    }
    else {
        std::cerr << "Failed to open highscore file: " << highscorePath << "\n";
    }

    return loadedHighscore;
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::DeleteOffScreenAliens() {
    for (auto it = aliensA.begin(); it != aliensA.end(); ) {
        if (it->IsOffScreen()) {
            it = aliensA.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = aliensB.begin(); it != aliensB.end(); ) {
        if (it->IsOffScreen()) {
            it = aliensB.erase(it);
        }
        else {
            ++it;
        }
    }
    for (auto it = aliensC.begin(); it != aliensC.end(); ) {
        if (it->IsOffScreen()) {
            it = aliensC.erase(it);
        }
        else {
            ++it;
        }
    }
}

//---------------------------------------------------------------------------------------------------------------------------------//

void Game::Reset() {
    spaceship.Reset();
    aliensA.clear();
    aliensB.clear();
    aliensC.clear();
    alienLasers.clear();
    mysteryship.mlasers.clear();
    obstacles.clear();
    mysteryship.alive = false;
    score = 0;
    InitGame();
}

