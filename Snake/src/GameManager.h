#pragma once
#include <SDL.h>
#include <array>

class GameManager {
public:
	GameManager();
	~GameManager();
	void init();
	void createWindow();
	void createRenderer();
	void handleEvents();
	void renderSnake();
	void renderFood();
	void update();
	void clean();
	void moveSnake();
	bool running() { return isRunning; }
	
private:
	const int X_MAX = 40;
	const int Y_MAX = 30;
	int currentDirection;
	int snakeSize = 1;
	const int negativeSpeed = -20;
	const int speed = 20;
	int xVelocity = 0;
	int yVelocity = 0;
	bool isRunning = false;
	const int SCREEN_WIDTH = 800;
	const int SCREEN_HEIGTH = 600;
	SDL_Window *window = nullptr;
	SDL_Surface *screenSurface = nullptr;
	SDL_Renderer *renderer = nullptr;
	SDL_Rect snakeHead;
	SDL_Rect foodRect;
	std::array<SDL_Rect, 100> pos;
};