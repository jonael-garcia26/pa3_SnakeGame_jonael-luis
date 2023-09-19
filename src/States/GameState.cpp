#include "GameState.h"

//--------------------------------------------------------------
GameState::GameState() {
    foodSpawned = false;
    cellSize = 25;
    boardSizeWidth = 64;
    boardSizeHeight = 36;
    snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
    scoreTxt.load("Minecraft.ttf", 20);
    powerUpTxt.load("Minecraft.ttf", 15);
}
//--------------------------------------------------------------
GameState::~GameState() {
    delete snake;
}
//--------------------------------------------------------------
void GameState::reset() {
    if(GameState::lastState != "PauseState"){   // Si el State anterior no es Pause, no borra los datos al volver a Game
        staticEntities.clear(); //this clears the entities so that new ones spawn everytime the snake dies
        delete snake;
        snake = new Snake(cellSize, boardSizeWidth, boardSizeHeight);
        foodSpawned = false;
        GameState::score = 0;

        tree.load("sprites/treesprite.png"); //this is the sprite image 
        for (int i=0; i<15; i++){ //this loops adds all the random entities
            int entityX = ofRandom(1, boardSizeWidth-1); 
            int entityY = ofRandom(1, boardSizeHeight-1);
            StaticEntity* entity = new StaticEntity(entityX*cellSize, entityY*cellSize, cellSize, cellSize,tree);
            staticEntities.push_back(entity);
        }
    }
    setFinished(false);
    setNextState("");

    powerUp = "";
    speedPower = false;
}
//--------------------------------------------------------------
void GameState::update() {
    if(!Snake::godPower){       // Si GodMode esta activo, ignora este pedazo de code y activa el timer
        if(snake->isCrashed()) {
        GameState::lastState = "GameState";
        this->setNextState("LoseState");
        this->setFinished(true);
        return;
        }
    } else {
        if(ofGetElapsedTimef() - timer >= 10){
            Snake::godPower = false;
        }
    }

    if(foodSpawned && score != 50 && score != 100 && score != 150 && ofGetElapsedTimef() - foodTimer >= 30) {
        foodSpawned = false;
    }

    if(snake->getHead()[0] == currentFoodX && snake->getHead()[1] == currentFoodY) {

        snake->grow();

        foodSpawned = false;
        score = score + 10;
                                // Cuando la serpiente come la manzana de su respectivo score se activa la opcion de su powerUp
        if(score == 60){
            powerUp = "SpeedBoost";
        } else if(score == 110){
            powerUp = "BetterApple";
        } else if(score == 160){
            powerUp = "GodMode";
        }
    }

    foodSpawner();
    if(speedPower){     // Si el speedBoost se utiliza, los frames por segundo para la serpiente cambian y se mueve mas rapido por 15s
        frameSpeed = 5;
        if(ofGetElapsedTimef() - timer >= 15){
            speedPower = false;
        }
    } else {
        frameSpeed = 10;
    }
    if(ofGetFrameNum() % frameSpeed == 0){
        snake->update();
    }

    if(!Snake::godPower){
        for (unsigned int i=0; i<staticEntities.size(); i++){ //this loop checks if the snake has collided with a entity, if so, the snake dies
            if(snake->getHead()[0] == staticEntities[i]->getX()/cellSize && snake->getHead()[1] == staticEntities[i]->getY()/cellSize){
                snake->entityCrash();
            }
        }
    }

}
//--------------------------------------------------------------
void GameState::draw() {
    ofSetBackgroundColor(96,96,96);
    drawBoardGrid();
    snake->draw();

    for (auto entity : staticEntities) { // this loop draws the entities 
        entity->draw();
    }
    
    drawFood();

    ofSetColor(255);
    scoreTxt.drawString("Score: " + to_string(score), ofGetWidth() / 2 - 30, 25);

    if(powerUp != ""){
        powerUpTxt.drawString("Current Power-up: " + powerUp, ofGetWidth() / 2 - 110, 50);
    }
}
//--------------------------------------------------------------
void GameState::keyPressed(int key) {

    switch(key) {
        case OF_KEY_LEFT:
            snake->changeDirection(LEFT);
            break;
        case OF_KEY_RIGHT:
            snake->changeDirection(RIGHT);
            break;
        case OF_KEY_UP:
            snake->changeDirection(UP);
            break;
        case OF_KEY_DOWN:
            snake->changeDirection(DOWN);
            break;
        case 'a':   //debug key for adding 10 points
            score+=10;
            break;
        case 'u':   //shrinks the snake when pressed 
            snake->shrink();
            break;
        case 'p':       // Al precionar P pausa el juego
            GameState::lastState = "GameState";
            setNextState("PauseState");
		    setFinished(true);
        case 'b':       // Activate power-up
            if(powerUp != ""){
                if(powerUp == "SpeedBoost"){        // aumenta la velocidad de la serpiente por 15s
                    speedPower = true;
                    timer = ofGetElapsedTimef();
                } else if(powerUp == "BetterApple"){    // aumenta dos segmentos cuando BetterApple se activa
                    snake->grow();  
                    snake->grow();
                } else if(powerUp == "GodMode"){    // vuelve la serpiente inmortal por 10s
                    Snake::godPower = true;
                    timer = ofGetElapsedTimef();
                }
                powerUp = "";
            }
            break;
    }
}
//--------------------------------------------------------------

void GameState::mousePressed(int x, int y, int button){
}

//--------------------------------------------------------------
void GameState::foodSpawner() {
        if(!foodSpawned) {
            bool isInSnakeBody;
            bool isInEntity;
            do {
                isInSnakeBody = false;
                isInEntity = false;
                currentFoodX = ofRandom(1, boardSizeWidth-1);
                currentFoodY = ofRandom(1, boardSizeHeight-1);
                for (unsigned int i = 0; i < staticEntities.size(); i++){ //this loop makes sure that the food does not spawn inside an entity
                    if (currentFoodX == staticEntities[i]->getX()/cellSize && currentFoodY == staticEntities[i]->getY()/cellSize){
                        isInEntity = true;
                    }
                }
                for(unsigned int i = 0; i < snake->getBody().size(); i++) {
                    if(currentFoodX == snake->getBody()[i][0] and currentFoodY == snake->getBody()[i][1]) {
                        isInSnakeBody = true;
                    }
                }
            } while(isInSnakeBody && isInEntity);
            foodSpawned = true;
            foodTimer = ofGetElapsedTimef();
        }
}
//--------------------------------------------------------------
void GameState::drawFood() {
    
    if(foodSpawned) {
                            // Depende de el score necesario por powerUp cambia el color del powerUp
        if(score == 50){
            ofSetColor(ofColor::blue);
        } else if(score == 100){
            ofSetColor(ofColor::green);
        } else if(score == 150){
            ofSetColor(ofColor::yellow);
        } else {
            ofSetColor(255 - ((ofGetElapsedTimef() - foodTimer) * 6), 0, 0);
        }

        ofDrawRectangle(currentFoodX*cellSize, currentFoodY*cellSize, cellSize, cellSize);
    }
}
//--------------------------------------------------------------
void GameState::drawBoardGrid() {
    
    ofSetColor(255,153,204);
    for(int i = 0; i <= boardSizeWidth; i++) {
        ofDrawLine(i*cellSize, 0, i*cellSize, ofGetHeight());
    }
    for(int i = 0; i <= boardSizeHeight; i++) {
        ofDrawLine(0, i*cellSize, ofGetWidth(), i*cellSize);
    }
}
//--------------------------------------------------------------

int GameState::score = 0;

std::string GameState::lastState = "";