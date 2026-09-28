#ifndef PLAYER_H
#define PLAYER_H

#include <vector>
#include "raylib.h"
#include "Bullet.h"

class Player {
public:
    Vector2 position;
    Vector2 size;
    float velocity;
    int health;
    Color color;

    std::vector<Bullet> bullets;

    Player();

    // So the player doesn't move out the screen
    void clampPosition();

    void shoot(float dt);
    

    void draw();

    void controls(float dt);

    void update(float dt);
};

#endif