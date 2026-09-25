#ifndef ENEMY_H
#define ENEMY_H

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
        size;
        position;
        velocity;
        health;
        color; 
        active;
    }

    void draw();

    void takeDamage();

    void die();

    void checkCollisionBullet(std::vector<Bullet>& bullets);

    void update(std::vector<Bullet>& bullets);
};

#endif