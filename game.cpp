#include "./headers/game.hpp"
#include "./headers/drawing.hpp"
#include <iostream>
using namespace std;
SDL_Renderer *Drawing::gRenderer = NULL;
SDL_Texture *Drawing::assets = NULL;

bool Game::init()
{
	// Initialization flag
	bool success = true;

	// obj = Object();
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
		gWindow = SDL_CreateWindow("Pong Game", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
		if (gWindow == NULL)
		{
			printf("Window could not be created! SDL Error: %s\n", SDL_GetError());
			success = false;
		}
		else
		{
			// Create renderer for window
			Drawing::gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED);

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

	gTexture = loadTexture("./assets/main.png");

	if (gTexture == NULL || Drawing::assets == NULL)
	{
		printf("Unable to run due to error: %s\n", SDL_GetError());
		success = false;
	}
	return success;
}

void Game::close()
{
	// Free loaded images

	SDL_DestroyTexture(gTexture);

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
	bool quit = false;
	SDL_Event e;
	SDL_Rect srcRect, moverRect;

	srcRect = {141, 240, 297, 818};
	moverRect = {10, 10, 50, 150};
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
				case SDLK_1:
					cout << 1 << " Pressed " << endl;
					if (state == 0)
					{
						state = 1;
					}
					else if (state == 2)
					{
						state = 3;
					}
					else if (state == 4)
					{
						state = 5;
					}
					break;
				case SDLK_2:
					cout << 2 << " Pressed " << endl;
					if (state == 0)
					{
						state = 2;
					}
					else if (state == 2)
					{
						state = 4;
					}
					else if (state == 4)
					{
						state = 5;
					}
					break;
				case SDLK_UP:
					moverRect.y -= 10;
					break;
				case SDLK_DOWN:
					moverRect.y += 10;
					break;
				// case SDLK_3:
				// 	if (state == 2)
				// 	{
				// 		state = 3;
				// 	}
				// 	break;
				// case SDLK_4:
				// 	if (state == 2)
				// 	{
				// 		state = 4;
				// 	}
				// 	break;
				// case SDLK_5:
				// 	if (state == 4)
				// 	{
				// 		state = 5;
				// 	}
				case SDLK_b:
					cout << "b Pressed" << endl;
					if (state == 1 || state == 2)
					{
						state = 0;
					}
					else if (state == 4 || state == 3)
					{
						state = 2;
					}
					else if (state == 5)
					{
						state = 4;
					}
					break;
				}
			}

			// if (e.type == SDL_MOUSEBUTTONDOWN)
			// {
			// 	// this is a good location to add pigeon in linked list.
			// 	int xMouse, yMouse;
			// 	SDL_GetMouseState(&xMouse, &yMouse);
			// 	if (xMouse > 220 * 1.5 && xMouse < 500 * 1.5 && yMouse > 210 * 1.5 && yMouse < 270 * 1.5)
			// 	{
			// 		quit = false;
			// 		gTexture = loadTexture("./assets/mode.png");
			// 		// tried to implement switching between multiple screens but this code is
			// 		//  skipping the screens so i'll keep working on it
			// 		//      if(e.type == SDL_MOUSEBUTTONDOWN){
			// 		//          int xMouse1, yMouse1;
			// 		//          SDL_GetMouseState(&xMouse1,&yMouse1);
			// 		//      if(xMouse1>220 && xMouse1<500 && yMouse1>210 && yMouse1<270){
			// 		//      quit = false;
			// 		//      gTexture = loadTexture("levels.png");
			// 		//      }
			// 		//      else if(xMouse1>220 && xMouse1<500 && yMouse1>290 && yMouse1<350){
			// 		//      quit = false;
			// 		//      gTexture = loadTexture("player1paddles.png");
			// 		//  }}
			// 	}
			// 	else if (xMouse > 220 * 1.5 && xMouse < 500 * 1.5 && yMouse > 290 * 1.5 && yMouse < 350 * 1.5)
			// 	{
			// 		quit = false;
			// 		gTexture = loadTexture("./assets/instructions.png");
			// 	}
			// }
		}

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
		SDL_RenderClear(Drawing::gRenderer); // removes everything from renderer
		SDL_RenderCopy(Drawing::gRenderer, gTexture, NULL, NULL);

		//***********************draw the objects here********************

		SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &srcRect, &moverRect);
		// SDL_RenderCopy(Drawing::gRenderer, Drawing::assets, &{141, 240, 297, 818}, &{10, 10, 25, 100});
		//****************************************************************
		SDL_RenderPresent(Drawing::gRenderer); // displays the updated renderer

		SDL_Delay(100); // causes sdl engine to delay for specified miliseconds
	}
}
