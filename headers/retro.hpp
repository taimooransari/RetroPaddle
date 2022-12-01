#include <iostream>
#include "object.hpp"
#include "player.hpp"
// using namespace std;

class Retro
{
    Player *player_one;
    Player *player_two;
    Object *ball;
    // bool isRunning;
    bool isServing;
    bool isPC;
    bool onWait;
    int lastHit;

public:
    Retro();

    Retro(int, int, int, int);
    ~Retro();
    

    void update();
   

    int declareResult();
   
    void moveOne(int);
   

    void moveTwo(int);
    
};