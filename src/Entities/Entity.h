#pragma once

#pragma once
#include "ofMain.h"

class Entity {
  protected:
    int x, y, width, height;
    ofImage sprite;

  public:
    explicit Entity(int x, int y, int width, int height, ofImage sprite);
    virtual void draw();
    bool collides(Entity *entity);
    ofRectangle getBounds();

    int getX() { return x; }
    int getY() { return y; }
    int getWidth() { return width; }
    int getHeight() { return height; }
    void setY(int y) { this->y = y; }
    void setX(int x) { this->x = x; }
};