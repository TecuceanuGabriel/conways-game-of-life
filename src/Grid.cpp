#include "Grid.hpp"

void Grid::init_positions()
{
    cells.resize(height);
    for (auto &row : cells)
        row.resize(width);

	for (int row = 0; row < height; ++row)
		for (int col = 0; col < width; ++col)
			cells[row][col].set_position(row, col);
}

Grid::Grid()
	: board_data(DEFAULT_WIDTH, DEFAULT_HEIGHT), width(DEFAULT_WIDTH),
	  height(DEFAULT_HEIGHT)
{
    init_positions();
}

Grid::Grid(BoardData board_data)
	: board_data(board_data), width(board_data.get_width()),
	  height(board_data.get_height())
{
    init_positions();
}

void Grid::draw(sf::RenderWindow &window) {
    for (int row = 0; row < height; ++row)
        for (int col = 0; col < width; ++col)
            cells[row][col].draw(window);
}
