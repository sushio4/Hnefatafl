#pragma once
#include <string>
#include <SFML/Window/Event.hpp>

class Game;

class Scene
{
public:
    Scene(Game& super, std::string name);
    virtual void draw() = 0;
    virtual void mouseMove(const sf::Event::MouseMoveEvent& e) = 0;
    virtual void mouseClick(const sf::Event::MouseButtonEvent& e) = 0;
    virtual void keyboardPressed(const sf::Event::KeyEvent& e) = 0;
    std::string getName();
protected:
    std::string name;
    Game& super;
};