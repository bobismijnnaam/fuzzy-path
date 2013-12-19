// Author: Bob Rubbens - Knights of the Compiler
// Creation date: 17-12-13
// Contact: http://knightsofthecompiler.wordpress.com - @broervanlisa - gmail (bobrubbens)

// Includes I didn't make myself


// Includes I did make myself
#include "gamestate.hpp"
#include "Game.hpp"
#include "Menu.hpp"

GameMan::GameMan(GameStates startState) {
    switch (startState) {
        case STATE_GAME:
            this->currState = new Game();
            break;
        case STATE_MENU:
            this->currState = new Menu();
            break;
        default:
            this->currState = new Game();
            break;
    }

    this->stateID = startState;
    this->nextState = STATE_NULL;

    diff = 2;
    snd = true;
}

GameMan::~GameMan() {
    delete this->currState;
}

int GameMan::setNextState(GameStates targetState) {
    if (this->nextState != STATE_EXIT) {
        this->nextState = targetState;
    }

    return 0;
}

int GameMan::changeState() {
    if (this->nextState != STATE_NULL) {
        if (this->nextState != STATE_EXIT) {
            delete this->currState;

            switch (this->nextState) {
                case STATE_GAME:
                    this->currState = new Game();
                    break;
                case STATE_MENU:
                    this->currState = new Menu();
                    break;
                default:
                    this->currState = new Game();
                    break;
            }

            this->stateID = this->nextState;
            this->nextState = STATE_NULL;
        } else {
            this->stateID = STATE_EXIT;
        }
    }

    return 0;
}

GameStates GameMan::getState() {
    return this->stateID;
}