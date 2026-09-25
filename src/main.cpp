#include "raymath.h"
#include "raylib.h"

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"

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