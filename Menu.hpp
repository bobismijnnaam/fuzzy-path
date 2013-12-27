// Author: Bob Rubbens - Knights of the Compiler
// Creation date: di 17-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef MENU_HPP
#define MENU_HPP

// Includes I didn't make myself


 // Includes I did make myself
#include "Gamestate.hpp"

class Menu : public GameState {
public:
	Menu();
	~Menu();

	int events(sf::RenderWindow& window);
    int logic(sf::RenderWindow& window);
    int render(sf::RenderWindow& window);

private:
	sf::Font mainFont;
	sf::Text playText;
	sf::Text scoreText;
};

#endif
