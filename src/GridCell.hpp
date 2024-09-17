#pragma once

#include <SFML/Graphics.hpp>

#define CELL_SIZE 50

class GridCell
{
  public:
	GridCell();

	void set_position(int x, int y);
    void draw(sf::RenderWindow &window);

    bool is_hovered(sf::Vector2f mouse_position);
    bool is_visible(sf::RenderWindow &window);

  private:
    int x;
    int y;
	sf::RectangleShape shape;
};
