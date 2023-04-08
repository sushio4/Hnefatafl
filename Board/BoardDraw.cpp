#include "Board.hpp"
#include <cmath>

void Board::draw() 
{
    for(int x = 0; x < 11; x++)
        for(int y = 0; y < 11; y++)
        {
            drawField(x, y);
            drawPiece(x, y);
        }
    
    if(gameOver)
    {
        sf::RectangleShape rect(sf::Vector2f(size/2, 170));
        rect.setPosition(size/4, size/4);
        rect.setFillColor(sf::Color(0xBA, 0x4A, 0x00));
        window.draw(rect);

        sf::Text text;
        text.setCharacterSize(30);
        text.setFillColor(sf::Color::White);
        text.setStyle(sf::Text::Bold);
        text.setFont(font);

        text.setString("GAME OVER");
        text.setPosition(size/4 + 30, size/4 + 30);
        window.draw(text);

        if(winner == Attackers)
            text.setString("ATTACKERS WON");
        else
            text.setString("DEFENDERS WON");
        text.setPosition(size/4 + 30, size/4 + 70);
        window.draw(text);

        text.setString("Click anywhere to exit");
        text.setPosition(size/4 + 30, size/4 + 110);
        window.draw(text);
    }
}

void Board::drawField(int x, int y)
{
    sf::RectangleShape rect(sf::Vector2f(tileSize - 2, tileSize - 2));
    if(x == clicked_x && y == clicked_y)
        rect.setFillColor(sf::Color(0xF3, 0x9C, 0x12));
    else if(legal[x][y]) 
        rect.setFillColor(sf::Color(0x78, 0x42, 0x12));
    else
        rect.setFillColor(sf::Color(0x6E, 0x2C, 0x00));
    rect.setPosition(pos_x + x * tileSize + 1, pos_y + y * tileSize + 1);

    window.draw(rect);

    if((x == 0 || x == 10) && (y == 0 || y == 10))
    {
        double sqrt2 = sqrt(2);
        sf::RectangleShape line(sf::Vector2f(sqrt2 * (tileSize - 9), 5));
        line.setFillColor(sf::Color(0x93, 0x51, 0x16));
        line.rotate(45);
        line.setPosition(pos_x + x * tileSize + 7, pos_y + y * tileSize + 3);
        window.draw(line);
        line.rotate(90);
        line.setPosition(pos_x + (x + 1) * tileSize - 2, pos_y + y * tileSize + 6);
        window.draw(line);
    }

    if(x == 5 && y == 5)
    {
        sf::RectangleShape line(sf::Vector2f(6, tileSize - 2));
        line.setFillColor(sf::Color(0x93, 0x51, 0x16));
        line.setPosition(pos_x + (x + 0.5) * tileSize - 3, pos_y + y * tileSize + 1);
        window.draw(line);
        line.rotate(-90);
        line.setPosition(pos_x + x * tileSize + 1, pos_y + (y + 0.5) * tileSize + 3);
        window.draw(line);
    }
}

void Board::drawPiece(int x, int y)
{
    if(getField(x,y) == None) return;

    sf::CircleShape circle(0.4 * tileSize);
    circle.setPosition(pos_x + (x + 0.1) * tileSize, pos_y + (y + 0.1) * tileSize);
    
    switch(getField(x,y))
    {
    case Attacker:
        circle.setFillColor(sf::Color::Black);
        break;
    case Defender:
        circle.setFillColor(sf::Color::White);
        break;
    case King:
        circle.setFillColor(sf::Color::Yellow);
        break;
    }

    window.draw(circle);
}