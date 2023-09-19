#include "Snake.h"
#include "ofMain.h"

Snake::Snake(int segmentSize, int boardSizeW, int boardSizeH) {
    body.push_back({8, 9});
    body.push_back({9, 9});
    body.push_back({10, 9});
    body.push_back({11, 9});
    this->direction = LEFT;
    this->crashed = false;
    this->segmentSize = segmentSize;
    this->boardSizeWidth = boardSizeW;
    this->boardSizeHeight = boardSizeH;
}

Snake::~Snake() {
    // TODO Auto-generated destructor stub
}

void Snake::update() {
    vector<int> oldHead = this->getHead();

    switch(this->direction) {
        case LEFT: {
            this->body[0][0] -= 1;
            break;
        }
        case DOWN: {
            this->body[0][1] += 1;
            break;
        }
        case RIGHT: {
            this->body[0][0] += 1;
            break;
        }
        case UP: {
            this->body[0][1] -= 1;      
            break;
        }
        case NONE: {    // Add NONE para eliminar el warning
            break;
        }
    }

    // Si GodPowerUp esta activo y la serpiente llega al borde, la serpiente para y permite cambiar la direccion
    if (godPower && (this->body[0][0] < 0 || this->body[0][0] >= boardSizeWidth || this->body[0][1] < 0 || this->body[0][1] >= boardSizeHeight)) {
        this->body[0] = oldHead; 
        return;
    }

    if(oldHead[0] == -1 || oldHead[0] == boardSizeWidth || oldHead[1] == -1 || oldHead[1] == boardSizeHeight) {
        if(!godPower){
            crashed = true;
            return;
        } else {
            snakeStop = true;
        }
        
    }

    if(!snakeStop){     // si la serpiente toca el borde no actualiza las demas secciones del cuerpo
        int prevX = oldHead[0];
        int prevY = oldHead[1];
        for (unsigned int i = 1; i < this->body.size(); i++) {
            int currX = this->body[i][0];
            int currY = this->body[i][1];
            this->body[i][0] = prevX;
            this->body[i][1] = prevY;
            prevX = currX;
            prevY = currY;
        }
    }
    
    if(!godPower){ // cuando GodPowerUp esta activo ignora est funcion
        checkSelfCrash();
    }
   
}

void Snake::draw() {
    for (unsigned int i = 0; i < body.size(); i++) {
        int curX = this->body[i][0];
        int curY = this->body[i][1];
        
        ofSetColor(0,204,204);
        if(godPower) ofSetColor(ofColor::lightGray);
        if(i == 0){
            ofSetColor(0,255,0);
            if(godPower) ofSetColor(ofColor::purple);
        }
        ofDrawRectangle(curX * segmentSize, curY * segmentSize, segmentSize, segmentSize);
    }
}

void Snake::changeDirection(Direction d) {
    snakeStop = false;
    if(this->direction == LEFT and d == RIGHT)
        return;
    if(this->direction == RIGHT and d == LEFT) 
        return;
    if(this->direction == UP and d == DOWN) 
        return;
    if(this->direction == DOWN and d == UP)
        return;

    this->direction = d;
}

void Snake::checkSelfCrash() {
    std::vector<std::vector<int>> snake = this->body;
    vector<int> head = snake[0];
    for( unsigned int i = 1; i < snake.size(); i++) {
        if(head[0] == snake[i][0] and head[1] == snake[i][1]) {
            crashed = true;
            return;
        }
    }
}

void Snake::grow() {
    vector<int> newSegment = this->getTail();
    this->body.push_back(newSegment);
}

void Snake::shrink() { //this is the function that shrinks the snake
    if (body.size()>2){
        this->body.pop_back();
    }
    
}

void Snake::entityCrash() {
    crashed = true;
}

bool Snake::godPower = false;