#include "GridCell.hpp"

GridCell::GridCell() : shape()
{
	shape.setSize(sf::Vector2f(CELL_SIZE, CELL_SIZE));
	shape.setFillColor(sf::Color::Black);
	shape.setOutlineThickness(2);
	shape.setOutlineColor(sf::Color::White);
	shape.setPosition(sf::Vector2f(0, 0));
}

void GridCell::set_position(int x, int y)
{
	this->x = x;
	this->y = y;
	shape.setPosition(x * CELL_SIZE, y * CELL_SIZE);
}

void GridCell::draw(sf::RenderWindow &window)
{
	if (is_hovered(sf::Mouse::getPosition(window)))
		shape.setFillColor(sf::Color::White);
	else
		shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}

bool GridCell::is_hovered(sf::Vector2i mouse_position)
{
	return x * CELL_SIZE <= mouse_position.x &&
		   mouse_position.x <= (x + 1) * CELL_SIZE &&
		   y * CELL_SIZE <= mouse_position.y &&
		   mouse_position.y <= (y + 1) * CELL_SIZE;
}
