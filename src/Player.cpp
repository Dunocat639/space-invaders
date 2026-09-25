#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"

#include "raylib.h"


class Player {
public:
    Vector2 position;
    Vector2 size;
    float velocity;
    int health;
    Color color;

    std::vector<Bullet> bullets;

    Player() {
        size = {60.0f, 60.0f};
        position = {(float)screenWidth / 2, (float)screenHeight - 75}; // At the bottom of the screen
        velocity = 700.0f;
        health = 100;
        color = GREEN;
    }

    // So the player doesn't move out the screen
    void clampPosition() {
        // Right corner
        if (position.x > (screenWidth - size.x)) {
            position.x = screenWidth - size.x;
        }
        // Left corner
        else if (position.x < 0) {
            position.x = 0;
        }
    }

    void shoot(float dt) {
        if (IsKeyPressed(KEY_SPACE) || IsMouseButtonPressed(MOUSE_LEFT_BUTTON)) {
            Bullet newBullet(Vector2 {position.x + size.x/2.0f, position.y}); // Add the vector to center the bullet to the player
            bullets.push_back(newBullet); // Add a new bullet to the bullets list
        }
        
        // Update each of the spawned bullets
        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].update(dt);

            // Eliminate non active bullets
            if (!bullets[i].active) {
                bullets.erase(bullets.begin() + i);
                i--; // All the elements in the vector moved back, so we should do this to prevent skipping a bullet
            }
        }
    }
    

    void draw() {
        DrawRectangleV(position, {size.x, size.y}, color);

        for (size_t i = 0; i < bullets.size(); i++) {
            bullets[i].draw();
        }
    }

    void controls(float dt) {
        if (IsKeyDown(KEY_LEFT)  || IsKeyDown(KEY_A)) position.x -= velocity * dt;
        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) position.x += velocity * dt;
        // We dont need vertical movement at the moment:
        // if (IsKeyDown(KEY_UP)    || IsKeyDown(KEY_W)) position.y -= velocity * dt;
        // if (IsKeyDown(KEY_DOWN)  || IsKeyDown(KEY_S)) position.y += velocity * dt;

        clampPosition();
    }

    void update(float dt) {
        controls(dt);
        shoot(dt);
    }
};