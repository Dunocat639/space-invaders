#include "raylib.h"
#include <vector>
#include "raymath.h"

int screenWidth = 700;
int screenHeight = 500;

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

    void draw() {
        if(active) DrawRectangleRec(body, color);
    }
 
    void takeDamage() {
        health -= 50;
    }

    void die() {
        active = false;
    }

    void checkCollisionBullet(std::vector<Bullet>& bullets) {
        if (!active) return;
        for (size_t i = 0; i < bullets.size(); i++) {
            if (CheckCollisionCircleRec(bullets[i].position, bullets[i].size, body) && bullets[i].active) {
                takeDamage();
                bullets[i].active = false;
            }
        }

    }

    void update(std::vector<Bullet>& bullets) {
        body = {position.x, position.y, size, size};
        checkCollisionBullet(bullets);
        if (health <= 0) {
            die();
        }
    }

};

int main() {
    InitWindow(screenWidth, screenHeight, "Space Invaders");

    int monitor = GetCurrentMonitor();
    int refreshRate = GetMonitorRefreshRate(monitor);
    SetTargetFPS(refreshRate);

    Player player;
    Enemy enemy;

    while (!WindowShouldClose()) {

        float deltaTime = GetFrameTime();

        player.update(deltaTime);
        enemy.update(player.bullets);

        BeginDrawing();
        ClearBackground(DARKBLUE);

        player.draw();
        enemy.draw();
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}