#pragma once
#include <SDL.h>
#include "./drawing.hpp"
using namespace std;
class Object
{
protected:
    SDL_Rect srcRect, moverRect;

public:
    Object(SDL_Rect s, SDL_Rect m)
    {
        srcRect = s;
        moverRect = m;
    };
    virtual void movePaddle(int){};
    virtual void moveBall(){};
    virtual void draw() = 0;
};

class Paddle : public Object
{
public:
    Paddle(SDL_Rect s = {141, 240, 297, 818}, SDL_Rect m = {10, 10, 40, 120}) : Object(s, m){};

    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };

    void movePaddle(int dir)
    {
        // cout << moverRect.y << endl;
        moverRect.y += 5 * dir;
        if (moverRect.y <= 10)
        {
            moverRect.y = 10;
        }
        if (moverRect.y >= 560)
        {
            moverRect.y = 560;
        }
    }
};

// class FastPaddle : public Paddle
// {
// };

// class FastPaddle : public Paddle
// {
// };

// class SpeedPaddle : public Paddle
// {
// };

// class LongPaddle : public Paddle
// {
// };

class Ball : public Object
{
public:
    int dir = 1;
    Ball() : Object({559, 240, 297, 818 / 3}, {490, 10, 30, 30}){};

    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };
    void moveBall()
    {
        moverRect.y += 8 * dir;
        if (moverRect.y <= 10)
        {
            moverRect.y = 10;
            dir *= -1;
        }
        if (moverRect.y >= 610)
        {
            dir *= -1;
            moverRect.y = 610;
        }
    }
};