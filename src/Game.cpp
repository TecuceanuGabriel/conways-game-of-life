#include "Game.hpp"

Game::Game() : mWindow(sf::VideoMode(640, 480), "Conway's game"), grid()
{
}

void Game::run()
{
	while (mWindow.isOpen()) {
		processEvents();
		update();
		render();
	}
}

void Game::processEvents()
{
	sf::Event event;
	while (mWindow.pollEvent(event)) {
		if (event.type == sf::Event::Closed)
			mWindow.close();
	}
}

void Game::update() {}

void Game::render()
{
	mWindow.clear();
    grid.draw(mWindow); 
	mWindow.display();
}
