#include "Board.hpp"
#include "../Game.hpp"

void Board::mouseMove(const sf::Event::MouseMoveEvent& e)
{
    int x = e.x;
    int y = e.y;

    if(gameOver) return;
    if(clicked_x >= 0 && clicked_y >= 0 && clicked_x < 11 && clicked_y < 11) return;

    x -= pos_x, y -= pos_y;
    x /= tileSize;
    y /= tileSize;

    selected_x = x;
    selected_y = y;

    updateLegals();
}

void Board::updateLegals()
{
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 11; j++)
            legal[i][j] = legalMove(i,j);
}

void Board::mouseClick(const sf::Event::MouseButtonEvent& e)
{
    int x = e.x;
    int y = e.y;

    if(gameOver)
    {
        super.setScene("MainMenu");
        return;
    }

    x -= pos_x, y -= pos_y;
    x /= tileSize;
    y /= tileSize;

    if(clicked_x >= 0 && clicked_y >= 0 && clicked_x < 11 && clicked_y < 11 && legalMove(clicked_x, clicked_y, x, y))
    {
        move(x, y);
            
        clicked_x = -1, clicked_y = -1;
    }
    else
    {
        if(
            (getField(x, y) == Attacker && turn == Defenders) ||
            (getField(x, y) == Defender && turn == Attackers) ||
            (getField(x, y) == King && turn == Attackers) ||
            (getField(x, y) == None)
        ) 
        {
            selected_x = selected_y = clicked_x = clicked_y = -1;
        }
        else
        {
            selected_x = clicked_x = x;
            selected_y = clicked_y = y;
        }
    }
    updateLegals();
}

void Board::move(int to_x, int to_y)
{
    fields[to_x][to_y] = getField(clicked_x, clicked_y);
    fields[clicked_x][clicked_y] = None;

    if((to_x == 0 || to_x == 10) && (to_y == 0 || to_y == 10) && getField(to_x, to_y) == King)
    {
        winDefenders();
        return;
    }

    //check for capture
    Player player = turn;
    Player enemy;
    if(player == Defenders) enemy = Attackers;
    else enemy = Defenders;

    //north
    if(hostileFor(to_x, to_y - 1, player) && (hostileFor(to_x, to_y - 2, enemy) || getField(to_x, to_y - 1) == King))
        capture(to_x, to_y - 1);
    //south
    if(hostileFor(to_x, to_y + 1, player) && (hostileFor(to_x, to_y + 2, enemy) || getField(to_x, to_y + 1) == King))
        capture(to_x, to_y + 1);
    //east
    if(hostileFor(to_x - 1, to_y, player) && (hostileFor(to_x - 2, to_y, enemy) || getField(to_x - 1, to_y) == King))
        capture(to_x - 1, to_y);
    //west
    if(hostileFor(to_x + 1, to_y, player) && (hostileFor(to_x + 2, to_y, enemy) || getField(to_x + 1, to_y) == King))
        capture(to_x + 1, to_y);

    turn = enemy;
}

void Board::capture(int x, int y)
{
    if(getField(x, y) != King)
    {
        fields[x][y] = None;
        return;
    }

    if(
        (x == 0 || hostileFor(x - 1, y, Defenders)) &&
        (x == 10 || hostileFor(x + 1, y, Defenders)) &&
        (y == 0 || hostileFor(x, y - 1, Defenders)) &&
        (y == 10 || hostileFor(x, y + 1, Defenders))
    )
        winAttackers();
}

void Board::keyboardPressed(const sf::Event::KeyEvent& e)
{
    if(e.code == sf::Keyboard::Key::R && e.control)
        init();
}