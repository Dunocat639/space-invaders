#ifndef BULLET_H
#define BULLET_H

#include "raylib.h"

class Bullet {
public:
    Vector2 position;
    float size;
    float velocity;
    Color color;
    bool active;

    Bullet(Vector2 originPos);

    void update(float dt);

    void draw();

};

#endif