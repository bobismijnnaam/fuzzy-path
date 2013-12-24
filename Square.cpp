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
			squareShape.setFillColor(sf::Color(235, 235, 235, 255));
			break;
		case SquareColor::LowerGrey:
			squareShape.setFillColor(sf::Color(85, 85, 85, 255));
			break;
		default:
			squareShape.setFillColor(sf::Color(255,20,147, 255));
			break;
	}

	target.draw(squareShape, states);
}

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
}

void Square::commit(SquareColor newColor) {

}

SquareState Square::getState() {
	return SquareState::Usable;
}

SquareColor Square::getColor() {
	return SquareColor::Black;
}

sf::Color Square::getRgbColor() {
	return rgbColor;
}