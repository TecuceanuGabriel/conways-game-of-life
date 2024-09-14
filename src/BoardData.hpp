#pragma once

#include <vector>

enum CellState { DEAD, ALIVE };

class BoardData
{
  public:
	BoardData();
    BoardData(int width, int height);

	void set_cell(int x, int y, CellState cs);
	CellState get_cell(int x, int y);

    int get_width();
    int get_height();

	void next_generation();

  private:
	int count_neighbours(int x, int y);
    void resize(int width, int height);

  private:
	int height;
	int width;

	std::vector<std::vector<CellState>> cells;
};
