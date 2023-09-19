#pragma once

#include "State.h"
#include "Snake.h"
#include "ofMain.h"
#include "StaticEntity.h"

class GameState : public State {
    public:
        GameState();
        ~GameState();
        void reset();
        void update();
        void draw();
        void keyPressed(int key);
        void mousePressed(int x, int y, int button);
        void foodSpawner();
        void drawFood();
        void drawBoardGrid();

        Snake* snake;
        
        bool foodSpawned = false;

        int currentFoodX;
        int currentFoodY;
        int foodTimer = 0;
        float colorFood = 255;

        int boardSizeWidth, boardSizeHeight;
        int cellSize; // Pixels

        static int score;
        ofTrueTypeFont scoreTxt;

        vector<StaticEntity*>staticEntities;
        ofImage tree;

        bool speedPower = false;
        int frameSpeed = 10;
        int timer = 0;
        
        static std::string lastState;

        std::string powerUp = "";
        ofTrueTypeFont powerUpTxt;
};