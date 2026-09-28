#include "GameManager.h"

GameManager::GameManager(){

};

float GameManager::GetDeltaTime() {
    float deltaTime = GetFrameTime();
    return deltaTime;
}

void GameManager::Update(Player& player, Bullet& bullet, Enemy& enemy) {

    player.update(GetDeltaTime());
    bullet.update(GetDeltaTime());
    enemy.update(player.bullets);
}

void GameManager::Draw(Player& player, Bullet& bullet, Enemy& enemy) {
    player.draw();
    bullet.draw();
    enemy.draw();
}