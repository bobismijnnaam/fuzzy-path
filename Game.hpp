// Author: Bob Rubbens - Knights of the Compiler
// Creation date: di 17-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef GAME_HPP
#define GAME_HPP

// Includes I didn't make myself

 // Includes I did make myself
#include "Gamestate.hpp"

class Game : public GameState {
public:
	Game();
	~Game();

	int events(sf::RenderWindow& window);
    int logic(sf::RenderWindow& window);
    int render(sf::RenderWindow& window);

private:

};

#endif
