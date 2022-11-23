#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vector>
#include "./object.hpp"
#include "./drawing.hpp"

class Game
{
    // Screen dimension constants
    const int SCREEN_WIDTH = 680 * 1.5;
    const int SCREEN_HEIGHT = 480 * 1.5;

    // vector <SDL_Window*> winds;

    // The window we'll be rendering to
    SDL_Window *gWindow = NULL;

    // Current displayed texture
    SDL_Texture *gTexture = NULL;

    // Current displayed texture
    // SDL_Texture *paddleTexture = NULL;

    int state = 0;

    bool gameRunning = false;

    // Object obj;
    // 0 for mainpage
    // 1 for instructions
    // 2 for mode
    // 3 for 1player -  for easy/medium/hard
    // 4 for 2player  - 5 for paddle types

    //  6 for 1player match
    // 7 for 2payer match
public:
    bool init();
    bool loadMedia();
    void close();
    SDL_Texture *loadTexture(std::string path);
    void run();
};
