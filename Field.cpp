// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: do 19-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 

 // Includes I did make myself 
#include "constants.hpp"
#include "Field.hpp"

Field::Field(sf::Vector2i inputSize, InputMethod preferredMethod) : 
	fieldView(sf::FloatRect(0, 0, inputSize.x * SQUARE_SIDE, inputSize.y * SQUARE_SIDE)) {

	size = inputSize;
	for (int x = 0; x < size.x; ++x) {
		squareField.push_back(std::vector<Square>());

		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).push_back(Square(sf::Vector2i(x, y)));
		}
	}

	inputMethod = preferredMethod;

	pointer.x = 0;
	pointer.y = 0;

	fieldView.setViewport(sf::FloatRect(0.125f, 0.125f, 0.75f, 0.75f));
}

Field::~Field() {

}

void Field::events(sf::Event event, sf::RenderWindow& window) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).at(y).events(event, window);
		}
	}

	switch (inputMethod) {
		case InputMethod::Keyboard:
			break;
		case InputMethod::Mouse:
			if (event.type == sf::Event::MouseMoved) {
				pointer.x = event.mouseMove.x;
				pointer.y = event.mouseMove.y;

				pointer = sf::Vector2i(window.mapPixelToCoords(pointer, fieldView)) / SQUARE_SIDE;
			}
			break;
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
	sf::View previousView = target.getView();
	target.setView(fieldView);

	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			target.draw(squareField.at(x).at(y), states);
		}
	}

	sf::RectangleShape pointerPlace(sf::Vector2f(SQUARE_SIDE, SQUARE_SIDE));
	pointerPlace.setPosition(sf::Vector2f(pointer * SQUARE_SIDE));
	pointerPlace.setFillColor(sf::Color::Red);
	target.draw(pointerPlace, states);

	target.setView(previousView);
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
