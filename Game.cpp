// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: di 17-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 

 // Includes I did make myself 
#include "Game.hpp" 
#include "globals.hpp"

Game::Game() {

}

Game::~Game() {

}

int Game::events(sf::RenderWindow& window) {
	sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gm->setNextState(STATE_EXIT);
        }
	}
	
	return 0;
}

int Game::logic(sf::RenderWindow& window) {

	return 0;
}

int Game::render(sf::RenderWindow& window) {

	return 0;
}