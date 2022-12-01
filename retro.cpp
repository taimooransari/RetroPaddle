#include "./headers/retro.hpp"
#include <iostream>
using namespace std;
Retro::Retro()
{
    player_one = new HumanPlayer(1, 3);
    player_two = new PC();
    ball = new Ball();
    isServing = true;
    isPC = true;
    onWait = false;
    lastHit = 2;
};

Retro::Retro(int mode, int level, int pad1, int pad2)
{

    isServing = true;
    onWait = false;
    lastHit = 2;
    ball = new Ball();
    player_one = new HumanPlayer(1, pad1);
    if (mode == 2)
    {
        isPC = false;
        player_two = new HumanPlayer(2, pad2);
    }
    else
    {
        isPC = true;
        player_two = new PC(level);
    }
}

Retro::~Retro()
{
    //
    //
    //
}

void Retro::update()
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

int Retro::declareResult()
{

    if (player_one->score >= 10)
    {

        return 1;
    }
    else if (player_one->score >= 10)
    {

        return 2;
    }

    return 0;
}

void Retro::moveOne(int dir)
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

void Retro::moveTwo(int dir)
{
    cout << 1 << endl;
    if (!isPC)
    {
        cout << 2 << endl;
        if (!isServing)
        {
            cout << 3 << endl;
            player_two->movepaddle(dir);
        }
        if (lastHit == 1)
        {
            cout << 4 << endl;
            isServing = false;
        }
    }
};