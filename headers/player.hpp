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
    HumanPlayer(int side) : Player()
    {
        SDL_Rect s;
        SDL_Rect m;
        if (side == 1)
        {
            s = {141, 240, 297, 818};
            m = {10, 10, 40, 120};
        }
        else
        {
            s = {141, 240, 297, 818};
            m = {970, 10, 40, 120};
        }

        paddle = new Paddle(s, m);
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
