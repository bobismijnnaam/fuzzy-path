// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: do 19-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 

 // Includes I did make myself
#include "constants.hpp"
#include "Randomizer.hpp"
#include "Square.hpp" 

Square::Square(sf::Vector2i inputPosition) {
	position = inputPosition;

	if(Randomizer::getRange(0, 1)) {
		color = SquareColor::White;
	} else {
		color = SquareColor::Black;
	}
}

Square::~Square() {

}

void Square::events(sf::Event event, sf::RenderWindow& window) {

}

void Square::logic(sf::RenderWindow& window) {

}

void Square::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::RectangleShape squareShape(sf::Vector2f(SQUARE_SIDE, SQUARE_SIDE));
	squareShape.setPosition(sf::Vector2f(position * SQUARE_SIDE));
	switch (color) {
		case SquareColor::Black:
			squareShape.setFillColor(sf::Color(0, 0, 0, 255));
			break;
		case SquareColor::White:
			squareShape.setFillColor(sf::Color(255, 255, 255, 255));
			break;
		default:
			squareShape.setFillColor(sf::Color(255,20,147, 255));
	}

	target.draw(squareShape, states);
}

void Square::stage() {

}

void Square::remove() {

}

void Square::commit(SquareColor newColor) {

}

SquareState Square::getState() {
	return SquareState::Usable;
}

SquareColor Square::getColor() {
	return SquareColor::Black;
}
