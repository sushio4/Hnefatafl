#include "Board.hpp"

inline Piece Board::getField(int x, int y) 
{
    if(x < 0 || x > 10 || y < 0 || y > 10) return None;

    return fields[x][y];
}

bool Board::hostileFor(int x, int y, Player player)
{
    return ((x == 0 || x == 10) && (y == 0 || y == 10)) ||  //corners
    (player == Attackers && (                                 
        getField(x, y) == Defender || 
        getField(x, y) == King || 
        (x == 5 && y == 5))
    ) ||
    (player == Defenders && (
        getField(x, y) == Attacker ||
        (
            x == 5 && y == 5 &&         //center when theres no king
            getField(5, 5) == None
        )
    ));
}

inline bool Board::canStand(int x, int y)
{
    return((getField(selected_x, selected_y) == King && 
        turn == Defenders && 
        (
            (x == 5 && y == 5) ||
            ((x == 0 || x == 10) && (y == 0 || y == 10))
        )
    ) ||
    (
        getField(x,y) == None &&
        !(x == 5 && y == 5) &&
        !((x == 0 || x == 10) && (y == 0 || y == 10))
    )); 
}

bool Board::legalMove(int to_x, int to_y)
{
    if (selected_x < 0 || selected_x > 10 || selected_y < 0 || selected_y > 10) return false;

    int from_x = selected_x, from_y = selected_y;

    return legalMove(from_x, from_y, to_x, to_y);
}

bool Board::legalMove(int from_x, int from_y, int to_x, int to_y)
{
    Piece piece = getField(from_x, from_y);
    if((piece == Attacker && turn == Defenders) || //checking whose turn it is
        (
            (piece == King || piece == Defender) 
            && turn == Attackers
        ) ||
        piece == None
        )
        return false;

    if( (from_x == to_x && from_y == to_y) ||   //along the lines
        (from_x != to_x && from_y != to_y)
        )
        return false;

    //go along the direction and see whether anything stands on the way
    if(from_x == to_x)
    {
        if(from_y < to_y)
            for(int i = from_y + 1; i <= to_y; i++)
                if(!canStand(from_x, i)) return false;

        if(from_y > to_y)
            for(int i = from_y - 1; i >= to_y; i--)
                if(!canStand(from_x, i)) return false;
    }
    else 
    {
        if(from_x < to_x)
            for(int i = from_x + 1; i <= to_x; i++)
                if(!canStand(i, from_y)) return false;
        
        if(from_x > to_x)
            for(int i = from_x - 1; i >= to_x; i--)
                if(!canStand(i, from_y)) return false;
    }

    return true;
}