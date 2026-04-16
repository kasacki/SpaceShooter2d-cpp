#ifndef LASER_H
#define LASER_H

#include "alien.h"
#include <raylib.h>
#include <vector>
#include <iostream>


/**
 * @brief Klasa reprezentuj¹ca pojedynczy laser w grze.
 * * Lasery mog¹ byæ wystrzeliwane zarówno przez gracza, jak i przez obcych.
 */
class Laser {
public:
    Vector2 position; ///< Pozycja lasera na ekranie.
    Vector2 velocity; ///< Wektor prêdkoœci lasera.
    bool active; ///< Flaga okreœlaj¹ca, czy laser jest aktywny (widoczny i kolizyjny).

    /**
     * @brief Konstruktor klasy Laser.
     * @param position Pozycja pocz¹tkowa lasera.
     * @param velocity Wektor prêdkoœci i kierunku lasera.
     */
    Laser(Vector2 position, Vector2 velocity);

    /**
     * @brief Aktualizuje pozycjê lasera i sprawdza, czy nie wylecia³ poza ekran.
     */
    void Update();

    /**
     * @brief Rysuje laser na ekranie.
     * * Laser jest rysowany jako prostok¹t, którego wymiary zale¿¹ od kierunku ruchu.
     */
    void Draw();

    /**
     * @brief Zwraca prostok¹t kolizji lasera.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji lasera.
     */
    Rectangle getRect();
};
#endif