#include "Scene.hpp"

std::string Scene::getName()
{
    return name;
}

Scene::Scene(std::string name, Game& super, sf::RenderWindow& window) : window(window), super(super), name(name) {}