#include "Menu.h"

Menu::Menu(sf::Font& gameFont) : font(gameFont)
{
    selectedOption = 0;

    title.setFont(font);
    title.setString("SNAKE XENZIA");
    title.setCharacterSize(46);
    title.setFillColor(sf::Color::Green);
    title.setPosition(220, 100);

    options[0].setString("Play Game");
    options[1].setString("Instructions");
    options[2].setString("Exit");

    for (int i = 0; i < 3; i++)
    {
        options[i].setFont(font);
        options[i].setCharacterSize(28);
        options[i].setPosition(315, 260 + i * 65);
    }

    updateOptionColors();
}

void Menu::updateOptionColors()
{
    for (int i = 0; i < 3; i++)
    {
        if (i == selectedOption)
        {
            options[i].setFillColor(sf::Color::Yellow);
        }
        else
        {
            options[i].setFillColor(sf::Color::White);
        }
    }
}

MenuChoice Menu::handleEvent(const sf::Event& event)
{
    if (event.type != sf::Event::KeyPressed)
    {
        return MenuChoice::None;
    }

    if (event.key.code == sf::Keyboard::Up)
    {
        selectedOption--;

        if (selectedOption < 0)
        {
            selectedOption = 2;
        }

        updateOptionColors();
    }
    else if (event.key.code == sf::Keyboard::Down)
    {
        selectedOption++;

        if (selectedOption > 2)
        {
            selectedOption = 0;
        }

        updateOptionColors();
    }
    else if (event.key.code == sf::Keyboard::Enter)
    {
        if (selectedOption == 0)
        {
            return MenuChoice::Play;
        }
        else if (selectedOption == 1)
        {
            return MenuChoice::Instructions;
        }
        else
        {
            return MenuChoice::Exit;
        }
    }

    return MenuChoice::None;
}

void Menu::draw(sf::RenderWindow& window)
{
    window.clear(sf::Color(25, 25, 35));

    window.draw(title);

    for (int i = 0; i < 3; i++)
    {
        window.draw(options[i]);
    }

    window.display();
}
