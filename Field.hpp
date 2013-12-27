// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 19-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef FIELD_HPP
#define FIELD_HPP

// Includes I didn't make myself
#include <vector>

 // Includes I did make myself
#include "Chain.hpp"
#include "Square.hpp"

enum class InputMethod {
	Keyboard,
	Mouse
} ;

enum class FieldState {
	Idling,
	Drawing,
	Committing
} ;

class Field : public sf::Drawable {
public:
	Field(sf::Vector2i inputSize, InputMethod preferredInputMethod);
	~Field();

	void events(sf::Event event, sf::RenderWindow& window);
	void logic(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	int getTrajectoryScore();
	bool isTrajectoryFinished();
	int getPreviousTrajectoryScore();
	int getRemainingBlack();
	int getRemainingWhite();
	bool isGameOver();

	Square& at(sf::Vector2i p);

	FieldState getState();

private:
	sf::Vector2i size;
	std::vector<std::vector<Square>> squareField;

	// std::vector<sf::Vector2i> points;
	// bool pointerChanged;

	Chain chain;
	
	InputMethod inputMethod;

	sf::View fieldView;

	FieldState state;

	int whites;
	int blacks;
	int latestScore;
	int previousScore;
	bool newScore;
	bool gameOver;
};

#endif
