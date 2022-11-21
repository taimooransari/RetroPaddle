
#include <SDL.h>
#include <stdio.h>
#include <string>
#include <sstream>
class LWindow
{
public:
	// Intializes internals
	LWindow();

	// Creates window
	bool init();

	// Handles window events
	void handleEvent(SDL_Event &e);

	// Focuses on window
	void focus();

	// Shows windows contents
	void render();

	// Deallocates internals
	void free();

	// Window dimensions
	int getWidth();
	int getHeight();

	// Window focii
	bool hasMouseFocus();
	bool hasKeyboardFocus();
	bool isMinimized();
	bool isShown();
	SDL_Window *getWin(){return mWindow};

private:
	// Window data
	SDL_Window *mWindow;
	SDL_Renderer *mRenderer;
	int mWindowID;

	// Window dimensions
	int mWidth;
	int mHeight;

	// Window focus
	bool mMouseFocus;
	bool mKeyboardFocus;
	bool mFullScreen;
	bool mMinimized;
	bool mShown;
};
