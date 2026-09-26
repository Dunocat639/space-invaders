#ifndef BULLET_H
#define BULLET_H

class Bullet {
public:
    Vector2 position;
    float size;
    float velocity;
    Color color;
    bool active;

    Bullet(Vector2 originPos) {
        size;
        position; // The bullet spawns where the player is at the moment of the shoot
        velocity;
        color;   
        active;
    }

    void update(float dt);

    void draw();

};

#endif