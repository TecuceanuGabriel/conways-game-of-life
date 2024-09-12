#pragma once

#include "BoardData.hpp"

class Grid
{
  public:
	Grid();

    void handle_click();

  private:
    BoardData board_data;
};
