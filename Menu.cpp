// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: di 17-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <SFML/Graphics.hpp>

 // Includes I did make myself 
#include "constants.hpp"
#include "functions.hpp"
#include "globals.hpp"
#include "Menu.hpp" 
#include "Square.hpp"

Menu::Menu() {
	if (!mainFont.loadFromFile("Media/gtw.ttf")) {
		// error!
	}

	playText.setFont(mainFont);
	playText.setCharacterSize(100);
	playText.setColor(Square::High);
	playText.setString(firstTime ? "PLAY" : "PLAY AGAIN?");
	playText.setOrigin(playText.getLocalBounds().width / 2, playText.getLocalBounds().height / 2);
	playText.setPosition(SCR_W / 2, SCR_H / 2);

	if (!firstTime) {
		scoreText = sf::Text(playText);
		scoreText.setString("Score: " + itos(previousGameScore));
		scoreText.setOrigin(scoreText.getLocalBounds().width / 2, scoreText.getLocalBounds().height / 2);
		scoreText.setPosition(SCR_W / 2, SCR_H / 2 - 300);
	}
}

Menu::~Menu() {

}

int Menu::events(sf::RenderWindow& window) {
	sf::Event event;

    while (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed) {
            gm->setNextState(STATE_EXIT);
        } else if (event.type == sf::Event::MouseButtonReleased) {
        	if (event.mouseButton.button == sf::Mouse::Left) {
        		if (playText.getGlobalBounds().contains(event.mouseButton.x, event.mouseButton.y)) {
        			gm->setNextState(STATE_GAME);
        		}
        	}
        }
	}
	return 0;
}

int Menu::logic(sf::RenderWindow& window) {

	return 0;
}

int Menu::render(sf::RenderWindow& window) {
	window.clear(Square::Low);

	window.draw(playText);
	window.draw(scoreText);

	window.display();

	return 0;
}

