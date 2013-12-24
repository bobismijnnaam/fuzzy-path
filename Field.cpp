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

	pointerChanged = false;

	fieldView.setViewport(sf::FloatRect(0.125f, 0.125f, 0.75f, 0.75f));

	state = FieldState::Idling;
}

Field::~Field() {

}

void Field::events(sf::Event event, sf::RenderWindow& window) {
	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			squareField.at(x).at(y).events(event, window);
		}
	}

	sf::Vector2i tp;

	switch (inputMethod) {
		case InputMethod::Keyboard:
			// TODO
			break;
		case InputMethod::Mouse:
			if (event.type == sf::Event::MouseMoved) {
				switch (state) {
					case FieldState::Drawing:
						tp = sf::Vector2i(event.mouseMove.x, event.mouseMove.y);
						tp = sf::Vector2i(window.mapPixelToCoords(tp, fieldView));

						if (!(inRange(tp.x, 0, SQUARE_SIDE * size.x) && inRange(tp.y, 0, SQUARE_SIDE * size.y))) {
							state = FieldState::Committing;
						} else {
							tp.x = floor(tp.x / (float)SQUARE_SIDE);
							tp.y = floor(tp.y / (float)SQUARE_SIDE);
							// TODO: Make sure that you can't travel over a point that you have passed,
							// Unless it is the previous point (that should be added to the list)
							if (tp != points.at(points.size() - 1)) {
								pointerChanged = true;
								points.push_back(tp);
							}
						}
						break;
					default:
						break;
				}

				// std::cout << "Mousemove\n";
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					tp = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					tp = sf::Vector2i(window.mapPixelToCoords(tp, fieldView));

					std::cout << event.mouseButton.x << " | " << event.mouseButton.y << ";\n";
					std::cout << tp.x << " | " << tp.y << ";\n";

					if (inRange(tp.x, 0, SQUARE_SIDE * size.x) && inRange(tp.y, 0, SQUARE_SIDE * size.y)) {
						state = FieldState::Drawing;
						pointerChanged = true;

						points.push_back( sf::Vector2i( floor( tp.x / (float)SQUARE_SIDE ), floor( tp.y / (float)SQUARE_SIDE ) ) );

						std::cout << "Drawing started!\n";
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Button::Left) {
					state = FieldState::Committing;
				}
			}
			break;
		}
	}
}

void Field::logic(sf::RenderWindow& window) {
	switch (state) {
		case FieldState::Idling:
			// Would be suprised if there would be code here...
			break;
		case FieldState::Drawing:
			// TODO: Handle diagonal line drawing. Yes, it happens! T_T
			if (pointerChanged) {
				pointerChanged = false;
				if (points.size() < 3) {
					sf::Vector2i p = points.at(points.size() - 1);
					chain.push(sf::Vector2f(p * SQUARE_SIDE) + sf::Vector2f(SQUARE_SIDE / 2, SQUARE_SIDE / 2), squareField.at(p.x).at(p.y).getRgbColor());
					squareField.at(p.x).at(p.y).stage();
				} else {
					int i = points.size() - 1;
					
					if (points.at(i) == points.at(i - 2)) {
						// Player took a step back
						squareField.at(points.at(i - 1).x).at(points.at(i - 1).y).remove();
						chain.pop();
						points.pop_back();
						points.pop_back();
					} else {
						// Player advanced one step
						sf::Vector2i p = points.at(points.size() - 1);
						chain.push(sf::Vector2f(p * SQUARE_SIDE) + sf::Vector2f(SQUARE_SIDE / 2, SQUARE_SIDE / 2), squareField.at(p.x).at(p.y).getRgbColor());
						squareField.at(p.x).at(p.y).stage();
					}
				}
			}
			break;
		case FieldState::Committing:
			// TODO: Make committing a trajectory possible
			break;
		default:
			std::cout << "Invalid state @ Field::logic()\n";
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

	/*
	sf::RectangleShape pointerPlace(sf::Vector2f(SQUARE_SIDE, SQUARE_SIDE));
	pointerPlace.setPosition(sf::Vector2f(pointer * SQUARE_SIDE));
	pointerPlace.setFillColor(sf::Color::Red);
	target.draw(pointerPlace, states);
	*/

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