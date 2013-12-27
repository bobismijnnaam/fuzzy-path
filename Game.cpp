// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: di 17-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <string>

 // Includes I did make myself 
#include "Field.hpp"
#include "functions.hpp"
#include "Game.hpp" 
#include "globals.hpp"

Game::Game() : field(sf::Vector2i(10, 10), InputMethod::Mouse) {
	if (!mainFont.loadFromFile("Media/gtw.ttf")) {
		// error!
	}

	sf::Text test("0", mainFont, 50);

	whitesLeftText = sf::Text(test);
	whitesLeftText.setPosition(96, 100);
	whitesLeftText.setColor(Square::High);

	blacksLeftText = sf::Text(test);
	blacksLeftText.setPosition(928, 100);
	blacksLeftText.setColor(Square::Low);

	scoreText = sf::Text(test);
	scoreText.setPosition(20, 700);

	score = 0;
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

	if (field.isTrajectoryFinished()) {
		score += field.getTrajectoryScore();
	}

	if (field.isGameOver()) {
		previousGameScore = score;
		firstTime = false;
		gm->setNextState(STATE_MENU);
	}

	// update texts texts;
	whitesLeftText.setString(itos(field.getRemainingWhite()));
	blacksLeftText.setString(itos(field.getRemainingBlack()));
	scoreText.setString("Score: " + itos(score));

	centerAlignText(whitesLeftText);
	centerAlignText(blacksLeftText);

	return 0;
}

int Game::render(sf::RenderWindow& window) {
	window.clear(sf::Color(88, 5, 171, 255));

	window.draw(field);

	window.draw(whitesLeftText);
	window.draw(blacksLeftText);
	window.draw(scoreText);

	window.display();

	return 0;
}