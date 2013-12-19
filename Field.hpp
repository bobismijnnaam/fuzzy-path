// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 19-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef FIELD_HPP
#define FIELD_HPP

// Includes I didn't make myself
#include <vector>

 // Includes I did make myself
#include "Square.hpp"


class Field : public sf::Drawable {
public:
	Field(sf::Vector2i inputSize);
	~Field();

	void events(sf::Event event, sf::RenderWindow& window);
	void logic(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getTrajectoryScore();
	bool isTrajectoryFinished();
	int getPreviousTrajectoryScore();
	int getRemainingBlack();
	int getRemainingWhite();

private:
	sf::Vector2i size;
	std::vector<std::vector<Square>> squareField;

	sf::Vector2i pointer;
	bool newPointer;
};

#endif
