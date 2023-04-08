#include "Menu.hpp"
#include "../Game.hpp"

Menu::Menu(std::string name, Game& super, sf::RenderWindow& window) : Scene(name, super, window) 
{
    font.loadFromFile("default.otf");
}

void Menu::init()
{
    selected = -1;
}

void Menu::draw()
{
    window.clear(sf::Color(0x6E, 0x2C, 0x00));

    sf::Text text;
    text.setFont(font);
    text.setString("HNEFATAFL");
    text.setCharacterSize(60);
    text.setPosition(sf::Vector2f(60,30));
    text.setFillColor(sf::Color::White);
    window.draw(text);

    text.setPosition(sf::Vector2f(60,120));
    text.setCharacterSize(40);
    text.setString("aka Vikings chess");
    window.draw(text);

    //New game
    sf::RectangleShape rect(sf::Vector2f(400, 80));
    rect.setPosition(60, 200);
    if(selected == 0)
        rect.setFillColor(sf::Color(0xF3, 0x9C, 0x12));
    else
        rect.setFillColor(sf::Color(0x78, 0x42, 0x12));
    window.draw(rect);

    text.setPosition(90, 215);
    text.setString("New game");
    window.draw(text);

    //Exit
    rect.setPosition(60, 320);
    if(selected == 1)
        rect.setFillColor(sf::Color(0xF3, 0x9C, 0x12));
    else
        rect.setFillColor(sf::Color(0x78, 0x42, 0x12));
    window.draw(rect);

    text.setPosition(90, 335);
    text.setString("Exit");
    window.draw(text);

    window.display();
}

void Menu::mouseClick(const sf::Event::MouseButtonEvent& e)
{
    int x = e.x;
    int y = e.y;

    if(x >= 60 && x <= 460 && y >= 200 && y <= 280)
        super.setScene("Board");
    else if(x >= 60 && x <= 460 && y >= 320 && y < 400)
        window.close();
}

void Menu::mouseMove(const sf::Event::MouseMoveEvent& e)
{
    int x = e.x;
    int y = e.y;

    if(x >= 60 && x <= 460 && y >= 200 && y <= 280)
        selected = 0;
    else if(x >= 60 && x <= 460 && y >= 320 && y < 400)
        selected = 1;
    else
        selected = -1;
}

void Menu::keyboardPressed(const sf::Event::KeyEvent& e)
{

}