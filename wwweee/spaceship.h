#ifndef SPACESHIP_H
#define SPACESHIP_H

#include "alien.h"
#include "laser.h"
#include <raylib.h>
#include <vector>




/**
 * @brief Klasa reprezentuj¹ca statek kosmiczny gracza.
 * * Odpowiada za ruch statku, strzelanie laserami i zarz¹dzanie jego stanem.
 */
class Spaceship {
public:
    /**
     * @brief Konstruktor klasy Spaceship.
     * * Inicjalizuje statek gracza, ³aduje tekstury i dŸwiêki.
     */
    Spaceship();

    /**
     * @brief Destruktor klasy Spaceship.
     * * Zwolnienie za³adowanych tekstur i dŸwiêków.
     */
    ~Spaceship();

    /**
     * @brief Rysuje statek kosmiczny na ekranie.
     */
    void Draw() {
        DrawTextureV(image, position, WHITE);
    }

    /**
     * @brief Przesuwa statek w lewo.
     */
    void MoveLeft();

    /**
     * @brief Przesuwa statek w prawo.
     */
    void MoveRight();

    /**
     * @brief Przesuwa statek w górê.
     */
    void MoveUp();

    /**
     * @brief Przesuwa statek w dó³.
     */
    void MoveDown();

    /**
     * @brief Powoduje, ¿e statek wystrzeliwuje laser.
     */
    void FireLaser();

    /**
     * @brief Zwraca prostok¹t kolizji statku.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji statku.
     */
    Rectangle getRect();

    /**
     * @brief Resetuje pozycjê statku i usuwa wszystkie aktywne lasery.
     */
    void Reset();

    std::vector<Laser> lasers; ///< Wektor laserów wystrzelonych przez statek gracza.
    Vector2 movementDirection; ///< Kierunek ostatniego ruchu statku (u¿ywany do okreœlenia kierunku strza³u).

private:
    Texture2D image; ///< Tekstura statku kosmicznego.
    Vector2 position; ///< Pozycja statku kosmicznego (wektor X, Y).
    double lastFireTime; ///< Czas ostatniego strza³u gracza.
    Sound laserSound; ///< DŸwiêk lasera wystrzelonego przez gracza.
};
#endif