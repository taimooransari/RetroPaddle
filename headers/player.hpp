#include "object.hpp"
#include <SDL.h>
class Player
{

public:
    Object *paddle;
    int score = 0;

    Player(){};
    virtual void movepaddle(int dir) = 0;
    void updateScore() { score++; };
};

class HumanPlayer : public Player
{

public:
    HumanPlayer(int side, int pad_type) : Player()
    {
        // SDL_Rect s;
        // SDL_Rect m;
        // if (side == 1)
        // {
        //     s = {141, 240, 297, 818};
        //     m = {10, 10, 40, 120};
        // }
        // else
        // {
        //     s = {559, 240, 297, 818};
        //     m = {970, 10, 40, 120};
        // }

        // if (pad_type == 1)
        // {
        //     paddle = new Paddle(s, m);
        // }
        // else if (pad_type == 2)
        // {
        //     paddle = new Paddle(s, m);
        // }
        // else
        // {
        //     paddle = new Paddle(s, m);
        // }

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

    void movepaddle(int dir)
    {
        // cout<<"move 2"<<endl;
        paddle->movePaddle(dir);
    };
};

// class PC : public Player
// {

// public:
//     void movepaddle();
// };
