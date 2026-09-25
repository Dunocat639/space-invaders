#include "Bullet.h"
#include "Player.h"

#include "raylib.h"

class Bullet {
public:
    Vector2 position;
    float size;
    float velocity;
    Color color;
    bool active;

    Bullet(Vector2 originPos) {
        size = 10.0f;
        position = originPos; // The bullet spawns where the player is at the moment of the shoot
        velocity = 1500.0f;
        color = YELLOW;   
        active = true;
    }

    void update(float dt) {
        position.y -= velocity * dt;

        // If no longer in screen
        if (position.y < (0 - size)) {
            active = false;
        }
    }

    void draw() {
        DrawCircleV(position, size, color);
    }

};