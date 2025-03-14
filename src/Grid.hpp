#pragma once

#include "BoardData.hpp"
#include "GridCell.hpp"

#define DEFAULT_WIDTH 100
#define DEFAULT_HEIGHT 100

class Grid
{
  public:
	Grid();
	Grid(BoardData board_data);

	void draw(sf::RenderWindow &window);
    void update();

	void handle_click(sf::RenderWindow &window);

  private:
	void init_positions();

  private:
	BoardData board_data;
	int width;
	int height;

	std::vector<std::vector<GridCell>> cells;
};
