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
    bool isServing;

public:
    Retro()
    {
        player_one = new HumanPlayer(1, 1);
        player_two = new HumanPlayer(2, 1);
        ball = new Ball();
        isRunning = true;
        isServing = true;
    };

    Retro(int mode, int level, int pad1, int pad2)
    {

        ball = new Ball();
        isRunning = true;
        player_one = new HumanPlayer(1, pad1);
        if (mode == 2)
        {
            player_two = new HumanPlayer(2, pad2);
        }

        cout << "game: " << mode << endl;
        cout << "level: " << level << endl;
        cout << "pad1: " << pad1 << endl;
        cout << "pad2: " << pad2 << endl;

        // else
        // {
        // player_two
        // }
    }

    void update()
    {
        player_one->paddle->draw();
        player_two->paddle->draw();
        ball->draw();
        if (isServing)
        {
            ball->setToServe(1);
        }
        else
        {

            ball->moveBall();
        }
    };

    void moveOne(int dir)
    {
        isServing = false;
        player_one->movepaddle(dir);
    };

    void moveTwo(int dir)
    {
        isServing = true;
        player_two->movepaddle(dir);
    };

    void declareResult()
    {
        isRunning = false;
    };
};