#include <vector>
#include <SFML/Window/Event.hpp>
#include "Scene.hpp"

class Game 
{
public:
    void addScene(Scene&& s);
    void setScene(std::string name);

    void draw(void);
    void mouseMove(const sf::Event::MouseMoveEvent& e);
    void mouseClick(const sf::Event::MouseButtonEvent& e);
    void keyboardPressed(const sf::Event::KeyEvent& e);
private:
    std::vector<Scene&> scenes;
    Scene* active;
};