# Snake Xenzia — PF Project

## Project overview
Snake Xenzia is a full-screen desktop game written in C++ using SFML 2.6. It builds on Classic Snake with selectable skins and map themes, timed collectibles, a saved high score, and sound effects.

## Included features
- Main menu with mouse controls for Play Game, Skins, Maps, Instructions, and Exit.
- Classic Snake with arrow-key movement. Each red apple adds one body segment and 10 points. The snake moves faster as it grows.
- Four snake skins with previews: Default, Orange, Blue, and Pink.
- Three map themes with previews: Grass, Desert, and Retro. Each changes the playfield background.
- Poison apples appear after random delays of 15–25 seconds and end the run on contact, even while a shield is active.
- Shields appear after random delays of 20–30 seconds. Picking up a shield gives 6 seconds of protection from self-collisions and lets the snake wrap to the opposite side of the board at a wall. The remaining shield time appears on screen.
- Uncollected poison apples and shields disappear after 8 seconds and blink during their final 3 seconds.
- A wall hit or self-collision ends the run when the shield is inactive.
- The game displays the current score and high score. A new record is saved in `highscore.txt` when the run ends and loaded at the start of the next run.
- Looping gameplay music and sound effects for menu actions, collecting items, snake death, the Game Over transition, and restarting.
- The snake's head blinks before the Game Over screen zooms in and displays the final score and high score. Press **R** to restart or **Esc** to return to the menu.

## Project files
| File | Purpose |
|---|---|
| `main.cpp` | Opens the full-screen window, loads assets, and switches between screens. |
| `Menu.h` | Declares menu functions, menu choices, and shared menu sounds. |
| `Menu.cpp` | Handles mouse clicks on the main menu, keyboard input for skin and map selection, and menu sounds. |
| `SnakeGame.h` | Declares game functions and the `Point` structure. |
| `SnakeGame.cpp` | Handles movement, collisions, collectibles, score saving, textures, audio, and game screens. |
| `CMakeLists.txt` | Configures the project's CMake build. |
| `assets/` | Holds the font, screen images, map backgrounds and previews, sprites, and audio. |
| `highscore.txt` | Stores the best score. The game creates this file in its working directory when a new record is saved. |

## Requirements
- Windows 10/11.
- Visual Studio 2022 C++ tools (VC17, x64).
- CMake 3.16 or newer for the build steps below.
- SFML 2.6.x for Visual C++ 17, 64-bit. The build uses SFML Graphics, Window, System, and Audio.
- The project's `assets/` folder, including `BlackOpsOne-Regular.ttf`.


## Build using PowerShell
Open Developer PowerShell for Visual Studio 2022 in the full project folder containing `CMakeLists.txt` and `assets/`.

Change to the project folder:
```powershell
cd "D:\path\to\Snake_Xenzia"
```

Configure CMake. Change the SFML path to the location on your computer:
```powershell
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DSFML_DIR="D:/SFML-2.6.1-windows-vc17-64-bit/SFML-2.6.1/lib/cmake/SFML"
```

Build Debug:
```powershell
cmake --build build --config Debug
```

Run Debug:
```powershell
.\build\Debug\SnakeXenzia.exe
```

Build Release:
```powershell
cmake --build build --config Release
```

Run Release:
```powershell
.\build\Release\SnakeXenzia.exe
```

Run these commands from the project folder so the relative `assets/` path resolves. If the build uses shared SFML libraries, keep the matching DLLs beside the executable, including the SFML Audio DLL.

## What is CMake?
CMake reads `CMakeLists.txt` and prepares the build system. The build configuration tells Visual Studio which source files to compile and which SFML libraries to link.

## Controls
| Key or input | Action |
|---|---|
| Left mouse click | Select an option on the main menu. |
| Left / Right arrows | Cycle through skins or maps on the preview screens. |
| Enter | Confirm the displayed skin or map and return to the main menu. |
| Arrow keys | Steer the snake during gameplay. |
| R | Restart after Game Over. |
| Esc | Return to the main menu from another screen or close the game from the main menu. |

