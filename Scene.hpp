#pragma once
#include <string>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/RenderWindow.hpp>

class Game;

class Scene
{
public:
    Scene(std::string name, Game& super, sf::RenderWindow& window);
    virtual void draw() = 0;
    virtual void init() = 0;
    virtual void mouseMove(const sf::Event::MouseMoveEvent& e) = 0;
    virtual void mouseClick(const sf::Event::MouseButtonEvent& e) = 0;
    virtual void keyboardPressed(const sf::Event::KeyEvent& e) = 0;
    std::string getName();
protected:
    std::string name;
    sf::RenderWindow& window;
    Game& super;
};