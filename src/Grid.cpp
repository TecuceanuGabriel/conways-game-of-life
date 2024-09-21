#include "Grid.hpp"

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

	sf::FloatRect view_bounds;
	view_bounds.left = view.getCenter().x - view.getSize().x / 2;
	view_bounds.top = view.getCenter().y - view.getSize().y / 2;
	view_bounds.width = view.getSize().x;
	view_bounds.height = view.getSize().y;

	int bottom_corner_col = std::floor(view_bounds.left / CELL_SIZE);
	int bottom_corner_row = std::floor(view_bounds.top / CELL_SIZE);

	sf::Vector2u window_size = window.getSize();

	bottom_corner_col =
		std::max(0, std::min(bottom_corner_col, DEFAULT_WIDTH - 1));
	bottom_corner_row =
		std::max(0, std::min(bottom_corner_row, DEFAULT_HEIGHT - 1));

	return sf::Vector2i(bottom_corner_col, bottom_corner_row);
}

static sf::Vector2i getLastVisibleCell(const sf::RenderWindow &window)
{
	sf::View view = window.getView();

	sf::FloatRect view_bounds;
	view_bounds.left = view.getCenter().x - view.getSize().x / 2;
	view_bounds.top = view.getCenter().y - view.getSize().y / 2;
	view_bounds.width = view.getSize().x;
	view_bounds.height = view.getSize().y;

	int top_corner_col =
		std::floor((view_bounds.left + view_bounds.width) / CELL_SIZE);
	int top_corner_row =
		std::floor((view_bounds.top + view_bounds.height) / CELL_SIZE);

	sf::Vector2u window_size = window.getSize();

	top_corner_col = std::max(0, std::min(top_corner_col, DEFAULT_WIDTH - 1));
	top_corner_row = std::max(0, std::min(top_corner_row, DEFAULT_HEIGHT - 1));

	return sf::Vector2i(top_corner_col, top_corner_row);
}

void Grid::draw(sf::RenderWindow &window)
{
	sf::Vector2i top_left_cell = getFirstVisibleCell(window);
	sf::Vector2i bottom_right_cell = getLastVisibleCell(window);

	for (int row = top_left_cell.x; row <= bottom_right_cell.x; ++row) {
		for (int col = top_left_cell.y; col <= bottom_right_cell.y; ++col) {
			cells[row][col].draw(window, board_data.get_cell(row, col));
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

	board_data.set_cell(
		row,
		col,
		(board_data.get_cell(row, col) == ALIVE ? DEAD : ALIVE));
}

void Grid::update() { board_data.next_generation(); }
