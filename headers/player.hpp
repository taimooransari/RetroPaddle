#include "object.hpp"
#include <SDL.h>
class Player
{

public:
    Object *paddle;
    int score = 0;
    SDL_Rect src;
    SDL_Rect mov = {450, 20, 40, 40};
    ;
    Player(){};
    virtual ~Player();
    virtual void movepaddle(int dir) = 0;
    // void updateScore() { score++; };
    virtual void decideDirection(SDL_Rect ballDimension){};
    void operator++();
    void viewScore(int xPos = 1)
    {
        if (xPos == 2)
        {
            mov.x = 530;
        }
        switch (score)
        {
        case 0:
            src = {710,
                   381,
                   102,
                   134};

            break;
        case 1:
            src = {81, 95, 83, 130};

            break;
        case 2:
            src =
                {220, 93, 84, 132};

            break;
        case 3:
            src = {361, 93, 89, 134};
            break;
        case 4:
            src = {504,95,99,130};
            break;
        case 5:
            src = {664,95,88,132};
            break;
        case 6:
            src = {75,381,93,134};
            break;
        case 7:
            src = {222,383,80,130};
            break;
        case 8:
            src = {366,381,91,134};
            break;
        case 9:
            src = {517,381,93,134};
            break;
        default:
            src = {710,
                   381,
                   102,
                   134};
            break;
        }




        SDL_RenderCopy(Drawing::gRenderer, Drawing::scoreAsset, &src, &mov);
    }
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
    PC(int lvl = 1);
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
