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

    void operator++()
    {
        score++;
    }
};

class HumanPlayer : public Player
{

public:
    HumanPlayer(int side, int pad_type) : Player()
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

    void movepaddle(int dir)
    {
        // cout<<"move 2"<<endl;
        paddle->movePaddle(dir);
    };
};

class PC : public Player
{

public:
    void movepaddle();
};
