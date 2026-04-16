#ifndef BLOCK_H
#define BLOCK_H

#include "alien.h"
#include <raylib.h>
#include <vector>
#include <iostream>


/**
 * @brief Klasa reprezentuj¹ca pojedynczy blok, bêd¹cy czêœci¹ przeszkody.
 * * Bloki s¹ podstawowymi elementami sk³adaj¹cymi siê na przeszkody, które mog¹
 * zostaæ zniszczone przez lasery.
 */
class Block {
public:
    /**
     * @brief Konstruktor klasy Block.
     * @param position Pozycja bloku (wektor X, Y).
     */
    Block(Vector2 position);

    /**
     * @brief Rysuje blok na ekranie.
     * * Blok jest rysowany jako ma³y prostok¹t w okreœlonym kolorze.
     */
    void Draw();

    /**
     * @brief Zwraca prostok¹t kolizji bloku.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji bloku.
     */
    Rectangle getRect();
private:
    Vector2 position; ///< Pozycja bloku na ekranie.
};
#endif