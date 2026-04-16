#ifndef ALIEN_H
#define ALIEN_H

#include <raylib.h>


/**
 * @brief Klasa bazowa dla wszystkich typów obcych w grze.
 * * Klasa Alien definiuje wspólny interfejs i podstawowe w³aœciwoœci dla ró¿nych typów obcych.
 * Jest to klasa abstrakcyjna, co oznacza, ¿e nie mo¿na tworzyæ jej bezpoœrednich instancji,
 * a klasy pochodne musz¹ implementowaæ jej czysto wirtualne metody.
 */
class Alien {
public:
    /**
     * @brief Konstruktor klasy Alien.
     * @param edge KrawêdŸ, z której obcy siê pojawi (1: lewo, 2: prawo, 3: góra).
     * @param type Typ obcego (mo¿e byæ u¿yty do rozró¿niania zachowañ lub wygl¹du).
     * @param position Pozycja pocz¹tkowa obcego (wektor X, Y).
     * @param velocity Prêdkoœæ i kierunek ruchu obcego (wektor X, Y).
     */
    Alien(int edge, int type, Vector2 position, Vector2 velocity);

    /**
     * @brief Czysto wirtualna metoda do aktualizacji stanu obcego.
     * * Implementacja tej metody bêdzie zale¿eæ od konkretnego typu obcego.
     */
    virtual void Update() = 0;

    /**
     * @brief Czysto wirtualna metoda do rysowania obcego na ekranie.
     * * Implementacja tej metody bêdzie zale¿eæ od konkretnego typu obcego.
     */
    virtual void Draw() = 0;

    /**
     * @brief Czysto wirtualna metoda sprawdzaj¹ca, czy obcy jest poza ekranem.
     * @return true jeœli obcy jest poza granicami ekranu, false w przeciwnym razie.
     */
    virtual bool IsOffScreen() const = 0;

    /**
     * @brief Czysto wirtualna metoda zwracaj¹ca prostok¹t kolizji obcego.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji obcego.
     */
    virtual Rectangle getRect() const = 0;

    /**
     * @brief Statyczna tablica przechowuj¹ca tekstury dla ró¿nych typów obcych.
     * * Dostêp do tekstur powinien byæ realizowany poprzez klasy pochodne.
     */
    static Texture2D alienImages[3];

    int type; ///< Typ obcego.
    int edge; ///< KrawêdŸ, z której obcy siê pojawi³.

    Vector2 position; ///< Pozycja obcego na ekranie.
    Vector2 velocity; ///< Wektor prêdkoœci obcego.
private:

};

#endif