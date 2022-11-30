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
    bool isServing = true;
    bool isPC = false;
    bool onWait = false;
    int lastHit = 2;

public:
    Retro()
    {
        player_one = new HumanPlayer(1, 3);
        player_two = new PC();
        ball = new Ball();
        isRunning = true;
        isServing = true;
    };

    Retro(int mode, int level, int pad1, int pad2)
    {

        cout << "mode: " << mode << endl;
        cout << "lvl: " << level << endl;
        cout << "p1: " << pad1 << endl;
        cout << "p2: " << pad2 << endl;

        ball = new Ball();
        isRunning = true;
        player_one = new HumanPlayer(1, pad1);
        if (mode == 2)
        {
            player_two = new HumanPlayer(2, pad2);
        }
        else
        {
            isPC = true;
            player_two = new PC();
        }
    }

    void update()
    {
        onWait = false;
        if (isPC && !onWait)
        {
            player_two->decideDirection(ball->getMover());
        }

        player_one->paddle->draw();
        player_two->paddle->draw();
        ball->draw();
        if (isServing)
        {
            ball->setToServe(lastHit);
            player_one->paddle->setToServe(0);
            player_two->paddle->setToServe(0);
        }
        else
        {
            ball->moveBall();
            int a = ball->collideFromPaddle(player_one->paddle, player_two->paddle);
            int b = ball->isScored();
            if (b != 0)
            {
                lastHit = b;
            }

            if (isPC)
            {
                lastHit = 2;
            }

            if (a == 2)
            {
                onWait = true;
            }
            else if (a == 1)
            {
                onWait = false;
            }

            if (b > 0)
            {

                if (b == 1)
                {
                    ++(*player_one);
                }
                else if (b == 2)
                {
                    ++(*player_two);
                }

                cout << "p1 " << player_one->score << " p2 " << player_two->score << endl;
                isServing = true;
                onWait = false;
                SDL_Delay(700);
            }
        }
    };

    int declareResult()
    {

        if (player_one->score >= 10)
        {
            isRunning = false;
            return 1;
        }
        else if (player_one->score >= 10)
        {
            isRunning = false;
            return 2;
        }

        return 0;
    }

    void moveOne(int dir)
    {
        if (!isServing)
        {
            player_one->movepaddle(dir);
        }
        if (lastHit == 2)
        {
            isServing = false;
        }
    };

    void moveTwo(int dir)
    {
        if (!isPC)
        {
            if (!isServing)
            {
                player_two->movepaddle(dir);
            }
            if (lastHit == 1)
            {
                isServing = false;
            }
        }
    };
};