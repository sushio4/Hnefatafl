#include "Game.hpp"

void Game::addScene(Scene* s)
{
    scenes.push_back(s);
}

void Game::setScene(std::string name)
{
    for(auto s : scenes)
    {
        if(s->getName() == name)
        {
            active = s;
            s->init();
            return;
        }
    }

    active = nullptr;
}

void Game::draw(void)
{
    if(active) active->draw();
}

void Game::mouseMove(const sf::Event::MouseMoveEvent& e)
{
    if(active) active->mouseMove(e);
}

void Game::mouseClick(const sf::Event::MouseButtonEvent& e)
{
    if(active) active->mouseClick(e);
}

void Game::keyboardPressed(const sf::Event::KeyEvent& e)
{
    if(active) active->keyboardPressed(e);
}