# SpaceShooter 2D

A classic **Space Shooter** game written in **C++** using the [raylib](https://www.raylib.com/) library. The player's ship defends against waves of aliens attacking from all sides of the screen, and a mysterious bonus ship appears for brave players with a high score.

---

## Table of Contents

- [Requirements](#requirements)
- [Building and Running](#building-and-running)
- [How to Play](#how-to-play)
- [Controls](#controls)
- [Enemies](#enemies)
- [Scoring System](#scoring-system)
- [Project Structure](#project-structure)
- [Technologies](#technologies)

---

## Requirements

- **Operating system:** Windows (project includes a `.sln` file for Visual Studio)
- **Compiler:** MSVC (Visual Studio 2022 or newer) with **C++20** support
- **Library:** [raylib](https://www.raylib.com/) — must be installed and configured in the project
- **Standard:** C++20 (uses: `concepts`, `ranges`, `std::filesystem`)

---

## Building and Running

1. Clone or download the repository.
2. Open `wwweee.sln` in **Visual Studio**.
3. Make sure the **raylib** library is correctly linked in the project settings.
4. Build the project (`Ctrl+Shift+B`) and run (`F5`).

> Note: The game loads assets (graphics, sounds, fonts) from relative paths. Make sure the working directory at runtime is the folder containing the `Graphics/`, `Sounds/`, and `Font/` subdirectories.

---

## How to Play

The game starts immediately upon launch. Your goal is to **survive as long as possible** and **score as many points as you can** by shooting aliens attacking from all sides of the screen.

### Rules

- You control a spaceship that can move freely across the entire screen.
- Aliens spawn randomly from the **left, right, and top** edges of the screen and fly toward the center.
- Aliens also **fire lasers** — avoid them!
- The map contains **obstacles (bunkers)** made of blocks that protect you from enemy lasers, but can be destroyed.
- You have **3 lives**. Every hit from an enemy laser or collision with an alien costs one life.
- When all lives are gone — **game over**.
- Press **ENTER** to restart after losing.

### Mystery Ship

Once you exceed **1000 points**, a mystery ship begins appearing, flying horizontally across the top of the screen. Shooting it down awards **1001 points**, but beware — it fires back!

---

## Controls

| Key / Button | Action |
|---|---|
| `A` | Move left |
| `D` | Move right |
| `W` | Move up |
| `S` | Move down |
| **Left mouse button** | Shoot (laser) |
| `R` | Restart after game over |

---

## Enemies

The game features **three types of aliens** (AlienA, AlienB, AlienC), each with their own graphics and animation. Types alternate so that enemy waves are varied.

Aliens enter from one of three screen edges:
- **Top** — fly downward
- **Left side** — fly rightward
- **Right side** — fly leftward

Each alien randomly fires lasers in its direction of travel — lasers can travel horizontally or vertically depending on where the enemy entered from.

### Mystery Ship

Appears randomly every 10–20 seconds, **but only when the player has more than 1000 points**. It flies horizontally across the screen and fires lasers. Shooting it down is the highest-scoring event in the game.

---

## Scoring System

| Event | Points |
|---|---|
| Shooting down AlienA | +101 |
| Shooting down AlienB | +202 |
| Shooting down AlienC | +303 |
| Shooting down Mystery Ship | +1001 |

- The current score and **high score** are displayed on screen during gameplay.
- The high score is **saved to a file** and loaded on the next launch — your record is safe!

---

## Project Structure

```
SpaceShooter2d-cpp-master/
├── wwweee.sln               # Visual Studio solution file
└── wwweee/
    ├── main.cpp             # Program entry point
    ├── game.cpp / game.h    # Main game logic
    ├── spaceship.cpp / .h   # Player ship
    ├── alien.cpp / .h       # Alien base class
    ├── alienA/B/C.cpp / .h  # Three alien types
    ├── mysteryship.cpp / .h # Bonus mystery ship
    ├── laser.cpp / .h       # Projectiles (lasers)
    ├── obstacle.cpp / .h    # Obstacles / bunkers
    ├── block.cpp / .h       # Blocks that make up obstacles
    ├── Graphics/            # Graphics (PNG)
    ├── Sounds/              # Sound effects (OGG) + music
    ├── Font/                # Font (monogram.ttf)
    └── html/                # Generated Doxygen documentation
```

---

## Technologies

- **C++20** — `concepts`, `std::ranges`, `std::filesystem`, templates
- **[raylib](https://www.raylib.com/)** — 2D rendering, input handling, audio
- **Doxygen** — class and method documentation (available in the `html/` directory)
- **Visual Studio** — development environment (`.sln`)
- **Design patterns:** inheritance (base class `Alien`), concepts (`AlienLike`), function templates

---

## License/Author

Project created for educational purposes.
Karol Sawicki Silesian University of technology
