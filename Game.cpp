// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: di 17-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 

 // Includes I did make myself 
#include "Field.hpp"
#include "Game.hpp" 
#include "globals.hpp"

Game::Game() : field(sf::Vector2i(10, 10), InputMethod::Mouse) {

}

Game::~Game() {

}

int Game::events(sf::RenderWindow& window) {
	sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gm->setNextState(STATE_EXIT);
        }

        field.events(event, window);
	}
	
	return 0;
}

int Game::logic(sf::RenderWindow& window) {
	field.logic(window);

	return 0;
}

int Game::render(sf::RenderWindow& window) {
	window.clear(sf::Color(28, 144, 184, 255));

	window.draw(field);

	window.display();

	return 0;
}