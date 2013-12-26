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
#include "Randomizer.hpp"

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

	// pointerChanged = false;

	fieldView.setViewport(sf::FloatRect((SCR_W - FIELD_SIDE) / (float)(2 * SCR_W), (SCR_H - FIELD_SIDE) / (float)(2 * SCR_H), FIELD_SIDE / (float)SCR_W, FIELD_SIDE / (float)SCR_H));

	state = FieldState::Idling;

	whites = 100;
	blacks = 100;
	total = 0;
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
							tp.x = floor(tp.x / (float)SQUARE_SIDE) * SQUARE_SIDE + SQUARE_SIDE / 2;
							tp.y = floor(tp.y / (float)SQUARE_SIDE) * SQUARE_SIDE + SQUARE_SIDE / 2;

							if (chain.queue(sf::Vector2f(tp), squareField.at(tp.x / SQUARE_SIDE).at(tp.y / SQUARE_SIDE).getRgbColor()) == QueueMessage::Violation) {
								state = FieldState::Committing;
							}
						}
						break;
					default:
						break;
				}
			} else if (event.type == sf::Event::MouseButtonPressed) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					tp = sf::Vector2i(event.mouseButton.x, event.mouseButton.y);
					tp = sf::Vector2i(window.mapPixelToCoords(tp, fieldView));

					if (inRange(tp.x, 0, SQUARE_SIDE * size.x) && inRange(tp.y, 0, SQUARE_SIDE * size.y) && state == FieldState::Idling) {
						state = FieldState::Drawing;

						tp.x = floor(tp.x / (float)SQUARE_SIDE) * SQUARE_SIDE + SQUARE_SIDE / 2;
						tp.y = floor(tp.y / (float)SQUARE_SIDE) * SQUARE_SIDE + SQUARE_SIDE / 2;
						chain.queue(sf::Vector2f(tp), squareField.at(tp.x / SQUARE_SIDE).at(tp.y / SQUARE_SIDE).getRgbColor());
					}
				}
			} else if (event.type == sf::Event::MouseButtonReleased) {
				if (event.mouseButton.button == sf::Mouse::Left) {
					if (state == FieldState::Drawing) {
						state = FieldState::Committing;
					}
				}
			}

			break;
		default:
			break;
	}
}

void Field::logic(sf::RenderWindow& window) {
	std::vector<sf::Vector2i> pointChain;
	int subtotal = 0;
	SquareColor previousColor, tc;

	switch (state) {
		case FieldState::Idling:
			// Would be suprised if there would be code here...
			break;
		case FieldState::Drawing:
			// There should be some code here though!



			// Naaah.
			break;
		case FieldState::Committing:
			pointChain = chain.getChain();
			if (pointChain.size() > 1) {
				subtotal = 1;
				
				previousColor = at(pointChain.at(0)).getNormalizedColor();
				for (uint32_t i = 1; i < pointChain.size(); ++i) {
					if (previousColor != at(pointChain.at(i)).getNormalizedColor()) {
						subtotal += i + 1;
						previousColor = at(pointChain.at(i)).getNormalizedColor();
					} else {
						subtotal -= i + 1;
					}

					if (blacks == 0 && whites == 0) {
						// GAME ENDS B*TCH
					} else if (blacks == 0) {
						tc = SquareColor::White;
						--whites;
					} else if (whites == 0) {
						tc = SquareColor::Black;
						--blacks;
					} else if (Randomizer::getRange(0, 1)) {
						tc = SquareColor::White;
						whites--;
					} else {
						tc = SquareColor::Black;
						blacks--;
					}	
					
					at(pointChain.at(i)).commit(tc);
				}

				total += subtotal;
			}

			chain.commit();
			state = FieldState::Idling;
			
			std::cout << "Score: " << total << " | Subtotal = " << subtotal << " | w/b = " << whites << "/" << blacks << "\n";
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

	chain.logic();
}

void Field::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::View previousView = target.getView();
	target.setView(fieldView);

	for (int x = 0; x < size.x; ++x) {
		for (int y = 0; y < size.y; ++y) {
			target.draw(squareField.at(x).at(y), states);
		}
	}

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

Square& Field::at(sf::Vector2i p) {
	return squareField.at(p.x).at(p.y);
}

FieldState Field::getState() {
	return state;
}