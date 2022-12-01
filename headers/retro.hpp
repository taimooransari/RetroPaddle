#include <iostream>
#include "object.hpp"
#include "player.hpp"

class Retro
{
protected:
    Player *player_one;
    Player *player_two;
    Object *ball;

    bool isServing;
    bool isPC;
    bool onWait;
    int lastHit;

public:
    // Default constructor
    Retro();

    // Overloaded destructor
    Retro(int, int, int, int);

    // Destructor
    ~Retro();

    // update game dynamics according to game logic
    void update();

    // declare the game's result
    int declareResult();

    // move player one's paddle
    void moveOne(int);

    // move player two's paddle
    void moveTwo(int);
};