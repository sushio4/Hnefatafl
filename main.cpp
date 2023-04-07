#include <SFML/Graphics.hpp>
#include <cmath>
#include "Board.hpp"

const int WINDOW_X = 770, WINDOW_Y = 770;

int main()
{
    sf::RenderWindow window(sf::VideoMode(WINDOW_X, WINDOW_Y), "Hnefatafl");

    Board board(window, 0, 0, (int)fmin(WINDOW_X, WINDOW_Y));


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
                board.mouseMove(event.mouseMove.x, event.mouseMove.y);
                break;
            case sf::Event::MouseButtonPressed:
                board.mouseClick(event.mouseButton.x, event.mouseButton.y);
                break;
            case sf::Event::KeyPressed:
                if(event.key.code == sf::Keyboard::R && event.key.control)
                    board.restart();
                break;
            }
        }

        window.clear();

        board.draw();

        window.display();
    }
    return 0;
}