// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 17-12-13
// Contact: http://knightsofthecompiler.wordpress.com - @broervanlisa - gmail (bobrubbens)

#ifndef GAMESTATE_H
#define GAMESTATE_H

// Includes I didn't make myself
#include <SFML/Graphics.hpp>

// Includes I did make myself


enum GameStates {
    STATE_NULL,
    STATE_GAME,
    STATE_MENU,
    STATE_EXIT
};

class GameState {           
public:
    virtual int events(sf::RenderWindow& window) = 0;
    virtual int logic(sf::RenderWindow& window) = 0;
    virtual int render(sf::RenderWindow& window) = 0;

    virtual ~GameState(){};
private:
	
} ;

class GameMan {
public:
    ~GameMan();
    GameMan(GameStates startState);

    GameState* currState;

    int setNextState(GameStates targetState);
    GameStates getState();
    int changeState();

    int diff;
    bool snd;

private:
    GameStates nextState;
    GameStates stateID;
} ;

#endif