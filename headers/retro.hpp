#include <iostream>
#include "object.hpp"
#include "player.hpp"
// using namespace std;

class Retro
{
    Player *player_one;
    Player *player_two;
    Object *ball;
    bool isRunning;

public:
    Retro()
    {
        player_one = new HumanPlayer(1);
        player_two = new HumanPlayer(2);
        ball = new Ball();
        isRunning = true;
    };
    void draw()
    {
        player_one->paddle->draw();
        player_two->paddle->draw();
        ball->moveBall();
        ball->draw();
    };

    void moveOne(int dir)
    {
        player_one->movepaddle(dir);
    };

    void moveTwo(int dir)
    {
        player_two->movepaddle(dir);
    };

    void declareResult()
    {
        isRunning = false;
    };
};