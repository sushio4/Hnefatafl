#pragma once
#include <SFML/Graphics.hpp>
#include "Scene.hpp"

enum Piece {
    None,
    Attacker,
    Defender,
    King
};

enum Player {
    Attackers,
    Defenders
};

class Board : public Scene
{
public:
    Board(std::string name, Game& super, sf::RenderWindow &window, int posx, int posy, int size);

    void draw();

    void mouseMove(const sf::Event::MouseMoveEvent& e);
    void mouseClick(const sf::Event::MouseButtonEvent& e);
    void keyboardPressed(const sf::Event::KeyEvent& e);

private:
    void drawField(int x, int y);
    void drawPiece(int x, int y);
    inline Piece getField(int x, int y);

    inline bool canStand(int x, int y);
    bool hostileFor(int x, int y, Player player);
    bool legalMove(int to_x, int to_y);
    bool legalMove(int from_x, int from_y, int to_x, int to_y);

    void move(int to_x, int to_y);
    void capture(int x, int y);

    void restart();
    void winAttackers();
    void winDefenders();

    sf::RenderWindow &window;
    sf::Font font;
    int pos_x, pos_y, size;

    //helper
    int tileSize;

    Piece fields[11][11] = {Piece::None};
    bool legal[11][11] = {false};

    int selected_x = -1, selected_y = -1;
    int clicked_x = -1, clicked_y = -1;
    Player turn = Player::Attackers;

    bool gameOver = false;
    Player winner = Player::Attackers;
};