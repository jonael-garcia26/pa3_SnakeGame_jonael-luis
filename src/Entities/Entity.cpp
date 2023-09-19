#include "Entity.h"

Entity::Entity(int x, int y, int width, int height, ofImage sprite){
    this->x = x;
    this->y = y;
    this->width = width;
    this->height = height;
    this->sprite = sprite;
}

void Entity::draw(){
    sprite.draw(x, y, width, height);
}

bool Entity::collides(Entity* entity){
    return this->getBounds().intersects(entity->getBounds());
}

ofRectangle Entity::getBounds(){
    return ofRectangle(x, y, width, height);
}