#pragma once
#include <SDL.h>
#include "./drawing.hpp"
using namespace std;

// Object Class / Abstract Base Class for Paddle and Ball
class Object
{
protected:
    SDL_Rect srcRect, moverRect;

public:
    // Overloaded Constructor
    Object(SDL_Rect s, SDL_Rect m);

    // virtual Destructor to be used by derived class
    virtual ~Object();

    // virtual function to be overridden by Ball Class
    virtual int isScored() { return 0; };

    // virtual function to be overridden by Ball Class
    virtual void collideFromWall(){};

    // virtual function to be overridden by Ball Class
    virtual int collideFromPaddle(Object *p1, Object *p2);

    // Returns the moverRect cordinates of the object
    SDL_Rect getMover();

    // set the object to its serve position
    virtual void setToServe(int);

    // move the paddle along y-axis
    virtual void movePaddle(int){};

    // move the ball along x and y - axis
    virtual void moveBall(){};

    // pure virtual function to draw each object
    virtual void draw() = 0;
};


// Paddle Class -> Derived from Object Class
// Paddle Class / Abstract Base Class for Paddle Types
class Paddle : public Object
{
public:
    // Overloaded Paddle constructor
    Paddle(SDL_Rect s, SDL_Rect m);

    // pure virtual function to be implemented by paddle types
    virtual void draw() = 0;

    // move the paddle according to the direction in parameters
    void movePaddle(int dir);
};

// RegularPaddle Class, paddle has a moderate length and speed.
class RegularPaddle : public Paddle
{
public:
    // Overloaded RegularPaddle constructor
    RegularPaddle(int side = 1, SDL_Rect s = {141, 240, 297, 818}, SDL_Rect m = {10, 315, 30, 90});

    // Using SDL Function to render the paddle
    void draw();

    // move the paddle along y-axis
    void movePaddle(int);
};

// SpeedPaddle Class, paddle has a short length and fast speed.
class SpeedPaddle : public Paddle
{

public:
    // Overloaded RegularPaddle constructor
    SpeedPaddle(int side = 1, SDL_Rect s = {559, 240, 297, 818}, SDL_Rect m = {10, 315, 30, 70});

    // Using SDL Function to render the paddle
    void draw();

    // move the paddle along y-axis
    void movePaddle(int);
};

// SpeedPaddle Class, paddle has a long length and slow speed.
class LongPaddle : public Paddle
{

public:
    // Overloaded RegularPaddle constructor
    LongPaddle(int side = 1, SDL_Rect s = {977, 240, 297, 1090}, SDL_Rect m = {10, 300, 30, 90});

    // Using SDL Function to render the paddle
    void draw();

    // move the paddle along y-axis
    void movePaddle(int);
};

// Ball Class -> Derived from Object Class
class Ball : public Object
{
protected:
    bool onServe;
    int dir;
    int vel_X;
    int vel_Y;

public:
    // Default constructor
    Ball();
    // Draw the Ball using SDL Reder functions
    void draw();
    // Collide the ball from top and bottom walls
    void collideFromWall();
    // Collide from the paddles
    int collideFromPaddle(Object *p1, Object *p2);
    // Check if there is either of the player scored
    int isScored();
    // move the ball along x and y axis
    void moveBall();
    // set the ball to serve position according to the lastHit i.e. who hit the ball last
    void setToServe(int lastHit = 2);
};