#pragma once

#include "State.h"
#include "Button.h"
#include "GameState.h"

class PauseState : public State {
private:
    Button *continueButton;
    ofImage buttonImg;
    ofImage PausedImg;
    ofTrueTypeFont scoretxt;
    

public:
    PauseState();
    ~PauseState();
    void reset();
    void update();
    void draw();
    void keyPressed(int key);
    void mousePressed(int x, int y, int button);

    int size = 1.75;
    int xPosButton = 120;
    int yPosButton = 140;

};