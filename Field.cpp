// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: do 19-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 

 // Includes I did make myself 
#include "constants.hpp"
#include "Field.hpp"

Field::Field(sf::Vector2i inputSize) {
	size = inputSize;
	for (int x = 0; x < size.x; ++x) {
		squareField.push_back(std::vector<Square>());

		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).push_back(Square(sf::Vector2i(x, y)));
		}
	}
}

Field::~Field() {

}

void Field::events(sf::Event event, sf::RenderWindow& window) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).at(y).events(event, window);
		}
	}
}

void Field::logic(sf::RenderWindow& window) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).at(y).logic(window);
		}
	}
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::View fieldView(sf::FloatRect(0, 0, size.x * SQUARE_SIDE, size.y * SQUARE_SIDE));
	fieldView.setViewport(sf::FloatRect(0.25f, 0.25f, 0.5f, 0.5f));
	target.setView(fieldView);

	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			target.draw(squareField.at(x).at(y), states);
		}
	}
}

int Field::getTrajectoryScore() {
	return 0;
}

bool Field::isTrajectoryFinished() {
	return false;
}

int Field::getPreviousTrajectoryScore() {
	return 0;
}

int Field::getRemainingBlack() {
	return 0;
}

int Field::getRemainingWhite() {
	return 0;
}
