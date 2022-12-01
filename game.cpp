#include "./headers/game.hpp"
#include "./headers/drawing.hpp"
#include "./headers/retro.hpp"
#include <iostream>
#include <SDL_mixer.h>
using namespace std;
SDL_Renderer *Drawing::gRenderer = NULL;
SDL_Texture *Drawing::assets = NULL;
SDL_Texture *Drawing::scoreAsset = NULL;


Mix_Chunk *Drawing::gLeft = NULL;
Mix_Chunk *Drawing::gRight = NULL;
Mix_Chunk *Drawing::gButton = NULL;
Mix_Chunk *Drawing::gScore = NULL;
Mix_Music *Drawing::gMusic = NULL;

bool Game::init()
{
	// Initialization flag
	bool success = true;

	// obj = Object();
	// Initialize SDL
	if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0)
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
		gWindow = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{

			// Create renderer for window
			// Drawing::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);
			Drawing::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);

			if (Drawing::gRenderer == NULL)
			{
				printf("Renderer could not be created! SDL Error: %s\n", SDL_GetError());
				success = false;
			}
			else
			{
				// Initialize renderer color
				SDL_SetRenderDrawColor(Drawing::gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);

				// Initialize PNG loading
				int imgFlags = IMG_INIT_PNG;
				if (!(IMG_Init(imgFlags) & imgFlags))
				{
					printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
					success = false;
				}
				// Initialize SDL_mixer
				if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0)
				{
					printf("SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError());
					success = false;
				}
			}
		}
	}

	return success;
}

bool Game::loadMedia()
{
	// Loading success flag
	bool success = true;
	Drawing::assets = loadTexture("./assets/paddles.png");
	Drawing::scoreAsset = loadTexture("./assets/score.png");

	gTexture = loadTexture("./assets/main.png");

	if (gTexture == NULL || Drawing::assets == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}

	// Load music
	Drawing::gMusic = Mix_LoadMUS("./assets/ost/game.wav");
	if (Drawing::gMusic == NULL)
	{
		printf("Failed to load beat music! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Load sound effects
	Drawing::gLeft = Mix_LoadWAV("./assets/ost/ping.ogg");
	if (Drawing::gLeft == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Load sound effects
	Drawing::gRight = Mix_LoadWAV("./assets/ost/pong.ogg");
	if (Drawing::gRight == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Load sound effects
	Drawing::gButton = Mix_LoadWAV("./assets/ost/hit_paddle.wav");
	if (Drawing::gButton == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	// Load sound effects
	Drawing::gScore = Mix_LoadWAV("./assets/ost/score.wav");
	if (Drawing::gButton == NULL)
	{
		printf("Failed to load scratch sound effect! SDL_mixer Error: %s\n", Mix_GetError());
		success = false;
	}

	return success;
}

void Game::close()
{
	// Free loaded images

	SDL_DestroyTexture(gTexture);

	// Free the sound effects
	Mix_FreeChunk(Drawing::gLeft);
	Mix_FreeChunk(Drawing::gRight);
	Mix_FreeChunk(Drawing::gButton);
	// Mix_FreeChunk(Drawing::gScore);
	Drawing::gLeft = NULL;
	Drawing::gRight = NULL;
	Drawing::gButton = NULL;
	// Drawing::gScore = NULL;

	// Free the music
	Mix_FreeMusic(Drawing::gMusic);
	Drawing::gMusic = NULL;

	// Destroy window
	SDL_DestroyRenderer(Drawing::gRenderer);
	SDL_DestroyWindow(gWindow);
	gWindow = NULL;
	Drawing::gRenderer = NULL;
	// Quit SDL subsystems
	IMG_Quit();
	SDL_Quit();
}

SDL_Texture *Game::loadTexture(std::string path)
{
	// The final texture
	SDL_Texture *newTexture = NULL;

	// Load image at specified path
	SDL_Surface *loadedSurface = IMG_Load(path.c_str());
	if (loadedSurface == NULL)
	{
		printf("Unable to load image %s! SDL_image Error: %s\n", path.c_str(), IMG_GetError());
	}
	else
	{
		// Create texture from surface pixels
		newTexture = SDL_CreateTextureFromSurface(Drawing::gRenderer, loadedSurface);
		if (newTexture == NULL)
		{
			printf("Unable to create texture from %s! SDL Error: %s\n", path.c_str(), SDL_GetError());
		}

		// Get rid of old loaded surface
		SDL_FreeSurface(loadedSurface);
	}

	return newTexture;
}
void Game::run()
{
	bool wasStarted = false;
	bool quit = false;
	SDL_Event e;
	Retro *game;
	bool p1_up = false, p1_down = false, p2_up = false, p2_down = false;
	int mode;
	int level;
	int p1_pad;
	int p2_pad;
	// test end

	// Play the music
	Mix_PlayMusic(Drawing::gMusic, 99);
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

			if (e.type == SDL_KEYDOWN)
			{
				switch (e.key.keysym.sym)
				{
				case SDLK_9:

					Mix_PlayChannel(-1, Drawing::gButton, 0);
					// If there is no music playing
					if (Mix_PlayingMusic() == 0)
					{

						// Play the music
						Mix_PlayMusic(Drawing::gMusic, 99);
					}
					// If music is being played
					else
					{
						// If the music is paused
						if (Mix_PausedMusic() == 1)
						{
							// Resume the music
							Mix_ResumeMusic();
						}
						// If the music is playing
						else
						{
							// Pause the music
							Mix_PauseMusic();
						}
					}
					break;
				case SDLK_1:

					if (state <= 5)
					{

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					// instruction
					if (state == 0)
					{
						state = 1;
					}
					// choose mode 1
					else if (state == 2)
					{
						state = 3;
						mode = 1;
					}
					// mode 1 level 1
					else if (state == 3)
					{
						level = 1;
						state = 6;
						game = new Retro(mode, level, 3, 3);
						wasStarted = true;
					}
					// mode 2 p1 = 1
					else if (state == 4)
					{
						p1_pad = 1;
						state = 5;
					}
					else if (state == 5)
					{
						state = 7;
						game = new Retro(mode, level, p1_pad, p2_pad);
						wasStarted = true;
					}

					break;
				case SDLK_2:

					if (state <= 5)
					{

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					// choose mode
					if (state == 0)
					{
						state = 2;
					}

					// choose mode 2
					else if (state == 2)
					{
						mode = 2;
						state = 4;
					}
					// mode 2 p1 = 2
					else if (state == 4)
					{
						p1_pad = 2;
						state = 5;
					}
					// mode 2 p2 = 2
					else if (state == 5)
					{
						p2_pad = 2;
						state = 7;

						game = new Retro(mode, level, p1_pad, p2_pad);
						wasStarted = true;
					}
					// mode 1 level 2
					else if (state == 3)
					{
						level = 2;
						state = 6;
						game = new Retro(mode, level, 3, 3);
						wasStarted = true;
					}
					break;
				case SDLK_3:

					if (state <= 5)
					{

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					// mode 1 level 3
					if (state == 3)
					{
						level = 3;
						state = 6;

						game = new Retro(mode, level, 3, 3);
						wasStarted = true;
					}
					// mode 2 p1 = 2
					else if (state == 4)
					{
						p1_pad = 3;
						state = 5;
					}
					// mode 2 p2 = 2
					else if (state == 5)
					{
						p2_pad = 3;
						state = 7;

						game = new Retro(mode, level, p1_pad, p2_pad);
						wasStarted = true;
					}
					break;
				case SDLK_e:

					Mix_PlayChannel(-1, Drawing::gButton, 0);
					quit = true;
					break;
				case SDLK_r:

					if (state == 8)
					{
						state = 0;

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					break;
				case SDLK_p:
					p2_up = true;
					p2_down = false;
					break;
				case SDLK_l:

					p2_up = false;
					p2_down = true;
					break;

				case SDLK_w:
					p1_up = true;
					p1_down = false;
					break;
				case SDLK_s:
					p1_up = false;
					p1_down = true;
					break;
				case SDLK_b:
					if (state == 1 || state == 2)
					{
						state = 0;

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					else if (state == 4 || state == 3)
					{
						state = 2;

						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					else if (state == 5)
					{
						state = 4;
						Mix_PlayChannel(-1, Drawing::gButton, 0);
					}
					break;
				}
			}
			else if (e.type == SDL_KEYUP)
			{

				switch (e.key.keysym.sym)
				{
				case SDLK_p:
					p2_up = false;
					break;
				case SDLK_l:
					p2_down = false;
					break;
				case SDLK_w:
					p1_up = false;
					break;
				case SDLK_s:
					p1_down = false;
					break;
				}
			}
		}

		SDL_DestroyTexture(gTexture);
		if (state == 0)
		{
			gTexture = loadTexture("./assets/main.png");
		}
		else if (state == 1)
		{
			gTexture = loadTexture("./assets/instructions.png");
		}
		else if (state == 2)
		{
			gTexture = loadTexture("./assets/mode.png");
		}
		else if (state == 3)
		{
			gTexture = loadTexture("./assets/levels.png");
		}
		else if (state == 4)
		{
			gTexture = loadTexture("./assets/player1paddles.png");
		}
		else if (state == 5)
		{
			gTexture = loadTexture("./assets/player2paddles.png");
		}
		else if (state == 7 || state == 6)
		{
			gTexture = loadTexture("./assets/game.png");
		}
		else if (state == 8)
		{

			gTexture = loadTexture("./assets/game_over.png");
		}

		SDL_RenderClear(Drawing::gRenderer); // removes everything from renderer
		SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, NULL);

		//***********************draw the objects here********************

		if (state == 7 || state == 6)
		{
			if (p1_up)
			{
				game->moveOne(-1);
			}
			if (p2_up)
			{
				game->moveTwo(-1);
			}

			if (p1_down)
			{

				game->moveOne(1);
			}
			if (p2_down)
			{

				game->moveTwo(1);
			}

			// SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
			// p.draw();
			// b.draw();
			// b.moveBall();
			// SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect1);
			game->update();
			int res = game->declareResult();
			if (res == 1)
			{
				state = 8;
			}
			else if (res == 2)
			{
				state = 8;
			}
		}
		// SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &{141, 240, 297, 818}, &{10, 10, 25, 100});
		//****************************************************************

		SDL_RenderPresent(Drawing::gRenderer); // displays the updated renderer

		// SDL_Delay(100); // causes sdl engine to delay for specified miliseconds
	}
	if (wasStarted)
	{
		game->~Retro();
		wasStarted = false;
	}
}
