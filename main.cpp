#include <iostream>
#include "Player/Player.h"
#include "Enemy/Enemy.h"
#include "Combat/Combat.h"

int main() {
    Player *player = new Player("Billy Goat", 40, 10, 4, 3);
    Enemy *enemy = new Enemy("Tolendo Ponens", 15, 6, 2, 5, 10);
    Enemy *enemy2 = new Enemy("Furcio", 15, 6, 2, 5, 10);

    vector<Character*> participants;

    participants.push_back(player);
    participants.push_back(enemy);
    participants.push_back(enemy2);

    Combat *combat = new Combat(participants);
    combat->doCombat();

    delete player;
    delete enemy;
    delete combat;
    return 0;
}
