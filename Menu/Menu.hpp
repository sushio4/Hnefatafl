#pragma once
#include "../Scene.hpp"
#include <SFML/Graphics.hpp>

class Menu : public Scene 
{
public:
    Menu(std::string name, Game& super, sf::RenderWindow& window);

    void draw();
    void init();

    void mouseClick(const sf::Event::MouseButtonEvent& e);
    void mouseMove(const sf::Event::MouseMoveEvent& e);
    void keyboardPressed(const sf::Event::KeyEvent& e);

private:
    int selected = -1;

    sf::Font font;
};