#ifndef GAMEMANAGER_H
#define GAMEMANAGER_H

#include "raylib.h"
#include <vector>

#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"

class GameManager {
public:
    float deltaTime();

    GameManager();

    float GetDeltaTime();

    void update(Player& player, Bullet& bullet, Enemy& enemy);

    void draw(Player& player, Bullet& bullet, Enemy& enemy);
};

#endif