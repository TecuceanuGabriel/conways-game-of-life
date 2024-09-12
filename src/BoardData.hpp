#pragma once

#include <vector>

enum CellState { DEAD, ALIVE };

class BoardData
{
  public:
	BoardData();

    void set_cell(int x, int y, CellState cs);
    CellState get_cell(int x, int y);

    void next_generation();

  private:
    int count_neighbours(int x, int y);

  private:
	std::vector<std::vector<CellState>> cells;
    int height;
    int width;

};
