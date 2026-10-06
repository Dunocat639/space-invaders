#ifndef PLAYER_H
#define PLAYER_H

#include "raylib.h"
#include <vector>
#include "Bullet.h"

class Player {
public:
    Vector2 position;
    Vector2 size;
    float velocity;
    int health;
    Color color;
    Texture2D texture;

    std::vector<Bullet> bullets;

    Player();
    
    void init();
    void unload();

    // So the player doesn't move out the screen
    void clampPosition();

    void shoot(float dt);
    

    void draw();

    void controls(float dt);

    void update(float dt);
};

#endif