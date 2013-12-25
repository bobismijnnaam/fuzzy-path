// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: 24/12/2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <iostream>
#include <cmath>
#include "SFML/Graphics.hpp"

 // Includes I did make myself 
#include "Chain.hpp"
#include "constants.hpp"
#include "functions.hpp"

Chain::Chain() {

}

Chain::~Chain() {

}

void Chain::push(sf::Vector2f point, sf::Color pointColor) {
	if (points.size() <= 1) {
		points.push_back(sf::Vertex(point, invertColor(pointColor)));
	} else {
		// Pushes end of last line and new point to extend the line segment
		points.push_back(points.at(points.size() - 1));
		points.push_back(sf::Vertex(point, invertColor(pointColor)));
	}

	pointChain.push_back(sf::Vector2i(point) / SQUARE_SIDE);
}

void Chain::push(sf::Vertex point) {
	if (points.size() <= 1) {
		points.push_back(point);
	} else {
		points.push_back(points.at(points.size() - 1));
		points.push_back(point);
	}
	
	pointChain.push_back(sf::Vector2i(point.position) / SQUARE_SIDE);
}

void Chain::pop() {
	if (points.size() == 1) {
		points.pop_back();
	} else if (points.size() == 2) {
		points.pop_back();
	} else if (points.size() > 2) {
		// Pop a whole line segment! :D
		points.pop_back();
		points.pop_back();
		// Why? For the glory of Satan ofcourse!
	} else {
		std::cout << "Tried to pop from empty stack @ Chain::pop()\n";
	}

	pointChain.pop_back();
}

QueueMessage Chain::queue(sf::Vector2f point, sf::Color pointColor) { 
	// TODO: Make sure that you can't travel over a point that you have passed,
		// Unless it is the previous point (that should be added to the list)
	// TODO: Committing

	int dx, dy;
	if (pointChain.size() == 0) {
		dx = 0;
		dy = 0;
	} else {
		dx = floor(point.x / SQUARE_SIDE) - pointChain.back().x;
		dy = floor(point.y / SQUARE_SIDE) - pointChain.back().y;
	}

	bool alreadyAdded = containsPoint(sf::Vector2i(point) / SQUARE_SIDE);

	// std::cout << dx << " | " << dy << " | " << pointChain.size() << ";\n";

	if (abs(dx) > 1 || abs(dy) > 1 || (abs(dx) == 1 && abs(dy) == 1)) {
		// std::cout << "Violation\n";
		return QueueMessage::Violation;
	} else {
		if (pointChain.size() < 2) {
			if (!alreadyAdded) {
				push(point, pointColor);
				// std::cout << "Succes\n";
				return QueueMessage::Success;
			} else {
				// std::cout << "Failure\n";
				return QueueMessage::Failure;
			}
		} else if (pointChain.size() == 2) {
			if (sf::Vector2i(point) / SQUARE_SIDE == pointChain.at(0)) {
				pop();
				// std::cout << "Rewind\n";
				return QueueMessage::Rewind;
			} else if (!alreadyAdded) {
				push(point, pointColor);
				// std::cout << "Success\n";
				return QueueMessage::Success;
			} else {
				// std::cout << "Failure\n";
				return QueueMessage::Failure;
			}
		} else if (pointChain.size() > 2) {
			if (sf::Vector2i(point) / SQUARE_SIDE == pointChain.at(pointChain.size() - 2)) {
				// Player took a step back
				pop();
				// std::cout << "Rewind\n";
				return QueueMessage::Rewind;
			} else if (!alreadyAdded) {
				// Player advanced one step
				push(point, pointColor);
				// std::cout << "Success\n";
				return QueueMessage::Success;
			} else if (sf::Vector2i(point) / SQUARE_SIDE == pointChain.back()) {
				// std::cout << "Failure\n";
				return QueueMessage::Failure;
			} else {
				// std::cout << "Violation\n";
				return QueueMessage::Violation;
			}
		}
	}

	// std::cout << "Failure\n";
	return QueueMessage::Failure;
}

void Chain::commit() {
	points.clear();
	pointChain.clear();
}

void Chain::logic() {

}

void Chain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (points.size() > 1) {
		target.draw(&points[0], points.size(), sf::Lines, states);
	}
}

int Chain::getChainLength() {
	if (points.size() <= 1) {
		return 0;
	} else {
		return points.size() / 2;
	}
}

std::vector<sf::Vector2i> Chain::getChain() {
	return pointChain;
}

int Chain::getArrayLength() {
	return points.size();
}

bool Chain::containsPoint(sf::Vector2i testPoint) {
	for (sf::Vector2i p : pointChain) {
		if (testPoint == p) {
			return true;
		}
	}

	return false;
}