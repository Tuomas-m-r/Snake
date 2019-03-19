#include "GameManager.h"
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
	snakeHead.w = 20;
	snakeHead.h = 20;
	snakeHead.y = SCREEN_HEIGTH / 2;
	snakeHead.x = SCREEN_WIDTH / 2;
	pos[0].x = snakeHead.x;
	pos[0].y = snakeHead.y;

	for (int i = 0; i < pos.size(); i++) {
		pos[i].w = 20;
		pos[i].h = 20;
	}
	foodRect.w = 20;
	foodRect.h = 20;
	currentDirection = DIRECTION_LEFT;
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
	if (snakeHead.x == foodRect.x && snakeHead.y == foodRect.y) {
		foodRect.x = 20 * (rand() % X_MAX + 1);
		foodRect.y = 20 * (rand() % Y_MAX + 1);
		snakeSize++;
	}
	moveSnake();
}

void GameManager::renderSnake() {
	for (int i = 0; i < snakeSize; i++){
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, SDL_ALPHA_OPAQUE);
		SDL_RenderClear(renderer);
		SDL_SetRenderDrawColor(renderer, 0, 255, 0, SDL_ALPHA_OPAQUE);
		for (int j = 0; j < snakeSize; j++) {
			SDL_RenderFillRect(renderer, &pos[j]);
		}
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
	yVelocity = 0;
	xVelocity = 0;
	if (currentDirection == DIRECTION_UP) {
		if (snakeHead.y == 0) {
			snakeHead.y = 0;
		}
		else {
			yVelocity = negativeSpeed;
		}
	}
	else if (currentDirection == DIRECTION_DOWN) {
		if (snakeHead.y == (SCREEN_HEIGTH - snakeHead.h)) {
			snakeHead.y = SCREEN_HEIGTH - snakeHead.h;
		}
		else {
			yVelocity = speed;
		}
	}
	else if (currentDirection == DIRECTION_LEFT) {
		if (snakeHead.x == 0) {
			snakeHead.x = 0;
		}
		else {
			xVelocity = negativeSpeed;
		}
	}
	else if (currentDirection == DIRECTION_RIGHT) {
		if (snakeHead.x == (SCREEN_WIDTH - snakeHead.w)) {
			snakeHead.x = SCREEN_WIDTH - snakeHead.w;
		}
		else {
			xVelocity = speed;
		}
	}

	if (snakeSize > 1) {
		for (int i = snakeSize - 1; i > 0; --i) {
			pos[i] = pos[i - 1];
		}
	}
	pos[0].x = snakeHead.x;
	pos[0].y = snakeHead.y;
	snakeHead.x += xVelocity;
	snakeHead.y += yVelocity;
}