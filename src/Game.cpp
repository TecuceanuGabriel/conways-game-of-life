#include "Game.hpp"

static sf::ContextSettings get_context_settings()
{
	sf::ContextSettings settings;
	settings.antialiasingLevel = 8;
	return settings;
}

Game::Game()
	: window(sf::VideoMode(WINDOW_WIDTH, WINDOW_HEIGHT),
			 "Conway's game",
			 sf::Style::Default,
			 get_context_settings()),
	  view(sf::FloatRect(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT)), current_zoom(1),
	  grid()
{
	view.setCenter(DEFAULT_WIDTH * CELL_SIZE / 2.f,
				   DEFAULT_HEIGHT * CELL_SIZE / 2.f);
}

void Game::run()
{
	while (window.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (window.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			window.close();
		if (event.type == sf::Event::Resized) {
			float new_width = static_cast<float>(event.size.width);
			float new_height = static_cast<float>(event.size.height);

			view.setSize(new_width, new_height);
			view.zoom(current_zoom);
		}
		if (event.type == sf::Event::MouseWheelScrolled) {
			if (event.mouseWheelScroll.delta > 0) {
				if (current_zoom > MIN_ZOOM) {
					view.zoom(0.9f);
					current_zoom *= 0.9f;
				}
			} else {
				if (current_zoom < MAX_ZOOM) {
					view.zoom(1.1f);
					current_zoom *= 1.1f;
				}
			}
		}
	}
}

void Game::update() {}

void Game::render()
{
	window.clear();
	window.setView(view);
	grid.draw(window);
	window.display();
}
