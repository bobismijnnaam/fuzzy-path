// Author: Bob Rubbens - Knights of the Compiler
// Creation date: do 19-12-2013
// Contact: http://knightsofthecompiler.worpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef SQUARE_HPP
#define SQUARE_HPP

// Includes I didn't make myself
#include <SFML/Graphics.hpp>

 // Includes I did make myself

enum class SquareColor {
	Black,
	White,
	LowerGrey,
	UpperGrey
} ;

enum class SquareState {
	Usable,
	Used
} ;

class Square : public sf::Drawable {
public:
	Square(sf::Vector2i inputPosition);
	~Square();

	void events(sf::Event event, sf::RenderWindow& window);
	void logic(sf::RenderWindow& window);
	void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	void stage();
	void remove();
	void commit(SquareColor newColor);

	SquareState getState();
	SquareColor getColor();
	SquareColor getNormalizedColor();
	sf::Color getRgbColor();

	static sf::Color Blue;
	static sf::Color Orange;
	static sf::Color High;
	static sf::Color Low;

private:
	SquareColor color;
	SquareState state;
	sf::Vector2i position;
	sf::Color rgbColor;
};

#endif
