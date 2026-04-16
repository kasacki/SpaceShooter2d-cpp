#ifndef MYSTERYSHIP_H
#define MYSTERYSHIP_H
#include "laser.h"
#include "alien.h"
#include <raylib.h>
#include <vector>
#include <iostream>



/**
 * @brief Klasa reprezentuj¹ca tajemniczy statek kosmiczny.
 * * Tajemniczy statek pojawia siê losowo na górze ekranu, porusza siê
 * poziomo i mo¿e strzelaæ laserami.
 */
class MysteryShip {
public:
    /**
     * @brief Konstruktor klasy MysteryShip.
     * * £aduje tekstury i dŸwiêki, ustawia pocz¹tkowy stan statku.
     */
    MysteryShip();

    /**
     * @brief Destruktor klasy MysteryShip.
     * * Zwolnienie za³adowanych tekstur.
     */
    ~MysteryShip();

    /**
     * @brief Aktualizuje stan tajemniczego statku (ruch, czy jest aktywny).
     */
    void Update();

    /**
     * @brief Rysuje tajemniczy statek na ekranie, jeœli jest aktywny.
     */
    void Draw();

    /**
     * @brief Spawnuje tajemniczy statek w losowej pozycji pocz¹tkowej.
     * * Ustawia statek na pocz¹tku ekranu po lewej lub prawej stronie.
     */
    void Spawn();

    /**
     * @brief Zwraca prostok¹t kolizji tajemniczego statku.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji statku.
     * * Zwraca prostok¹t o zerowych wymiarach, jeœli statek nie jest aktywny.
     */
    Rectangle getRect();

    bool alive; ///< Flaga okreœlaj¹ca, czy tajemniczy statek jest aktywny.

    /**
     * @brief Powoduje, ¿e tajemniczy statek wystrzeliwuje lasery.
     */
    void FireLasers();

    float lastFireTime; ///< Czas ostatniego strza³u tajemniczego statku.
    std::vector<Laser> mlasers; ///< Wektor laserów wystrzelonych przez tajemniczy statek.
private:
    Vector2 position; ///< Pozycja tajemniczego statku na ekranie.
    Texture2D image; ///< Tekstura tajemniczego statku.
    int speed; ///< Prêdkoœæ pozioma tajemniczego statku.
    Sound laserSound; ///< DŸwiêk lasera wystrzelonego przez tajemniczy statek.
};
#endif