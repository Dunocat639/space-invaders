#ifndef ENEMY_H
#define ENEMY_H

#include "raylib.h"
#include <vector>

#include "Bullet.h"

class Enemy {
public:
    Vector2 position;
    float size;
    float velocity;
    int health;
    Color color;
    bool active;
    Rectangle body;
    //Texture2D texture;

    Enemy();

    void init();

    void unload();

    void draw();

    void takeDamage();

    void die();

    void checkCollisionBullet(std::vector<Bullet>& bullets);

    void update(std::vector<Bullet>& bullets);
};

#endif