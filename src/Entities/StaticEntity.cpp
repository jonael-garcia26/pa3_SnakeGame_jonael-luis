#include "StaticEntity.h"
#include "ofMain.h"

StaticEntity::StaticEntity(int x, int y, int width, int height, ofImage sprite) : Entity(x, y, width, height, sprite) {
}

void StaticEntity::draw() {
    sprite.draw(this->x, this->y, this->width, this->height);
    
}

