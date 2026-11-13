# SnakeXenzia-
A 2D GAME BUILT BY STUDENTS OF FAST NUCES AS THEIR SEMESTER PROJECT FOR PROGRAMMING FUNDAMENTALS CS 1002

Snake Xenzia PF Project  

Snake Xenzia is a game written in C++ using SFML 2.6. This repository contains the first 25% work :a main menu, instructions screen and one playable basic mode. 


Included features 
Main menu: Play Game, Instructions and Exit. 
One Classic Snake mode. 
Arrow-key movement. 
Food appears at a random empty square. 
Eating food increases the snake length and adds 10 points. 
Hitting a wall or the snake's own body ends the game. 
R restarts after Game Over. 
ESC returns to the menu. ESC on the main menu closes the game. 


Project files 

File & Purpose 

main.cpp 
Opens the window and switches between screens. 

Menu.h 
Lists menu functions and menu choice numbers. 

Menu.cpp 
Reads menu key presses and draws the menu. 

SnakeGame.h 
Lists game functions and the Point structure. 

SnakeGame.cpp 
Snake array, movement, food, score, collision and drawing. 

CMakeLists.txt 
Build instructions and automatic copying of runtime files. 

assets/ 
Font used by the game. 

Requirements 
Windows 10/11. 
Visual Studio 2022 C++ tools (VC17, x64). 
CMake 3.16 or newer. 
SFML 2.6.x for Visual C++ 17, 64-bit. 
A TrueType font named arial.ttf inside assets/. 

Font setup 

The program expects assets/arial.ttf. For a font that can be included in a student GitHub repository, download the regular Roboto TrueType font from Google Fonts, place it in assets, and rename it to arial.ttf. Keep its licence file in the assets folder. Roboto is listed under the SIL Open Font License. 
Download: https://fonts.google.com/specimen/Roboto 

Do not copy a Windows system font into a public repository unless you have checked that you are allowed to redistribute it. 

Build using PowerShell 

Open Developer PowerShell for Visual Studio 2022 in the folder containing CMakeLists.txt. 

Change to the project folder: 
cd "D:\SnakeXenzia” 

Configure CMake. Change the SFML path to the location on your computer: 
cmake -S . -B build -G "Visual Studio 17 2022" -A x64 -DSFML_DIR="D:/SFML-2.6.1-windows-vc17-64-bit/SFML-2.6.1/lib/cmake/SFML" 

Build Debug: 
cmake --build build --config Debug 

Run Debug: 
.\build\Debug\SnakeXenzia.exe 

Build Release: 
cmake --build build --config Release 

Run Release: 
.\build\Release\SnakeXenzia.exe 

CMake copies the assets folder and the matching SFML DLL files beside the executable after a successful build. Manual DLL copying and a repeated PATH command should not be necessary. 

What is CMake? 

CMake reads CMakeLists.txt and prepares the build system. It tells the build system which source files to compile, which SFML libraries to link, and which runtime files to copy. CMake is not the C++ compiler; the Visual Studio compiler creates the executable. 

Controls 

Key & Action 

Up / Down 
Move through menu options 

Enter 
Select a menu option 

Arrow keys 
Move the snake 

R 
Restart after Game Over 

ESC 
Return to menu; close from the main menu 

Suggested group responsibilities 
Member 1: main.cpp, Menu.h, Menu.cpp — window, menu, instructions and screen changes. 
Member 2: SnakeGame.h and snake movement/input sections of SnakeGame.cpp. 
Member 3: food placement, score, collision, drawing/testing and README. 

All members should understand the complete project. Members 2 and 3 must coordinate before editing SnakeGame.cpp so that one person's changes do not overwrite the other's. 

GitHub workflow 
Create the repository and add all source files, CMakeLists.txt, README and the licensed font file. 
Add the other group members as collaborators. 
Each member clones the repository. 
Before editing, run git pull. 
Make a small change, test it, then commit and push. 
Do not upload the generated build folder. Each member configures and builds on their own computer.

Basic game logic 
The snake is stored in a normal array. snake[0] is the head. 
directionX and directionY store the movement direction. 
A clock controls how often the snake moves. 
Food is placed at a random empty grid square. 
Eating food increases the length and score. 
Wall or body collision ends the game. 

 
