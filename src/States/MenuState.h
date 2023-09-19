#pragma once

#include "State.h"
#include "GameState.h"

class MenuState : public State {
private:
    ofImage snakeImg, background;
    ofTrueTypeFont menutxt;

public:
    MenuState();
    ~MenuState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

};