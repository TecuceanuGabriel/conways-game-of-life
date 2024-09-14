#pragma once

#include <SFML/Graphics.hpp>

#include "Grid.hpp"

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
	sf::RenderWindow mWindow;

    Grid grid;
};
