#ifndef ALIENB_H
#define ALIENB_H

#include "alien.h"
#include <raylib.h>

/**
 * @brief Klasa reprezentuj¹ca drugi typ obcego (Alien B).
 * * Dziedziczy po klasie Alien i implementuje jej czysto wirtualne metody.
 * Obs³uguje ³adowanie i roz³adowywanie w³asnych tekstur oraz specyficzne zachowanie.
 */
class alienB : public Alien
{
public:

    /**
     * @brief Konstruktor klasy alienB.
     * @param edge KrawêdŸ, z której obcy siê pojawi (1: lewo, 2: prawo, 3: góra).
     * @param type Typ obcego (dla alienB zawsze 0, ale zachowane dla spójnoœci z klas¹ bazow¹).
     * @param position Pozycja pocz¹tkowa obcego (wektor X, Y).
     * @param velocity Prêdkoœæ i kierunek ruchu obcego (wektor X, Y).
     */
    alienB(int edge, int type, Vector2 position, Vector2 velocity);

    /**
     * @brief Aktualizuje pozycjê obcego.
     * * Implementacja metody wirtualnej z klasy bazowej Alien.
     */
    void Update() override;

    /**
     * @brief Rysuje obcego na ekranie.
     * * Implementacja metody wirtualnej z klasy bazowej Alien. Wykorzystuje teksturê
     * odpowiadaj¹c¹ wartoœci 'edge' obcego.
     */
    void Draw() override;

    /**
     * @brief Sprawdza, czy obcy jest poza ekranem.
     * @return true jeœli obcy jest poza granicami ekranu, false w przeciwnym razie.
     * * Implementacja metody wirtualnej z klasy bazowej Alien.
     */
    bool IsOffScreen() const override;

    /**
     * @brief Zwraca prostok¹t kolizji obcego.
     * @return Obiekt Rectangle reprezentuj¹cy obszar kolizji obcego.
     * * Implementacja metody wirtualnej z klasy bazowej Alien.
     */
    Rectangle getRect() const override;

    /**
     * @brief Statyczna metoda do ³adowania wszystkich tekstur dla Alien B.
     * * Tekstury s¹ ³adowane tylko raz i przechowywane w statycznej tablicy `alienBImages`.
     */
    static void LoadImages();

    /**
     * @brief Statyczna metoda do roz³adowywania wszystkich tekstur dla Alien B.
     * * Zwolnienie zasobów tekstur.
     */
    static void UnloadImages();

    /**
     * @brief Statyczna tablica przechowuj¹ca tekstury dla Alien B.
     * * Tablica zawiera trzy tekstury odpowiadaj¹ce ró¿nym krawêdziom (edge).
     */
    static Texture2D alienBImages[3];

    /**
     * @brief Statyczna metoda zwracaj¹ca referencjê do tekstury Alien B na podstawie krawêdzi.
     * @param edge KrawêdŸ (1, 2 lub 3) okreœlaj¹ca, któr¹ teksturê zwróciæ.
     * @return Referencja do obiektu Texture2D.
     */
    static Texture2D& GetImage(int edge);

};


#endif