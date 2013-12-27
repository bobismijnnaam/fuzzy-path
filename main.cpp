// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 17-12-13
// Contact: http://knightsofthecompiler.wordpress.com - @broervanlisa - gmail (bobrubbens)

// Includes I didn't make myself
#include <iostream>
#include <SFML/Graphics.hpp>

// Includes I did make myself
#include "constants.hpp"
#include "Gamestate.hpp"
#include "Randomizer.hpp"
#include "globals.hpp"

int main() {
	Randomizer::selfSeed();

    sf::RenderWindow window(sf::VideoMode(SCR_W, SCR_H), "fuzzy-path");

    gm = new GameMan(STATE_MENU);
	
	sf::Clock timelord;
	sf::Time minion;
	float timekeeper = 0;

    while (gm->getState() != STATE_EXIT) {
		minion = timelord.restart();
		timekeeper += minion.asSeconds();
	
		while (timekeeper >= SCR_SPF) {
			gm->currState->events(window);
			
			gm->currState->logic(window);
			
			timekeeper -= SCR_SPF;
		}

        gm->changeState();

        gm->currState->render(window);
    }

    std::cout << "Bye!";

    delete gm;

    return 0;
}