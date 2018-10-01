#include "Window.h"
#include <SDL.h>
#include <iostream> /// Umer likes this over printf() - too bad
using namespace std;

Window::Window(int width_, int height_, char * windowName_) {
	windowName = windowName_;
	screenSurface = nullptr;
	window = nullptr;
	width = width_;
	height = height_;
}

bool Window::OnCreate(){
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		std::cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	window = SDL_CreateWindow(windowName, SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, width, height, SDL_WINDOW_SHOWN);
	if (window == nullptr) {
		cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}

	screenSurface = SDL_GetWindowSurface(window);
	if (screenSurface == nullptr) {
		cout << "SDL_Error: " << SDL_GetError() << std::endl;
		return false;
	}
	return true;
}

void Window::OnDestroy(){
	/// Kill the surface first
	if (screenSurface) SDL_FreeSurface(screenSurface);

	/// Now kill the window
	if (window) SDL_DestroyWindow(window);
	
	///Exit the SDL subsystems
	SDL_Quit();

}

Window::~Window(){}

SDL_Window* Window::GetSDL_Window() {
	return window;
}