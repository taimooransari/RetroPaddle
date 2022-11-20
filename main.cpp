// #include "./headers/game.hpp"
#include "window.hpp"
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
// int main(int argc, char *argv[]){
//     Game game;
//     srand(time(NULL));
//     if( !game.init() ){
// 		printf( "Failed to initialize!\n" );
//         return 0;
// 	}
// 		//Load media
//     if( !game.loadMedia() ){
//         printf( "Failed to load media!\n" );
//         return 0;
//     }

//     game.run();
//     game.close();

//     return 0;
// }

// Screen dimension constants
const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 640;

// Starts up SDL and creates window
bool init();

// Frees media and shuts down SDL
void close();

// int TOTAL_WINDOWS = 3;
LWindow gWindows[3];
// vector<LWindow> gWindows;

bool init()
{
    // int TOTAL_WINDOWS = 3;
    // Initialization flag

    bool success = true;

    // Initialize SDL
    if (SDL_Init(SDL_INIT_VIDEO) < 0)
    {
        printf("SDL could not initialize! SDL Error: %s\n", SDL_GetError());
        success = false;
    }
    else
    {
        // Set texture filtering to linear
        if (!SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1"))
        {
            printf("Warning: Linear texture filtering not enabled!");
        }

        // Create window
        if (!gWindows[0].init())
        {
            printf("Window 0 could not be created!\n");
            success = false;
        }
    }

    return success;
}

void close()
{
    // int TOTAL_WINDOWS = 3;
    // Destroy windows
    for (int i = 0; i < 3; ++i)
    {
        gWindows[i].free();
    }

    // Quit SDL subsystems
    SDL_Quit();
}

int main(int argc, char *args[])
{
    // Start up SDL and create window
    if (!init())
    {
        printf("Failed to initialize!\n");
    }
    else
    {
        // Initialize the rest of the windows
        for (int i = 1; i < 3; ++i)
        {
            gWindows[i].init();
        }

        // Main loop flag
        bool quit = false;

        // Event handler
        SDL_Event e;

        // While application is running
        while (!quit)
        {
            // Handle events on queue
            while (SDL_PollEvent(&e) != 0)
            {
                // User requests quit
                if (e.type == SDL_QUIT)
                {
                    quit = true;
                }

                // Handle window events
                for (int i = 0; i < 3; ++i)
                {
                    gWindows[i].handleEvent(e);
                }

                // Pull up window
                if (e.type == SDL_KEYDOWN)
                {
                    switch (e.key.keysym.sym)
                    {
                    case SDLK_1:
                        gWindows[0].focus();
                        break;

                    case SDLK_2:
                        gWindows[1].focus();
                        break;

                    case SDLK_3:
                        gWindows[2].focus();
                        break;
                                       }
                }
            }

            // Update all windows
            for (int i = 0; i < 3; ++i)
            {
                gWindows[i].render();
            }

            // Check all windows
            bool allWindowsClosed = true;
            for (int i = 0; i < 3; ++i)
            {
                if (gWindows[i].isShown())
                {
                    allWindowsClosed = false;
                    break;
                }
            }

            // Application closed all windows
            if (allWindowsClosed)
            {
                quit = true;
            }
        }
    }

    // Free resources and close SDL
    close();

    return 0;
}