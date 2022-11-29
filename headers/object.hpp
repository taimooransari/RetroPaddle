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

    virtual int isScored() { return 0; };
    virtual void collideFromWall(){};
    virtual int collideFromPaddle(Object *p1, Object *p2) { return 0; };
    SDL_Rect getMover() { return moverRect; };
    // virtual void setToServe(int){};

    virtual void setToServe(int side) { moverRect.y = (720 - moverRect.h) / 2; }
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
        if (moverRect.y >= 700 - moverRect.h)
        {
            moverRect.y = 700 - moverRect.h;
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
    bool onServe = true;
    int dir = 1;
    int vel_X = 7;
    int vel_Y = -7;
    Ball() : Object({181, 1419, 215, 215}, {490, 10, 20, 20}){};

    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };

    void collideFromWall()
    {
        vel_Y *= -1;
    }

    int collideFromPaddle(Object *p1, Object *p2)
    {
        // cout << "check collison" << endl;

        // if (moverRect.x <= 10 || moverRect.x + moverRect.w>= 980)
        // {
        //     vel_X *= -1;
        // }
        SDL_Rect padCord = p1->getMover();
        if (moverRect.x <= 40)
        {
            // if ((moverRect.y >= padCord.y && moverRect.y <= padCord.y + padCord.h) || (moverRect.y + moverRect.h >= padCord.y && moverRect.y + moverRect.h <= padCord.y + padCord.h))
            // {
            //     vel_X *= -1;

            //     return 1;
            // }
            if (moverRect.y >= padCord.y && moverRect.y <= padCord.y + padCord.h)
            {
                vel_X *= -1;
                if (moverRect.y <= padCord.y + padCord.h / 3)
                {
                    vel_Y = -7;
                }
                else if (moverRect.y <= padCord.y + padCord.h / 1.5)
                {

                    vel_Y *= rand() % 3 - 1;
                }
                else
                {
                    vel_Y = 7;
                }
                return 1;
            }
            else if (moverRect.y + moverRect.h >= padCord.y && moverRect.y + moverRect.h <= padCord.y + padCord.h)
            {

                vel_X *= -1;
                if (moverRect.y <= padCord.y + padCord.h / 3)
                {
                    vel_Y = -7;
                }
                else if (moverRect.y <= padCord.y + padCord.h / 1.5)
                {

                    vel_Y *= rand() % 3 - 1;
                }
                else
                {
                    vel_Y = 7;
                }
                return 1;
            }

            // if (vel_Y == 0)
            // {
            //     vel_Y = 5;
            // }
            return -1;
        }

        else if (moverRect.x + moverRect.w >= 980)
        {
            padCord = p2->getMover();
            if (moverRect.y >= padCord.y && moverRect.y <= padCord.y + padCord.h)
            {
                vel_X *= -1;
                if (moverRect.y <= padCord.y + padCord.h / 3)
                {
                    vel_Y = -7;
                }
                else if (moverRect.y <= padCord.y + padCord.h / 1.5)
                {

                    vel_Y *= rand() % 3 - 1;
                }
                else
                {
                    vel_Y = 7;
                }
                return 2;
            }
            else if (moverRect.y + moverRect.h >= padCord.y && moverRect.y + moverRect.h <= padCord.y + padCord.h)
            {

                vel_X *= -1;
                if (moverRect.y <= padCord.y + padCord.h / 3)
                {
                    vel_Y = -7;
                }
                else if (moverRect.y <= padCord.y + padCord.h / 1.5)
                {

                    vel_Y *= rand() % 3 - 1;
                }
                else
                {
                    vel_Y = 7;
                }
                return 2;
            }

            // if (vel_Y == 0)
            // {
            //     vel_Y = 5;
            // }
            return -1;
        }

        // setToServe();
        return 0;
    }

    int isScored()
    {
        if (moverRect.x <= 10)
        {

            return 2;
        }
        else if (moverRect.x >= 980)
        {

            return 1;
        }
        return 0;
    }

    void moveBall()
    {
        // if (moverRect.x >= 10 && moverRect.x <= 980)
        // {
        moverRect.x += vel_X;
        moverRect.y += vel_Y;
        // }

        if (moverRect.y <= 10 || moverRect.y >= 700 - moverRect.h)
        {

            collideFromWall();
        }
    }

    void setToServe(int side = 0)
    {
        moverRect.y = (720 - moverRect.h) / 2;
        if (side == 0)
        {
            moverRect.x = 40;
            vel_X = abs(vel_X);
        }
        else
        {
            moverRect.x = 980;
            vel_X = -1 * abs(vel_X);
        }
        onServe = true;
    }
};