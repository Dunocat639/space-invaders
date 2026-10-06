#include "raylib.h"

#include "Enemy.h"
#include "Player.h"
#include "Bullet.h"
#include "GameManager.h"
#include "Constants.h"

int main() {
    InitWindow(screenWidth, screenHeight, "Space Invaders");

    int monitor = GetCurrentMonitor();
    int refreshRate = GetMonitorRefreshRate(monitor);
    SetTargetFPS(refreshRate);

    Player player;
    Bullet bullet(player.position);
    Enemy enemy;
    GameManager game;

    while (!WindowShouldClose()) {

        game.update(player, bullet, enemy);

        BeginDrawing();
        ClearBackground(DARKBLUE);

        game.draw(player, bullet, enemy);
        DrawFPS(10, 10);

        EndDrawing();
    }

    CloseWindow();
    return 0;
}