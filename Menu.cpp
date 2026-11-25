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
SoundBuffer selectSoundBuffer;
SoundBuffer confirmSoundBuffer;
SoundBuffer escapeSoundBuffer;
SoundBuffer playSoundBuffer;
SoundBuffer restartSoundBuffer;
Sound selectSound;
Sound confirmSound;
Sound escapeSound;
Sound playSound;
Sound restartSound;
void loadMenuSounds()
{
    if (!selectSoundBuffer.loadFromFile("assets/selectmenu.wav"))
        cout << "Failed to load menu selection sound!" << endl;

    if (!confirmSoundBuffer.loadFromFile("assets/confirmmenu.wav"))
        cout << "Failed to load menu confirmation sound!" << endl;
    
        if (!escapeSoundBuffer.loadFromFile("assets/escape.wav"))
        cout << "Failed to load escape sound!" << endl;
    
        if (!playSoundBuffer.loadFromFile("assets/play.mp3"))
        cout << "Failed to load play sound!" << endl;

        if (!restartSoundBuffer.loadFromFile("assets/restart.mp3.mpeg"))
        cout << "Failed to load restart sound!" << endl;


    selectSound.setBuffer(selectSoundBuffer);
    confirmSound.setBuffer(confirmSoundBuffer);
    escapeSound.setBuffer(escapeSoundBuffer);
    playSound.setBuffer(playSoundBuffer);
    restartSound.setBuffer(restartSoundBuffer);
}
int selectedOption = -1;

// Main menu mouse input
int handleMenuInput(Event event)
{
    if (event.type == Event::MouseButtonPressed &&
        event.mouseButton.button == Mouse::Left)
    {
        int mouseX = event.mouseButton.x;
        int mouseY = event.mouseButton.y;

        // Play Game
        if (mouseX >= 250 && mouseX <= 550 &&
            mouseY >= 190 && mouseY <= 240)
        {
            playSound.play();
            return MENU_PLAY;
        }

        // Skins
        else if (mouseX >= 250 && mouseX <= 550 &&
                 mouseY >= 255 && mouseY <= 300)
        {
            confirmSound.play();
            return MENU_SKINS;
        }

        // Maps
        else if (mouseX >= 250 && mouseX <= 550 &&
                 mouseY >= 315 && mouseY <= 365)
        {
            confirmSound.play();
            return MENU_MAPS;
        }

        // Instructions
        else if (mouseX >= 250 && mouseX <= 550 &&
                 mouseY >= 380 && mouseY <= 430)
        {
            confirmSound.play();
            return MENU_INSTRUCTIONS;
        }

        // Exit
        else if (mouseX >= 250 && mouseX <= 550 &&
                 mouseY >= 445 && mouseY <= 495)
        {
            confirmSound.play();
            return MENU_EXIT;
        }
    }

    return MENU_NOTHING;
}

void drawMenu(RenderWindow& window, Font& font)
{
    window.clear();

    window.draw(menuSprite);

    window.display();
}
int selectedSkinOption = 0;
int handleSkinInput(Event event)
{
     if (event.type != Event::KeyPressed)
        return -1;

    if (event.key.code == Keyboard::Left)
    {
        selectedSkinOption--;
        selectSound.play();

        if (selectedSkinOption < 0)
            selectedSkinOption = 3;

        setSelectedSkin(selectedSkinOption);
        loadSnakeTextures();
    }

    else if (event.key.code == Keyboard::Right)
    {
        selectedSkinOption++;
        selectSound.play();

        if (selectedSkinOption > 3)
            selectedSkinOption = 0;

        setSelectedSkin(selectedSkinOption);
        loadSnakeTextures();
    }

    else if (event.key.code == Keyboard::Enter)
    {
        confirmSound.play();
        return selectedSkinOption;
    }

    return -1;}





