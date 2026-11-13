#ifndef MENU_H
#define MENU_H

#include <SFML/Graphics.hpp>

enum class MenuChoice
{
    None,
    Play,
    Instructions,
    Exit
};

class Menu
{
private:
    sf::Font& font;
    sf::Text title;
    sf::Text options[3];
    int selectedOption;

    void updateOptionColors();

public:
    Menu(sf::Font& gameFont);

    MenuChoice handleEvent(const sf::Event& event);
    void draw(sf::RenderWindow& window);
};

#endif
