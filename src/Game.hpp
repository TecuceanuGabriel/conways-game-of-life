#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.hpp"

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define MIN_ZOOM 0.2
#define MAX_ZOOM 2.0

class Game
{
  public:
	Game();
	void run();

  private:
	void processEvents();
	void update();
	void render();

  private:
	sf::RenderWindow window;
	sf::View view;

	Grid grid;
	float current_zoom;
};
