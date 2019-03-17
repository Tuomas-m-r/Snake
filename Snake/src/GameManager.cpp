#include "GameManager.h"
#include "Snake.h"
#include <stdlib.h>
#include <SDL.h>
#include <iostream>

enum Directions {
	DIRECION_DEFAULT,
	DIRECTION_UP,
	DIRECTION_DOWN,
	DIRECTION_LEFT,
	DIRECTION_RIGHT
};

GameManager::GameManager() {
	init();
	std::cout << "Game created!\n";
}

GameManager::~GameManager() {
	clean();
	std::cout << "Game destroyed!\n";
}

void GameManager::init() {
	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		std::cout << "Failed to initialize SDL! SDL_Error:\n" << SDL_GetError();
	}
	else {
		std::cout << "SDL initiliazed succesfully!\n";
		createWindow();
		createRenderer();
		isRunning = true;
	}
	snakeHead = { 400, 300, 20, 20 };
	foodRect.w = 20;
	foodRect.h = 20;
}

void GameManager::createWindow() {
	window = SDL_CreateWindow("Snake", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, SCREEN_WIDTH, SCREEN_HEIGTH, SDL_WINDOW_SHOWN);

	if (window == nullptr) {
		std::cout << "Failed to create window! SDL_Error:\n" << SDL_GetError();
	}
	else {
		std::cout << "Window created succesfully!\n";
		screenSurface = SDL_GetWindowSurface(window);
	}
}

void GameManager::createRenderer() {
	renderer = SDL_CreateRenderer(window, -1, 0);

	if (renderer == nullptr) {
		std::cout << "Failed to create renderer! SDL_Error:\n" << SDL_GetError();
	}
	else {
		std::cout << "Renderer created succesfully!\n";
	}
}

void GameManager::handleEvents() {
	SDL_Event event;
	while (SDL_PollEvent(&event) != 0) {
		if(event.type == SDL_QUIT){
			isRunning = false;
		}
		else if (event.type == SDL_KEYDOWN) {
			switch (event.key.keysym.sym)
			{
				case SDLK_w:
				{
					if (currentDirection != DIRECTION_DOWN) {
						currentDirection = DIRECTION_UP;
						break;
					}
				}
				case SDLK_s:
				{
					if (currentDirection != DIRECTION_UP) {
						currentDirection = DIRECTION_DOWN;
						break;
					}
				}
				case SDLK_a:
				{
					if (currentDirection != DIRECTION_RIGHT) {
						currentDirection = DIRECTION_LEFT;
						break;
					}
				}
				case SDLK_d:
				{
					if (currentDirection != DIRECTION_LEFT) {
						currentDirection = DIRECTION_RIGHT;
						break;
					}
				}
				default:
					break;
			}
		}
	}
}

void GameManager::update() {
	
	moveSnake();
	if (snakeHead.x == foodRect.x && snakeHead.y == foodRect.y) {
		foodRect.x = 20 * (rand() % X_MAX + 1);
		foodRect.y = 20 * (rand() % Y_MAX + 1);
		
	}
}

void GameManager::renderSnake() {
	for (SDL_Rect &rect : snakePast) {
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderFillRect(renderer, &snakeHead);
		SDL_RenderPresent(renderer);
	}
}

void GameManager::renderFood() {
	SDL_SetRenderDrawColor(renderer, 255, 0, 0, SDL_ALPHA_OPAQUE);
	SDL_RenderFillRect(renderer, &foodRect);
	SDL_RenderPresent(renderer);
}

void GameManager::clean() {
	SDL_DestroyWindow(window);
	SDL_DestroyRenderer(renderer);
	SDL_Quit();
}

void GameManager::moveSnake() {
	if (currentDirection == DIRECTION_UP) {
		if (snakeHead.y == 0) {
			snakeHead.y = 0;
		}
		else {
			snakeHead.y -= yVelocity;
		}
	}
	else if (currentDirection == DIRECTION_DOWN) {
		if (snakeHead.y == (SCREEN_HEIGTH - snakeHead.h)) {
			snakeHead.y = SCREEN_HEIGTH - snakeHead.h;
		}
		else {
			snakeHead.y += yVelocity;
		}
	}
	else if (currentDirection == DIRECTION_LEFT) {
		if (snakeHead.x == 0) {
			snakeHead.x = 0;
		}
		else {
			snakeHead.x -= xVelocity;
		}
	}
	else if (currentDirection == DIRECTION_RIGHT) {
		if (snakeHead.x == (SCREEN_WIDTH - snakeHead.w)) {
			snakeHead.x = SCREEN_WIDTH - snakeHead.w;
		}
		else {
			snakeHead.x += xVelocity;
		}
	}
}