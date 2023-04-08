#include "Scene.hpp"

std::string Scene::getName()
{
    return name;
}

Scene::Scene(Game& super, std::string name) : super(super), name(name) {}