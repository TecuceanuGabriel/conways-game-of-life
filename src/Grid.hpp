#pragma once

#include "BoardData.hpp"
#include "GridCell.hpp"

#define DEFAULT_WIDTH 10
#define DEFAULT_HEIGHT 10

class Grid
{
  public:
	Grid();
    Grid(BoardData board_data);

    void draw(sf::RenderWindow &window);

	void handle_click();

  private:
    void init_positions();

  private:
	BoardData board_data;
    int width;
    int height;

	std::vector<std::vector<GridCell>> cells;
};
