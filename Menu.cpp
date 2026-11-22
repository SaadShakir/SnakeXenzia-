#include "Menu.h"
#include <iostream>
#include "SnakeGame.h"
using namespace std;
using namespace sf;

Texture menuTexture;
Sprite menuSprite;
void loadMenuImage()
{
    if (!menuTexture.loadFromFile("assets/menu.png"))
    {
        cout << "Failed to load menu image!" << endl;
    }
    else
    {
        menuSprite.setTexture(menuTexture);
        menuSprite.setScale(800.0f / menuTexture.getSize().x,
                          600.0f / menuTexture.getSize().y);
    }
}

void drawMenu(RenderWindow& window, Font& font)
{
    window.clear();

    window.draw(menuSprite);

    window.display();
}

