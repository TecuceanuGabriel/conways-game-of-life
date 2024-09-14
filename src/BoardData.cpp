#include "BoardData.hpp"

BoardData::BoardData() {}

void BoardData::resize(int width, int height)
{
	cells.resize(height);
	for (auto &row : cells)
		row.resize(width);
}

BoardData::BoardData(int width, int height) : width(width), height(height)
{
	resize(width, height);
}

void BoardData::set_cell(int x, int y, CellState cs) { cells[x][y] = cs; }

CellState BoardData::get_cell(int x, int y) { return cells[x][y]; }

int BoardData::get_width() { return width; }

int BoardData::get_height() { return height; }

int BoardData::count_neighbours(int x, int y)
{
	int count = 0;

	for (int i = -1; i <= 1; ++i)
		for (int j = -1; j <= 1; ++j) {
			if (i == 0 && j == 0)
				continue;

			int new_x = x + i;
			int new_y = y + j;

			if (0 <= new_x && new_x <= height && 0 <= new_y && new_y <= width)
				count += cells[new_x][new_y];
		}

	return count;
}

void BoardData::next_generation()
{
	for (int x = 0; x < height; ++x)
		for (int y = 0; y < width; ++y) {
			int neighbour_count = count_neighbours(x, y);

			if (cells[x][y] == CellState::ALIVE &&
				(neighbour_count < 2 || neighbour_count >= 4))
				set_cell(x, y, CellState::DEAD);
			else if (cells[x][y] == CellState::DEAD && neighbour_count == 3)
				set_cell(x, y, CellState::ALIVE);
		}
}
