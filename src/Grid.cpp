#include "Grid.hpp"

#include <iostream>
#include <math.h>

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

static sf::Vector2i getFirstVisibleCell(const sf::RenderWindow &window)
{
	sf::View view = window.getView();

	sf::FloatRect viewBounds;
	viewBounds.left = view.getCenter().x - view.getSize().x / 2;
	viewBounds.top = view.getCenter().y - view.getSize().y / 2;
	viewBounds.width = view.getSize().x;
	viewBounds.height = view.getSize().y;

	int firstVisibleCol = std::floor(viewBounds.left / CELL_SIZE);
	int firstVisibleRow = std::floor(viewBounds.top / CELL_SIZE);

	sf::Vector2u window_size = window.getSize();

	firstVisibleCol = std::max(0, std::min(firstVisibleCol, DEFAULT_WIDTH - 1));
	firstVisibleRow =
		std::max(0, std::min(firstVisibleRow, DEFAULT_HEIGHT - 1));

	return sf::Vector2i(firstVisibleCol, firstVisibleRow);
}

static sf::Vector2i getLastVisibleCell(const sf::RenderWindow &window)
{
	sf::View view = window.getView();

	sf::FloatRect viewBounds;
	viewBounds.left = view.getCenter().x - view.getSize().x / 2;
	viewBounds.top = view.getCenter().y - view.getSize().y / 2;
	viewBounds.width = view.getSize().x;
	viewBounds.height = view.getSize().y;

	int lastVisibleCol =
		std::floor((viewBounds.left + viewBounds.width) / CELL_SIZE);
	int lastVisibleRow =
		std::floor((viewBounds.top + viewBounds.height) / CELL_SIZE);

	sf::Vector2u window_size = window.getSize();

	lastVisibleCol = std::max(0, std::min(lastVisibleCol, DEFAULT_WIDTH - 1));
	lastVisibleRow = std::max(0, std::min(lastVisibleRow, DEFAULT_HEIGHT - 1));

	return sf::Vector2i(lastVisibleCol, lastVisibleRow);
}

void Grid::draw(sf::RenderWindow &window)
{
	sf::Vector2i top_left_cell = getFirstVisibleCell(window);
	sf::Vector2i bottom_right_cell = getLastVisibleCell(window);

	/* std::cout << top_left_cell.x << " " << top_left_cell.y << " " */
	/* 		  << bottom_right_cell.x << " " << bottom_right_cell.y << '\n'; */

	for (int row = top_left_cell.x; row <= bottom_right_cell.x; ++row) {
		for (int col = top_left_cell.y; col <= bottom_right_cell.y; ++col) {
			cells[row][col].draw(window);
		}
	}
}

void Grid::handle_click(sf::RenderWindow &window)
{
	sf::Vector2i mouse_window_pos = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_view_pos =
		window.mapPixelToCoords(mouse_window_pos, window.getView());

	if (mouse_view_pos.x < 0 || mouse_view_pos.y < 0)
		return;

	int row = mouse_view_pos.x / CELL_SIZE;
	int col = mouse_view_pos.y / CELL_SIZE;

	if (row >= DEFAULT_HEIGHT || col >= DEFAULT_WIDTH)
		return;

	/* std::cout << row << " " << col << '\n'; */

	cells[row][col].handle_click();
	board_data.set_cell(
		row,
		col,
		(board_data.get_cell(row, col) == ALIVE ? DEAD : ALIVE));
}
