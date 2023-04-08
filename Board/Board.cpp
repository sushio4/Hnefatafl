#include "Board.hpp"

Board::Board(std::string name, Game& super, sf::RenderWindow &window, int posx, int posy, int size) : Scene(name, super, window),
        size(size), pos_x(posx), pos_y(posy), tileSize(size / 11)
{
    font.loadFromFile("default.otf");
    
    init();
}

void Board::init()
{
    //set up tiles
    for(int i = 0; i < 11; i++)
        for(int j = 0; j < 11; j++)
            legal[i][j] = false, fields[i][j] = None;

    for (int i = 3; i < 8; i++)
    {
        fields[i][0] = Attacker;
        fields[i][10] = Attacker;
        fields[0][i] = Attacker;
        fields[10][i] = Attacker;

        fields[5][i] = Defender;
        fields[i][5] = Defender;
    }

    fields[5][1] = fields[1][5] = fields[9][5] = fields[5][9] = Attacker;

    fields[4][4] = fields[6][4] = fields[4][6] = fields[6][6] = Defender;
    fields[5][5] = King;

    turn = Attackers;
    gameOver = false;
    selected_x = selected_y = clicked_x = clicked_y = -1;
}

void Board::winAttackers()
{
    gameOver = true;
    winner = Attackers;
}

void Board::winDefenders()
{
    gameOver = true;
    winner = Defenders;
}