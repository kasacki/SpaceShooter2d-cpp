#ifndef GAME_H
#define GAME_H

#include "alien.h"
#include "obstacle.h"
#include "spaceship.h"
#include "mysteryship.h"
#include "laser.h"
#include "alienA.h"
#include "alienB.h"
#include "alienC.h"
#include <raylib.h>
#include <vector>
#include <iostream>
#include <fstream>
#include <chrono>
#include <concepts>
#include <ranges>
#include <algorithm>
#include <iterator>
#include <memory>
#include <filesystem> // Dodano to do 'namespace fs = std::filesystem;'

/**
 * @brief Koncept definiuj¹cy wymagania dla typów "Alien-podobnych".
 *
 * U¿ywany do zapewnienia, ¿e typy u¿ywane w szablonach funkcji zwi¹zanych z obcymi
 * posiadaj¹ niezbêdne pola i metody.
 * Wymaga pól: `position` (Vector2), `velocity` (Vector2), `edge` (int).
 * Wymaga statycznej metody: `GetImage(int edge)` zwracaj¹cej `Texture2D&`.
 *
 * @tparam T Typ, który ma zostaæ sprawdzony pod k¹tem zgodnoœci z konceptem AlienLike.
 */
template<typename T>
concept AlienLike = requires(T alien) {
    { alien.position } -> std::convertible_to<Vector2>;
    { alien.velocity } -> std::convertible_to<Vector2>;
    { alien.edge } -> std::convertible_to<int>;
    { T::GetImage(alien.edge) } -> std::convertible_to<Texture2D&>;
};

namespace fs = std::filesystem;

/**
 * @brief Klasa zarz¹dzaj¹ca logik¹ i stanem gry.
 *
 * Klasa Game obs³uguje inicjalizacjê, aktualizacjê i rysowanie wszystkich elementów gry,
 * takich jak statek kosmiczny, obcy, pociski, przeszkody i statek-zagadka.
 * Zarz¹dza równie¿ punktacj¹, ¿yciem gracza, logik¹ menu oraz zapisem/odczytem najlepszego wyniku.
 */
class Game {
public:
    /**
     * @brief Konstruktor klasy Game.
     * Inicjalizuje wszystkie komponenty gry, ³aduje zasoby audio i tekstury.
     */
    Game();

    /**
     * @brief Destruktor klasy Game.
     * Zwalnia za³adowane zasoby, takie jak dŸwiêki i tekstury.
     */
    ~Game();

    /**
     * @brief Rysuje wszystkie elementy gry na ekranie.
     * Obejmuje rysowanie statku gracza, obcych, laserów, przeszkód, statku-zagadki oraz HUD (wynik, ¿ycia).
     */
    void Draw();

    /**
     * @brief Aktualizuje stan gry.
     * Obs³uguje ruchy obcych, laserów, statku-zagadki, sprawdzanie kolizji,
     * zarz¹dzanie spawnowaniem obcych i laserów.
     */
    void Update();

    /**
     * @brief Obs³uguje wejœcie od gracza.
     * Przetwarza naciœniêcia klawiszy do sterowania statkiem kosmicznym gracza i strzelania.
     */
    void HandleInput();

    bool run; ///< Flaga wskazuj¹ca, czy gra jest uruchomiona.
    int lives; ///< Liczba pozosta³ych ¿yæ gracza.
    int score; ///< Aktualny wynik gracza.
    int highscore; ///< Najwy¿szy osi¹gniêty wynik.
    double timeLastAlienFiredA; ///< Czas ostatniego strza³u obcego typu A.
    double timeLastAlienFiredB; ///< Czas ostatniego strza³u obcego typu B.
    double timeLastAlienFiredC; ///< Czas ostatniego strza³u obcego typu C.
    Music music; ///< Muzyka w tle gry.

    /**
     * @brief Resetuje stan gry do pocz¹tkowego.
     * U¿ywane po zakoñczeniu gry w celu rozpoczêcia nowej rundy.
     */
    void Reset();

    /**
     * @brief Tworzy przeszkody na planszy.
     * @return Wektor obiektów Obstacle reprezentuj¹cych przeszkody.
     */
    std::vector<Obstacle> CreateObstacles();

    float alienSpawnInterval; ///< Interwa³ spawnowania obcych w sekundach.

private:
    /**
     * @brief Pozwala obcym danego typu na strzelanie laserami.
     * @tparam AlienType Typ obcego (musi spe³niaæ koncept AlienLike).
     * @param aliens Wektor obcych danego typu.
     * @param timeLastShot Referencja do zmiennej przechowuj¹cej czas ostatniego strza³u.
     * @param laserList Referencja do wektora, do którego dodawane s¹ lasery.
     * @param interval Minimalny interwa³ miêdzy strza³ami obcych.
     */
    template <AlienLike AlienType>
    void AlienShootLaserFrom(std::vector<AlienType>& aliens, double& timeLastShot, std::vector<Laser>& laserList, double interval);

    /**
     * @brief Obs³uguje kolizje laserów obcych z przeszkodami.
     * @tparam AlienType Typ obcego (musi spe³niaæ koncept AlienLike).
     * @param aliens Wektor obcych danego typu.
     */
    template <AlienLike AlienType>
    void HandleAlienObstacleCollision(std::vector<AlienType>& aliens);

    /**
     * @brief Spawnuje obcego danego typu.
     * @tparam AlienType Typ obcego (musi spe³niaæ koncept AlienLike).
     * @param container Kontener, do którego dodawany jest nowy obcy.
     */
    template<AlienLike AlienType>
    void SpawnAlien(std::vector<AlienType>& container);

    /**
     * @brief Usuwa nieaktywne lasery (te, które opuœci³y ekran lub uderzy³y w coœ).
     */
    void DeleteInactiveLasers();

    /**
     * @brief Sprawdza wszystkie mo¿liwe kolizje w grze.
     * Obejmuje kolizje laserów gracza z obcymi/statkiem-zagadk¹,
     * laserów obcych ze statkiem gracza/przeszkodami,
     * oraz obcych z przeszkodami.
     */
    void CheckForCollisions();

    /**
     * @brief Obs³uguje logikê koñca gry.
     * Wyœwietla komunikat "GAME OVER" i resetuje stan gry po krótkiej przerwie.
     */
    void GameOver();

    /**
     * @brief Inicjalizuje stan pocz¹tkowy gry.
     * Ustawia pocz¹tkowe wartoœci ¿ycia, punktacji i innych zmiennych.
     */
    void InitGame();

    /**
     * @brief Sprawdza, czy aktualny wynik jest nowym rekordem.
     * Jeœli tak, aktualizuje highscore i zapisuje go do pliku.
     */
    void checkForHighscore();

    /**
     * @brief Zapisuje najlepszy wynik do pliku.
     * @param highscore Wartoœæ najlepszego wyniku do zapisania.
     */
    void saveHighscoreToFile(int highscore);

    /**
     * @brief Odczytuje najlepszy wynik z pliku.
     * @return Wczytany najlepszy wynik.
     */
    int loadHighscoreFromFile();

    /**
     * @brief Usuwa obcych, którzy opuœcili ekran.
     */
    void DeleteOffScreenAliens();

    Spaceship spaceship; ///< Obiekt reprezentuj¹cy statek kosmiczny gracza.
    std::vector<Obstacle> obstacles; ///< Wektor przeszkód.
    std::vector<alienA> aliensA; ///< Wektor obcych typu A.
    std::vector<alienB> aliensB; ///< Wektor obcych typu B.
    std::vector<alienC> aliensC; ///< Wektor obcych typu C.
    std::vector<Alien*> aliensToRemove; ///< Tymczasowy wektor obcych do usuniêcia.
    int currentSpawnType; ///< Typ obcego, który ma byæ spawnowany (cyklicznie).
    int randomType; ///< Losowy typ obcego do spawnowania (0 = A, 1 = B, 2 = C).
    bool spawning; ///< Flaga wskazuj¹ca, czy obcy s¹ aktualnie spawnowani.
    int aliensDirection; ///< Kierunek ruchu obcych (1 dla prawo, -1 dla lewo).
    std::vector<Laser> alienLasers; ///< Wektor laserów wystrzelonych przez obcych.
    constexpr static float alienLaserShootInterval = 1.0; ///< Sta³y interwa³ strza³ów laserowych obcych.
    float timeLastAlienFired; ///< Czas ostatniego strza³u dowolnego obcego.
    MysteryShip mysteryship; ///< Obiekt reprezentuj¹cy statek-zagadkê.
    float mysteryShipSpawnInterval; ///< Interwa³ spawnowania statku-zagadki.
    float timeLastSpawn; ///< Czas ostatniego spawnu statku-zagadki.
    Sound explosionSound; ///< DŸwiêk eksplozji.
    Sound laserSound; ///< DŸwiêk lasera.
    float alienSpawnTimer; ///< Licznik czasu do spawnowania kolejnej fali obcych.
};

#endif