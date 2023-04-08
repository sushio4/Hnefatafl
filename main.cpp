#include <SFML/Graphics.hpp>
#include <cmath>
#include "Board/Board.hpp"
#include "Menu/Menu.hpp"
#include "Game.hpp"

const int WINDOW_X = 770, WINDOW_Y = 770;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Hnefatafl");

    Game game;
    game.addScene(new Board("Board", game, window, 0, 0, (int)fmin(WINDOW_X, WINDOW_Y)));
    game.addScene(new Menu("MainMenu", game, window));
    game.setScene("MainMenu");

    while(window.isOpen())
    {
        sf::Event event;
        while(window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            switch(event.type)
            {
            case sf::Event::MouseMoved:
                game.mouseMove(event.mouseMove);
                break;
            case sf::Event::MouseButtonPressed:
                game.mouseClick(event.mouseButton);
                break;
            case sf::Event::KeyPressed:
                game.keyboardPressed(event.key);
                break;
            }
        }

        window.clear();

        game.draw();

        window.display();
    }
    return 0;
}