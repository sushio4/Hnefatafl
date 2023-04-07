#include "Board.hpp"

void Board::mouseMove(int x, int y)
{
    if(gameOver) return;
    if(clicked_x >= 0 && clicked_y >= 0 && clicked_x < 11 && clicked_y < 11) return;

    x -= pos_x, y -= pos_y;
    x /= tileSize;
    y /= tileSize;

    selected_x = x;
    selected_y = y;

    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 11; j++)
            legal[i][j] = legalMove(i,j);
}

void Board::mouseClick(int x, int y)
{
    if(gameOver)
    {
        restart();
        return;
    }

    x -= pos_x, y -= pos_y;
    x /= tileSize;
    y /= tileSize;

    if(clicked_x >= 0 && clicked_y >= 0 && clicked_x < 11 && clicked_y < 11)
    {
        if(legalMove(clicked_x, clicked_y, x, y)) 
            move(x, y);
            
        clicked_x = -1, clicked_y = -1;
        for(int i = 0; i < 11; i++)
            for(int j = 0; j < 11; j++)
                legal[i][j] = false;
    }
    else
    {
        if(
            (getField(x, y) == Attacker && turn == Defenders) ||
            (getField(x, y) == Defender && turn == Attackers) ||
            (getField(x, y) == King && turn == Attackers) ||
            (getField(x, y) == None)
        ) return;

        clicked_x = x;
        clicked_y = y;
    }
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
    if(hostileFor(to_x, to_y - 1, player) && hostileFor(to_x, to_y - 2, enemy))
        capture(to_x, to_y - 1);
    //south
    if(hostileFor(to_x, to_y + 1, player) && hostileFor(to_x, to_y + 2, enemy))
        capture(to_x, to_y + 1);
    //east
    if(hostileFor(to_x - 1, to_y, player) && hostileFor(to_x - 2, to_y, enemy))
        capture(to_x - 1, to_y);
    //west
    if(hostileFor(to_x + 1, to_y, player) && hostileFor(to_x + 2, to_y, enemy))
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

