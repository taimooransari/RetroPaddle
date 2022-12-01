#include "object.hpp"
#include <SDL.h>
class Player
{

public:
    Object *paddle;
    int score = 0;

    Player(){};
    virtual void movepaddle(int dir) = 0;
    // void updateScore() { score++; };
    virtual void decideDirection(SDL_Rect ballDimension){};
    void operator++();
    // {
    //     score++;
    // }
};

class HumanPlayer : public Player
{

public:
    HumanPlayer(int side, int pad_type);
    // : Player()
    // {

    //     if (pad_type == 1)

    //     {
    //         paddle = new SpeedPaddle(side);
    //     }
    //     else if (pad_type == 2)
    //     {
    //         paddle = new LongPaddle(side);
    //     }
    //     else
    //     {
    //         paddle = new RegularPaddle(side);
    //     }
    // }

    void movepaddle(int dir);
    // {
    //     paddle->movePaddle(dir);
    // };
};

class PC : public Player
{
public:
    int level;
    PC(int lvl=1);
    // : Player()
    // {
    //     level = lvl;
    //     paddle = new RegularPaddle(2);
    // }
    void movepaddle(int dir);
    // {

    //     paddle->movePaddle(dir);
    // };
    void decideDirection(SDL_Rect ballDimensions);
    // {
    //     SDL_Rect padCord = paddle->getMover();
    //     int odd = rand() % 100 + 1;
    //     if (odd >= int(35 / level))
    //     {
    //         if ((ballDimensions.y + (ballDimensions.h) / 2 < padCord.y + (padCord.h) / 3))
    //         {
    //             movepaddle(-1);
    //         }
    //         else if (ballDimensions.y + (ballDimensions.h) / 2 > padCord.y + (padCord.h) / 1.5)
    //         {
    //             movepaddle(1);
    //         }
    //     }
    // };
}

;
