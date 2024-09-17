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
	sf::Vector2i mouse_window_pos = sf::Mouse::getPosition(window);
	sf::Vector2f mouse_view_pos =
		window.mapPixelToCoords(mouse_window_pos, window.getView());

	if (is_hovered(mouse_view_pos))
		shape.setFillColor(sf::Color::White);
	else
		shape.setFillColor(sf::Color::Black);

	window.draw(shape);
}

bool GridCell::is_hovered(sf::Vector2f mouse_position)
{
	return x * CELL_SIZE <= mouse_position.x &&
		   mouse_position.x <= (x + 1) * CELL_SIZE &&
		   y * CELL_SIZE <= mouse_position.y &&
		   mouse_position.y <= (y + 1) * CELL_SIZE;
}

bool GridCell::is_visible(sf::RenderWindow &window)
{
	sf::FloatRect object_bounds = shape.getGlobalBounds();

	sf::View view = window.getView();
	sf::FloatRect view_bounds;
	view_bounds.left = view.getCenter().x - view.getSize().x / 2;
	view_bounds.top = view.getCenter().y - view.getSize().y / 2;
	view_bounds.width = view.getSize().x;
	view_bounds.height = view.getSize().y;

	return object_bounds.intersects(view_bounds);
}
