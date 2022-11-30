#include <SDL.h>
#include <SDL_mixer.h>
#pragma once
class Drawing
{
public:
    // The window renderer
    static SDL_Renderer *gRenderer;
    // global reference to png image sheets
    static SDL_Texture *assets;

    // bg music
    static Mix_Music *gMusic;

    // The sound effects that will be used
    static Mix_Chunk *gLeft;
    static Mix_Chunk *gRight ;
    static Mix_Chunk *gWall;
    static Mix_Chunk *gScore;
};