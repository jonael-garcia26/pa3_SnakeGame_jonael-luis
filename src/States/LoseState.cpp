#include "LoseSate.h"

LoseState::LoseState(){
    skull.load("images/8-bit-skull.png");
    scoretxt.load("Minecraft.ttf", 20);
}

LoseState::~LoseState(){}

void LoseState::reset(){
    setFinished(false);
    setNextState("");
    
}

void LoseState::update(){}

void LoseState::draw(){
    ofSetBackgroundColor(ofColor::red);
    ofSetColor(ofColor::white);
    skull.draw(ofGetWidth() / 2 - 385, ofGetHeight() / 2 - 400, skull.getWidth()* 1.50, skull.getHeight()* 1.50);
    ofSetColor(ofColor::black);
    scoretxt.drawString("Score: " + to_string(GameState::score), ofGetWidth() / 2 - 55, ofGetHeight() / 2 - 190);
    string text = "You lost! Press any arrow key to play again,";
    string text2 = "Press ENTER for the menu or ESC to exit.";
    ofDrawBitmapString(text, ofGetWidth()/2-8*text.length()/2, ofGetHeight()/2-140);
    ofDrawBitmapString(text2, ofGetWidth()/2-8*text2.length()/2, ofGetHeight()/2-120);
    return;

}

void LoseState::keyPressed(int key){
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        GameState::lastState = "LoseState";
        setFinished(true);
        setNextState("GameState");
    }
    if(key == OF_KEY_RETURN){
        GameState::lastState = "LoseState";
        setFinished(true);
        setNextState("MenuState");
    }
}

void LoseState::mousePressed(int x, int y, int button){
}