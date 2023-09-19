#include "PauseState.h"

PauseState::PauseState(){
    scoretxt.load("Minecraft.ttf", 50);
    buttonImg.load("images/Resume.png");
    PausedImg.load("images/Pause.png");
	continueButton = new Button(ofGetWidth() / 2 - xPosButton, ofGetHeight() / 2 + yPosButton, buttonImg.getWidth() * size, buttonImg.getHeight() * size, "");
}

PauseState::~PauseState(){}

void PauseState::reset(){
    setFinished(false);
	setNextState("");
	continueButton->reset();
}

void PauseState::update(){
    continueButton->update();
	if(continueButton->wasPressed()){
        GameState::lastState = "PauseState";
		setNextState("GameState");
		setFinished(true);

	}
}

void PauseState::draw(){
    ofSetBackgroundColor(0, 153, 76);
    PausedImg.draw(ofGetWidth() / 2 - 200, 50, PausedImg.getWidth() * size, PausedImg.getHeight() * size);
    buttonImg.draw(ofGetWidth() / 2 - xPosButton, ofGetHeight() / 2 + yPosButton, buttonImg.getWidth() * size, buttonImg.getHeight() * size);
    ofSetColor(ofColor::black);
    scoretxt.drawString("Score: " + to_string(GameState::score), ofGetWidth() / 2 - 110, ofGetHeight() / 2);
    continueButton->draw();
}

void PauseState::keyPressed(int key){
    if(key == 'p'){
        pause = !pause;
        GameState::lastState = "PauseState";
        setFinished(true);
        setNextState("GameState");
        return;
    }
}

void PauseState::mousePressed(int x, int y, int button){
    pause = !pause;
    continueButton->mousePressed(x, y);
}