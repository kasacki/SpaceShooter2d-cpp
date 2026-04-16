#ifndef OBSTACLE_H
#define OBSTACLE_H

#include "alien.h"
#include "block.h"
#include <raylib.h>
#include <vector>
#include <iostream>




/**
 * @brief Klasa reprezentuj¹ca przeszkodê z³o¿on¹ z bloków.
 * * Przeszkody s³u¿¹ jako os³ona dla gracza i mog¹ byæ niszczone przez lasery.
 */
class Obstacle {
public:
    /**
     * @brief Konstruktor klasy Obstacle.
     * @param position Pozycja pocz¹tkowa lewego górnego rogu przeszkody.
     * * Na podstawie statycznej siatki `grid` tworzy wektor obiektów Block,
     * które sk³adaj¹ siê na przeszkodê.
     */
    Obstacle(Vector2 position);

    /**
     * @brief Rysuje wszystkie aktywne bloki nale¿¹ce do przeszkody.
     */
    void Draw();

    Vector2 position; ///< Pozycja lewego górnego rogu przeszkody.
    std::vector<Block> blocks; ///< Wektor bloków tworz¹cych przeszkodê.

    /**
     * @brief Statyczna siatka (mapa) definiuj¹ca kszta³t przeszkody.
     * * Wartoœæ 1 oznacza aktywny blok, 0 oznacza pust¹ przestrzeñ.
     */
    static std::vector<std::vector<int>> grid;
private:
};
#endif