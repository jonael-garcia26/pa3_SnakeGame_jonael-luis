#pragma once

#include "State.h"
#include "GameState.h"

class LoseState : public State{
    private:
        ofImage skull;
        ofTrueTypeFont scoretxt;
    public:
        LoseState();
        ~LoseState();

        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);

        
};