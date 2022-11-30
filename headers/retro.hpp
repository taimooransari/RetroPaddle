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
        // else
        // {
        //     player_two = new
        // }
    }

    void update()
    {
        player_one->paddle->draw();
        player_two->paddle->draw();
        ball->draw();
        if (isServing)
        {
            ball->setToServe(0);
            player_one->paddle->setToServe(0);
            player_two->paddle->setToServe(0);
        }
        else
        {
            // cout << "moving" << endl;
            ball->moveBall();
            int a = ball->collideFromPaddle(player_one->paddle, player_two->paddle);
            int b = ball->isScored();

            if (b > 0)
            {

                if (b == 1)
                {
                    // player_one->updateScore();
                    ++(*player_one);
                }
                else if (b == 2)
                {
                    ++(*player_two);

                    // player_two->updateScore();
                }

                cout << "p1 " << player_one->score << " p2 " << player_two->score << endl;
                isServing = true;

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
        isServing = false;
        player_one->movepaddle(dir);
    };

    void moveTwo(int dir)
    {
        // isServing = true;
        player_two->movepaddle(dir);
    };
};