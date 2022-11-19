#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <stdlib.h>
#include <time.h>
#include <vectors>

class Game{
    //Screen dimension constants
    const int SCREEN_WIDTH = 680*1.5;
    const int SCREEN_HEIGHT = 480*1.5;

    // vector <SDL_Window*> winds;

    //The window we'll be rendering to
    SDL_Window* gWindow = NULL;

    //Current displayed texture
    SDL_Texture* gTexture = NULL;
    

public:



    bool init();
    bool loadMedia();
    void close();
    SDL_Texture* loadTexture( std::string path );
    void run();
};

