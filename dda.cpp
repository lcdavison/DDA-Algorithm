#include <SDL.h>

#include <iostream>
#include <cmath>

// TODO: Use mouse position to determine the START and END points of a line

SDL_Renderer* renderer;

struct Point2 
{
	Point2(float x, float y) : x(x), y(y) {}
	float x, y;
};

void ColourPixel(int x, int y) 
{
	SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
	SDL_RenderDrawPoint(renderer, x, y);
	SDL_RenderPresent(renderer);
}

void DrawLine(Point2 start, Point2 end)
{
	float diff_x = end.x - start.x;
	float diff_y = end.y - start.y;

	float steps;

	if(diff_x > diff_y)
		steps = std::abs(diff_x);
	else
		steps = std::abs(diff_y);

	float increment_x = diff_x / steps;
	float increment_y = diff_y / steps;

	float x = start.x, y = start.y;

	for(int i = 0; i < steps; i++) 
	{
		std::cout << "X : " << x << " Y : " << y << std::endl;

		x += increment_x;
		y += increment_y;

		ColourPixel(std::floor(x), std::floor(y));
	}
}

int main(int argc, char* argv[]) 
{
	if(SDL_Init(SDL_INIT_VIDEO) < 0) 
	{
		std::cout << "Failed to initialize SDL2" << std::endl;
		return 1;
	}

	SDL_Window* window = SDL_CreateWindow("DDA", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	
	SDL_Event event;

	while(true)
	{
		while(SDL_PollEvent(&event)) 
		{
			switch(event.type) 
			{
				case SDL_QUIT:
					return 0;
			}
		}

		SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
		SDL_RenderClear(renderer);

		DrawLine(Point2(0, 0), Point2(1279, 719));	
		DrawLine(Point2(640, 360), Point2(1279, 360));
		DrawLine(Point2(1279, 0), Point2(0, 719));
	}


	return 0;
}
