// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: do 19-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <iostream>

 // Includes I did make myself
#include "constants.hpp"
#include "Randomizer.hpp"
#include "Square.hpp" 

Square::Square(sf::Vector2i inputPosition) {
	position = inputPosition;

	if(Randomizer::getRange(0, 1)) {
		color = SquareColor::White;
		rgbColor = sf::Color(255, 255, 255, 255);
	} else {
		color = SquareColor::Black;
		rgbColor = sf::Color(0, 0, 0, 255);
	}

	state = SquareState::Usable;
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
			squareShape.setFillColor(rgbColor);
			break;
		case SquareColor::White:
			squareShape.setFillColor(rgbColor);
			break;
		case SquareColor::UpperGrey:
			// squareShape.setFillColor(sf::Color(235, 235, 235, 255));
			squareShape.setFillColor(rgbColor);
			break;
		case SquareColor::LowerGrey:
			// squareShape.setFillColor(sf::Color(85, 85, 85, 255));
			squareShape.setFillColor(rgbColor);
			break;
		default:
			squareShape.setFillColor(sf::Color(255,20,147, 255));
			break;
	}

	target.draw(squareShape, states);
}

// TODO: When staged, square gets marked with it's position in the current chain
void Square::stage() {
	switch (color) {
		case SquareColor::Black:
			color = SquareColor::LowerGrey;
			break;
		case SquareColor::White:
			color = SquareColor::UpperGrey;
			break;
		default:
			std::cout << "Error @ Square::stage(): Square was not in binary (black/white) state";
			break;
	}

	state = SquareState::Used;
}

void Square::remove() {
	switch (color) {
		case SquareColor::UpperGrey:
			color = SquareColor::White;
			break;
		case SquareColor::LowerGrey:
			color = SquareColor::Black;
			break;
		default:
			std::cout << "Error @ Square::remove(): Square was not in float (upper/lower grey) state";
			break;
	}

	state = SquareState::Usable;
}

void Square::commit(SquareColor newColor) {
	color = newColor;

	switch (color) {
		case SquareColor::White:
			rgbColor = sf::Color::White;
			break;
		case SquareColor::Black:
			rgbColor = sf::Color::Black;
			break;
	}

	state = SquareState::Usable;
}

SquareState Square::getState() {
	return state;
}

SquareColor Square::getColor() {
	return color;
}

SquareColor Square::getNormalizedColor() {
	switch (color) {
		case SquareColor::White:
		case SquareColor::UpperGrey:
			return SquareColor::White;
			break;
		case SquareColor::Black:
		case SquareColor::LowerGrey:
			return SquareColor::Black;
			break;
	}
}

sf::Color Square::getRgbColor() {
	return rgbColor;
}