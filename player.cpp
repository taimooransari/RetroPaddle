#include "./headers/player.hpp"
#include <iostream>

using namespace std;

void Player::operator++()
{
    score++;
}

HumanPlayer::HumanPlayer(int side, int pad_type) : Player()
{

    if (pad_type == 1)

    {
        paddle = new SpeedPaddle(side);
    }
    else if (pad_type == 2)
    {
        paddle = new LongPaddle(side);
    }
    else
    {
        paddle = new RegularPaddle(side);
    }
}

void HumanPlayer::movepaddle(int dir)
{
    paddle->movePaddle(dir);
};

PC::PC(int lvl) : Player()
{
    level = lvl;
    paddle = new RegularPaddle(2);
}

void PC::movepaddle(int dir)
{

    paddle->movePaddle(dir);
};

void PC::decideDirection(SDL_Rect ballDimensions)
{
    SDL_Rect padCord = paddle->getMover();
    int odd = rand() % 100 + 1;
    if (odd >= int(35 / level))
    {
        if ((ballDimensions.y + (ballDimensions.h) / 2 < padCord.y + (padCord.h) / 3))
        {
            movepaddle(-1);
        }
        else if (ballDimensions.y + (ballDimensions.h) / 2 > padCord.y + (padCord.h) / 1.5)
        {
            movepaddle(1);
        }
    }
};