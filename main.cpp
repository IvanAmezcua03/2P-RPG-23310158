#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"

int main() {
    Player *player = new Player("billy goat", 100, 20, 5, 10);
    Player *player2 = new Player("Ivan", 110, 12, 5, 9);
    Enemy *enemy = new Enemy("Tolendo", 35, 15, 4, 20, 10);
    Enemy *enemy2 = new Enemy("Furcio", 70, 30, 4, 5, 30);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(player2);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete player2;
    delete enemy2;
    delete combat;
    return 0;
}
