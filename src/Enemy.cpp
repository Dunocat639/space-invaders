#include "Enemy.h"
#include "Constants.h"


class Enemy {
public:
    Vector2 position;
    float size;
    float velocity;
    int health;
    Color color;
    bool active;
    Rectangle body;

    Enemy() {
        size = 45.0f;
        position = {(float)screenWidth / 2, (float)screenHeight / 8}; // Upper side of the screen
        velocity = 1000.0f;
        health = 100;
        color = RED; 
        active = true;
    }

    void Enemy::draw() {
        if(active) DrawRectangleRec(body, color);
    }
 
    void Enemy::takeDamage() {
        health -= 50;
    }

    void Enemy::die() {
        active = false;
    }

    void Enemy::checkCollisionBullet(std::vector<Bullet>& bullets) {
        if (!active) return;
        for (size_t i = 0; i < bullets.size(); i++) {
            if (CheckCollisionCircleRec(bullets[i].position, bullets[i].size, body) && bullets[i].active) {
                takeDamage();
                bullets[i].active = false;
            }
        }

    }

    void Enemy::update(std::vector<Bullet>& bullets) {
        body = {position.x, position.y, size, size};
        checkCollisionBullet(bullets);
        if (health <= 0) {
            die();
        }
    }

};