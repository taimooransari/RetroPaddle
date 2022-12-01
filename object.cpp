// #pragma once
// #include <SDL.h>
#include "./headers/object.hpp"

// object
Object::Object(SDL_Rect s, SDL_Rect m)
{
    srcRect = s;
    moverRect = m;
};

SDL_Rect Object::getMover() { return moverRect; };

void Object::setToServe(int side) { moverRect.y = (720 - moverRect.h) / 2; }
int Object::collideFromPaddle(Object *p1, Object *p2) { return 0; }

Object::~Object() {}

// paddle
Paddle::Paddle(SDL_Rect s, SDL_Rect m) : Object(s, m){};

void Paddle::movePaddle(int dir)
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

// reg pad

RegularPaddle::RegularPaddle(int side, SDL_Rect s, SDL_Rect m) : Paddle(s, m)
{
    moverRect.y = (720 - moverRect.h) / 2;
    if (side == 2)
    {
        moverRect.x = 980;
    }
}

void RegularPaddle::draw()
{
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
};
void RegularPaddle::movePaddle(int dir)
{
    Paddle::movePaddle((int)(dir * 2));
}

// speed pad

SpeedPaddle::SpeedPaddle(int side, SDL_Rect s, SDL_Rect m) : Paddle(s, m)
{
    moverRect.y = (720 - moverRect.h) / 2;
    if (side == 2)
    {
        moverRect.x = 980;
    }
}
void SpeedPaddle::draw()
{
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
};
void SpeedPaddle::movePaddle(int dir)
{

    Paddle::movePaddle((int)(dir * 3));
}

// long paddle

LongPaddle::LongPaddle(int side, SDL_Rect s, SDL_Rect m) : Paddle(s, m)
{
    moverRect.h = 120;
    moverRect.y = (720 - moverRect.h) / 2;
    if (side == 2)
    {
        moverRect.x = 980;
    }
}
void LongPaddle::draw()
{
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
};

void LongPaddle::movePaddle(int dir)
{

    Paddle::movePaddle((int)(dir));
}

// balll

Ball::Ball() : Object({181, 1419, 215, 215}, {490, 10, 20, 20})
{

    onServe = true;
    dir = 1;
    vel_X = 7;
    vel_Y = -7;
};

void Ball::draw()
{
    SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
};

void Ball::collideFromWall()
{
    vel_Y *= -1;
    int rnd = rand() % 2;
    if (rnd == 0)
    {
        Mix_PlayChannel(-1, Drawing::gLeft, 0);
    }
    else
    {

        Mix_PlayChannel(-1, Drawing::gRight, 0);
    }
}

int Ball::collideFromPaddle(Object *p1, Object *p2)
{

    SDL_Rect padCord = p1->getMover();
    if (moverRect.x >= 35 && moverRect.x <= 40)
    {

        if (moverRect.y >= padCord.y && moverRect.y <= padCord.y + padCord.h)
        {
            vel_X *= -1;
            if (moverRect.y <= padCord.y + padCord.h / 3)
            {
                vel_Y = -7;
            }
            else if (moverRect.y <= padCord.y + padCord.h / 1.5)
            {

                vel_Y = 7 * (rand() % 3 - 1);
            }
            else
            {
                vel_Y = 7;
            }

            int rnd = rand() % 2;
            if (rnd == 0)
            {
                Mix_PlayChannel(-1, Drawing::gLeft, 0);
            }
            else
            {

                Mix_PlayChannel(-1, Drawing::gRight, 0);
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

                vel_Y = 7 * (rand() % 3 - 1);
            }
            else
            {
                vel_Y = 7;
            }

            int rnd = rand() % 2;
            if (rnd == 0)
            {
                Mix_PlayChannel(-1, Drawing::gLeft, 0);
            }
            else
            {

                Mix_PlayChannel(-1, Drawing::gRight, 0);
            }
            return 1;
        }

        return -1;
    }

    else if (moverRect.x + moverRect.w >= 980 && moverRect.x + moverRect.w <= 985)
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

                vel_Y = 7 * (rand() % 3 - 1);
            }
            else
            {
                vel_Y = 7;
            }

            int rnd = rand() % 2;
            if (rnd == 0)
            {
                Mix_PlayChannel(-1, Drawing::gLeft, 0);
            }
            else
            {

                Mix_PlayChannel(-1, Drawing::gRight, 0);
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

                vel_Y = 7 * (rand() % 3 - 1);
            }
            else
            {
                vel_Y = 7;
            }
            int rnd = rand() % 2;
            if (rnd == 0)
            {
                Mix_PlayChannel(-1, Drawing::gLeft, 0);
            }
            else
            {

                Mix_PlayChannel(-1, Drawing::gRight, 0);
            }
            return 2;
        }

        return -1;
    }

    return 0;
}

int Ball::isScored()
{
    if (moverRect.x <= 10)
    {
        Mix_PlayChannel(-1, Drawing::gScore, 0);

        setToServe(2);
        return 2;
    }
    else if (moverRect.x >= 980)
    {

        Mix_PlayChannel(-1, Drawing::gScore, 0);
        setToServe(1);
        return 1;
    }
    return 0;
}

void Ball::moveBall()
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

void Ball::setToServe(int lastHit)
{
    moverRect.y = (720 - moverRect.h) / 2;
    if (lastHit == 2)
    {
        moverRect.x = 40;
        vel_X = abs(vel_X);
    }
    else if (lastHit == 1)
    {
        moverRect.x = 960;
        vel_X = -1 * abs(vel_X);
    }
    onServe = true;
}
