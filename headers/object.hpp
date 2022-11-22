#pragma once
#include <SDL.h>
#include "./drawing.hpp"

class Object
{
    SDL_Rect srcRect = {141, 240, 297, 818};
    SDL_Rect moverRect = {10, 10, 25, 100};

public:
    Object();
    void draw()
    {
        SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
    };
};

// class Paddle : public Object
// {
// };

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

// class Ball : public Ball
// {
// };