#include "./headers/game.hpp"

#include <SDL.h>
#include <SDL_image.h>
#include <stdio.h>
#include <string>
#include <sstream>
using namespace std;
// Main function
int main(int argc, char *argv[])
{
    Game game;
    srand(time(NULL));
    if (!game.init())
    {
        printf("Failed to initialize!\n");
        return 0;
    }
    // Load media
    if (!game.loadMedia())
    {
        printf("Failed to load media!\n");
        return 0;
    }

    game.run();
    game.close();

    return 0;
}
