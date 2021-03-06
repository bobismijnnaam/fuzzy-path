// Author: Bob Rubbens - Knights of the Compiler
// Creation date: di 17-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef GAME_HPP
#define GAME_HPP

// Includes I didn't make myself

 // Includes I did make myself
#include "Field.hpp"
#include "Gamestate.hpp"

class Game : public GameState {
public:
	Game();
	~Game();

	int events(sf::RenderWindow& window);
    int logic(sf::RenderWindow& window);
    int render(sf::RenderWindow& window);

private:
	Field field;

	sf::Font mainFont;

	sf::Text whitesLeftText;
	sf::Text blacksLeftText;
	sf::Text scoreText;
	int score;
};

#endif
