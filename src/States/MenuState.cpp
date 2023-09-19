#include "MenuState.h"

//--------------------------------------------------------------
MenuState::MenuState() {
    snakeImg.load("images/Snake.png");
    background.load("images/background.jpg");
    menutxt.load("Minecraft.ttf", 32);
}   
//--------------------------------------------------------------
MenuState::~MenuState() {

}
//--------------------------------------------------------------
void MenuState::reset() {
    setFinished(false);
    setNextState("");
    return;
}
//--------------------------------------------------------------
void MenuState::update() {

}
//--------------------------------------------------------------
void MenuState::draw() {
    ofSetColor(ofColor::white);
    background.draw(0, 0, ofGetWidth(), ofGetHeight());
    snakeImg.draw(ofGetWidth() / 2 - 450, ofGetHeight() / 2 - 385, snakeImg.getWidth() * .90, snakeImg.getHeight() * .90);
    ofSetColor(ofColor::black);
    string text = "Press any arrow key to start.";
    menutxt.drawString(text, ofGetWidth() / 2 - 250, ofGetHeight() - 80);
    return;
}
//--------------------------------------------------------------
void MenuState::keyPressed(int key) {
    if(key == OF_KEY_LEFT || key == OF_KEY_RIGHT || key == OF_KEY_UP || key == OF_KEY_DOWN) {
        GameState::lastState = "MenuState";
        setFinished(true);
        setNextState("GameState");
        return;
    }
}
//--------------------------------------------------------------
void MenuState::mousePressed(int x, int y, int button){
}
