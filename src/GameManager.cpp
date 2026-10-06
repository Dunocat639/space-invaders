#include "GameManager.h"

GameManager::GameManager() {
    // Podria crear aquí els objectes de jugador, enemic i bala però de moment ho faré al main fins que sàpigui com.
}

void GameManager::init(Player& player) {
    player.init();
    //enemy.init();
}

void GameManager::unload(Player& player) {
    player.unload();
    //enemy.unload();
}

float GameManager::GetDeltaTime() {
    float deltaTime = GetFrameTime();
    return deltaTime;
}

void GameManager::update(Player& player, Bullet& bullet, Enemy& enemy) {

    player.update(GetDeltaTime());
    bullet.update(GetDeltaTime());
    enemy.update(player.bullets);
}

void GameManager::draw(Player& player, Bullet& bullet, Enemy& enemy) {
    player.draw();
    bullet.draw();
    enemy.draw();
}