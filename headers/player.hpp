#include "object.hpp"
#include <SDL.h>

// Player Class / Abstract Base Class for Human and PC
class Player
{

public:
    Object *paddle;
    int score = 0;
    SDL_Rect src;
    SDL_Rect mov ;//= {450, 20, 40, 40};

    // Default constructor
    Player();

    // Virtual destructor to be implemented by derived classes
    virtual ~Player();

    // move the paddle of the player
    virtual void movepaddle(int dir) = 0;

    // move the paddle of the PC according to Ball
    virtual void decideDirection(SDL_Rect ballDimension){};

    // Operator overloading for score update
    void operator++();

    // Render the score of the player
    void viewScore(int xPos = 1);
};

// HumanPlayer Class -> Derived from Player Class
class HumanPlayer : public Player
{

public:
    // Overloaded constructor
    HumanPlayer(int side, int pad_type);

    // Move the paddle for the player
    void movepaddle(int dir);
};

// PC Class -> Derived from Player Class
class PC : public Player
{
protected:
    int level;

public:
    // Overloaded constructor
    PC(int lvl = 1);

    // Move the paddle for the player
    void movepaddle(int dir);

    // Decide the movement for PC Paddle according to Ball
    void decideDirection(SDL_Rect ballDimensions);
};
