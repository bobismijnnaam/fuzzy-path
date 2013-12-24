// Author: Bob Rubbens - Knights of the Compiler 
// Creation date: 24/12/2013 
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens) 

// Includes I didn't make myself 
#include <iostream>
#include "SFML/Graphics.hpp"

 // Includes I did make myself 
#include "Chain.hpp"
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
		// Why? For the glory of satan ofcourse!
	} else {
		std::cout << "Tried to pop from empty stack @ Chain::pop()\n";
	}
}

void Chain::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	if (points.size() >= 2) {
		target.draw(&points[0], points.size(), sf::Lines, states);
	}
}

int Chain::getChainScore() {
	
	return 0;
}

int Chain::getChainLength() {
	if (points.size() <= 1) {
		return 0;
	} else {
		return points.size() / 2;
	}
}

int Chain::getArrayLength() {
	return points.size();
}
