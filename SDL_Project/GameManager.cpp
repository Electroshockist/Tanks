#include "GameManager.h"
#include "Window.h"
#include "Timer.h"
#include "Assignment1.h"
#include "Assignment2.h"
#include "Assignment3.h"
#include "SDL.h"

#include <iostream>

GameManager::GameManager() {	
	timer = nullptr;
	isRunning = true;
	currentScene = nullptr;
}


/// In this OnCreate() method, fuction, subroutine, whatever the word, 
bool GameManager::OnCreate() {
	const int SCREEN_WIDTH = 1024;
	const int SCREEN_HEIGHT = 500;
	ptr = new Window(SCREEN_WIDTH, SCREEN_HEIGHT, "");
	if (ptr == nullptr) {
		OnDestroy();
		return false;
	}
	if (ptr->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	timer = new Timer();
	if (timer == nullptr) {
		OnDestroy();
		return false;
	}

	currentScene = new Assignment1(ptr->GetSDL_Window());
	if (currentScene == nullptr) {
		OnDestroy();
		return false;
	}

	if (currentScene->OnCreate() == false) {
		OnDestroy();
		return false;
	}

	return true;
}

void GameManager::Run() {
    SDL_Event event;

    bool start =  false;

    while (isRunning) {

        if (SDL_PollEvent(&event) != 0) {
            currentScene->HandleEvents(event);

			switch (event.type) {
			case SDL_QUIT:
				isRunning = false;
				break;
			case SDL_KEYDOWN:
				if (event.key.keysym.sym == SDLK_ESCAPE) {
					isRunning = false;
				}
				if (event.key.keysym.sym == SDLK_F1) {
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Assignment1(ptr->GetSDL_Window());
					ptr->windowName = "Assignment 1";
					currentScene->OnCreate();
				}
				if (event.key.keysym.sym == SDLK_F2) {
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Assignment2(ptr->GetSDL_Window());
					ptr->windowName = "Assignment 2";
					currentScene->OnCreate();
				}
				if (event.key.keysym.sym == SDLK_F3) {
					currentScene->OnDestroy();
					delete currentScene;
					currentScene = new Assignment3(ptr->GetSDL_Window());
					ptr->windowName = "Assignment 3";
					currentScene->OnCreate();
				}
				if (event.key.keysym.sym == SDLK_SPACE) {
					start = true;
				}
				break;
			default:
				break;
			}
        }

        if (start) {

			currentScene->Update(timer->GetDeltaTime());
			currentScene->Render();
        }

		timer->UpdateFrameTicks();

        /// Keeep the event loop running at a proper rate
        SDL_Delay(timer->GetSleepTime(60)); ///60 frames per sec

    }
}

GameManager::~GameManager() {}

void GameManager::OnDestroy(){
	if (ptr) delete ptr;
	if (timer) delete timer;
	if (currentScene) delete currentScene;
}