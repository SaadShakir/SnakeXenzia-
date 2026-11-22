#include <SFML/Graphics.hpp>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include "Menu.h"
#include "SnakeGame.h"

using namespace sf;
using namespace std;


int main() {
    srand(time(0));
    RenderWindow window(VideoMode(800, 600), "Snake Xenzia");
    window.setFramerateLimit(60);

    Font font;
    if (!font.loadFromFile("assets/arial.ttf")) {
        cout << "Font file was not found. Check the assets folder." << endl;
        return 1;
    }
    
    loadGameOverImage();
    loadAppleTexture();
    loadInstructionsBackground();
    loadSnakeTextures();
    loadMenuImage();
    loadSkinMenuBackground();
    loadMapMenuBackground();
    loadMapPreviewImages();
    int currentScreen = 0; // 0 = menu, 1 = skins, 2 = instructions, 3 = game , 4 = gameover, 5 = map 

   while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed) {
                window.close();
                continue;
            }


            if (event.type == Event::KeyPressed && event.key.code == Keyboard::Escape) {
                if (currentScreen == 1 || currentScreen == 2 || currentScreen == 3||currentScreen==4|| currentScreen==5)
                    currentScreen = 0;
                else
                    window.close();
            }

            if (currentScreen == 0) {
                int choice = handleMenuInput(event);
                if (choice == 1) {
                    resetGame();
                    currentScreen = 3;
                } else if (choice == 2)
                    currentScreen = 2;
                else if (choice == 3)
                    currentScreen = 5;
                else if (choice == 4)
                    currentScreen = 1;
                else if (choice ==5 )
                    window.close();
            } 
            else if (currentScreen == 3) {
                handleGameInput(event);
            }
            else if (currentScreen == 2) {
                int skinChoice = handleSkinInput(event);
                if (skinChoice != -1)
                {
                setSelectedSkin(skinChoice);
                loadSnakeTextures();
                currentScreen = 0;
                }
            }
            else if (currentScreen == 4)
            {
        if (event.type == Event::KeyPressed)
        {
        if (event.key.code == Keyboard::R)
           {
            resetGame();
            currentScreen = 3;
           }
        }
           }
            else if (currentScreen == 5)
{
    int mapChoice = handleMapInput(event);

    if (mapChoice != -1)
    {
        setSelectedMap(mapChoice);
        loadSnakeTextures();
        currentScreen = 0;
    }
}     
        }
        if (currentScreen == 0) 
        {
            drawMenu(window, font);
        }
        else if (currentScreen == 1) 
        {
            drawInstructions(window);
        }
        else if (currentScreen == 2) 
        {
              drawSkinPreview(window);
        }
        else if (currentScreen == 3) 
        {
            updateGame();
            if (isGameOver())
            {
            currentScreen = 4;
            }
            drawGame(window, font);
        }
        else if (currentScreen == 4)
        {
        drawGameOver(window, font);
        }
        else if (currentScreen == 5)
        {
        drawMapPreview(window);
        }
    }

    return 0;
}
