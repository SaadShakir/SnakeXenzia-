#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Menu.h"
#include "SnakeGame.h"

using namespace sf;
using namespace std;

void drawInstructions(RenderWindow& window, Font& font) {
    window.clear(Color(25, 25, 35));
    Text heading;
    heading.setFont(font);
    heading.setString("HOW TO PLAY");
    heading.setCharacterSize(34);
    heading.setFillColor(Color::Yellow);
    heading.setPosition(285, 90);
    window.draw(heading);

    Text instructions;
    instructions.setFont(font);
    instructions.setString(
        "Use the arrow keys to move the snake.\n"
        "Eat the red food to grow and earn points.\n"
        "Do not hit the walls or your own body.\n\n"
        "Press ESC to return to the main menu."
    );
    instructions.setCharacterSize(22);
    instructions.setFillColor(Color::White);
    instructions.setPosition(145, 210);
    window.draw(instructions);
    window.display();
}

int main() {
    srand(time(0));
    RenderWindow window(VideoMode(800, 600), "Snake Xenzia");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        cout << "Font file was not found. Check the assets folder." << endl;
        return 1;
    }

    int currentScreen = 0; // 0 = menu, 1 = instructions, 2 = game

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
            }

            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                if (currentScreen == 1 || currentScreen == 2)
                    currentScreen = 0;
                else
                    window.close();
            }

            if (currentScreen == 0) {
                int choice = handleMenuInput(event);
                if (choice == 1) {
                    resetGame();
                    currentScreen = 2;
                } else if (choice == 2)
                    currentScreen = 1;
                else if (choice == 3)
                    window.close();
            } else if (currentScreen == 2)
                handleGameInput(event);
        }

        if (currentScreen == 0)
            drawMenu(window, font);
        else if (currentScreen == 1)
            drawInstructions(window, font);
        else if (currentScreen == 2) {
            updateGame();
            drawGame(window, font);
        }
    }

    return 0;
}
