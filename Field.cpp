// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: do 19-12-2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <iostream>
#include <cmath>

 // Includes I did make myself 
#include "constants.hpp"
#include "functions.hpp"
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
	previousPointer = pointer;
	pointerChanged = false;

	fieldView.setViewport(sf::FloatRect(0.125f, 0.125f, 0.75f, 0.75f));

	state = FieldState::Idle;
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
			// TODO
			break;
		case InputMethod::Mouse:
			if (event.type == sf::Event::MouseMoved) {
				pointerChanged = true;

				newPointer.x = event.mouseMove.x;
				newPointer.y = event.mouseMove.y;

				newPointer = sf::Vector2i(window.mapPixelToCoords(newPointer, fieldView));

				newPointer.x = floor(newPointer.x / (float)SQUARE_SIDE);
				newPointer.y = floor(newPointer.y / (float)SQUARE_SIDE);

				// std::cout << pointer.x << " | " << pointer.y << "\n";
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					if (inRange(pointer.x, 0, size.x) && inRange(pointer.y, 0, size.y)) {
						state = FieldState::Drawing;
						squareField.at(pointer.x).at(pointer.y).stage();
						chain.push(sf::Vector2f(pointer) + sf::Vector2f(SQUARE_SIDE / 2, SQUARE_SIDE / 2), squareField.at(pointer.x).at(pointer.y).getRgbColor());
					}
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					// TODO
					state = FieldState::Idle;	
				}
			}
			break;
	}
}

void Field::logic(sf::RenderWindow& window) {
	switch (state) {
		case FieldState::Idle:
			// Would be suprised if there would be code here...
			break;
		case FieldState::Drawing:
			if (pointerChanged) {
				pointerChanged = false;
				chain.push(sf::Vector2f(newPointer * SQUARE_SIDE) + sf::Vector2f(SQUARE_SIDE / 2, SQUARE_SIDE / 2), squareField.at(newPointer.x).at(newPointer.y).getRgbColor());

				previousPointer = pointer;
				pointer = newPointer;
			}
			break;
	}

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

	target.draw(chain, states);

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

FieldState Field::getState() {
	return state;
}