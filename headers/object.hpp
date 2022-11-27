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
    virtual void setToServe(int){};
    virtual void movePaddle(int){};
    virtual void moveBall(){};
    virtual void draw() = 0;
};

class Paddle : public Object
{
public:
    Paddle(SDL_Rect s, SDL_Rect m) : Object(s, m){};

    virtual void draw() = 0;

    void movePaddle(int dir)
    {

        moverRect.y += 4 * dir;
        if (moverRect.y <= 10)
        {
            moverRect.y = 10;
        }
        if (moverRect.y >= 670 - moverRect.h)
        {
            moverRect.y = 670 - moverRect.h;
        }
    }
};

// regular = {141,240,297,818}
// fast = {559, 240, 297, 818}
// long = {977,240,297,1090}

class RegularPaddle : public Paddle
{
public:
    RegularPaddle(int side = 1, SDL_Rect s = {141, 240, 297, 818}, SDL_Rect m = {10, 315, 30, 90}) : Paddle(s, m)
    {
        moverRect.y = (720 - moverRect.h) / 2;
        if (side == 2)
        {
            moverRect.x = 980;
        }
    }
    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };
    void movePaddle(int dir)
    {
        Paddle::movePaddle((int)(dir * 2));
    }
};

class SpeedPaddle : public Paddle
{

public:
    SpeedPaddle(int side = 1, SDL_Rect s = {559, 240, 297, 818}, SDL_Rect m = {10, 315, 30, 70}) : Paddle(s, m)
    {
        moverRect.y = (720 - moverRect.h) / 2;
        if (side == 2)
        {
            moverRect.x = 980;
        }
    }
    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };
    void movePaddle(int dir)
    {

        Paddle::movePaddle((int)(dir * 3));
    }
};

class LongPaddle : public Paddle
{

public:
    LongPaddle(int side = 1, SDL_Rect s = {977, 240, 297, 1090}, SDL_Rect m = {10, 300, 30, 90}) : Paddle(s, m)
    {
        moverRect.h = 120;
        moverRect.y = (720 - moverRect.h) / 2;
        if (side == 2)
        {
            moverRect.x = 980;
        }
    }
    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };

    void movePaddle(int dir)
    {

        Paddle::movePaddle((int)(dir));
    }
};

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
        if (moverRect.y >= 670)
        {
            dir *= -1;
            moverRect.y = 670;
        }
    }

    void setToServe(int side)
    {
        moverRect.y = (720 - moverRect.h) / 2;
        moverRect.x = 40;
    }
};