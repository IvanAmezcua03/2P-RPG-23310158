//
// Created by Victor Navarro on 15/02/24.
//

#include "Player.h"
#include <iostream>

using namespace std;

Player::Player(char* _name, int _health, int _attack, int _defense, int _speed) : Character(_name, _health, _attack, _defense, _speed, true) {
    level = 1;
    experience = 0;
}

void Player::doAttack(Character *target) {
    target->takeDamage(attack);

    if (target->getHealth() <= 0)
    {
        auto enemyTarget = dynamic_cast<Enemy*>(target);

        if (enemyTarget != nullptr) {
            gainExperience(enemyTarget->getExperience());
        }
    }
}

void Player::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0;
    }

    health-= trueDamage;
    if(health <= 0) {
        health = 0;
    }

    cout << name << " ha recibido " << trueDamage << " de danio!" << endl;
    cout << name << " le queda " << health << " de vida!" << endl;

    if(health <= 0) {
        cout << name << " has been defeated!" << endl;
    }

}




void Player::gainExperience(int exp) {
    experience += exp;
    if (experience >= 100) {
        levelUp();
        experience = 100-experience;
    }
}

Character* Player::selectTarget(vector<Enemy*> possibleTargets) {
    int selectedTarget = 0;
    cout << "Select a target: " << endl;
    for (int i = 0; i < possibleTargets.size(); i++) {
        cout << i << ". " << possibleTargets[i]->getName() << endl;
    }

    //TODO: Add input validation
    cin >> selectedTarget;
    return possibleTargets[selectedTarget];
}

Action Player::takeAction(vector<Enemy*> enemies) {
    int action = 0;
    while (true) {
        cout << getName() << ", te toca!" << endl
             << "Selecciona una accion: " << endl
             << "1. Attacar" << endl
             << "2. Defender" << endl;
        cin >> action;
        if (action == 1 || action == 2) {
            break;
        } else {
            cout << "Accion no valida" << endl;
        }
    }
    Action currentAction;
    Character* target = nullptr;

    if (getIsDefending()) {
        resetDefense();
    }

    switch(action) {
        case 1:
            target = selectTarget(enemies);
            currentAction.target = target;
            currentAction.action = [this, target](){
                doAttack(target);
            };
            currentAction.speed = getSpeed();
            break;
        case 2:
            currentAction.target = this;
            currentAction.action = [this](){
                defend();
            };
            currentAction.speed = DEFENSE_SPEED_PRIORITY;
            break;
        default:
            cout << "Accion no valida" << endl;
            break;
    }

    return currentAction;
}
// Level functions

void Player::levelUp() {
    level++;
    cout << getName() << " has alcanzado el nivel ( " << level << ")" << endl;

    upgradeStats();
}

void Player::upgradeStats() {

    int statOption;
    while(true) {
        cout << "\nChoose one stat to upgrade for " << getName() << ":" << endl;
        cout << "1. Attack" << endl << "2. Defense" << endl << "3. Speed" << endl;
        cin >> statOption;

        if (statOption > 0 && statOption < 4) {
            break;
        }
        else {
            cout << "That option doesn't exist, try again" << endl;
        }
    }

    int prevAttack, prevDefense, prevSpeed;

    switch (statOption) {
        case 1:
            prevAttack = getAttack();
            upgradeAttack();
            cout << getName() << " increased the attack of " << prevAttack << " to " << getAttack() << endl;
            break;
        case 2:
            prevDefense = getDefense();
            upgradeDefense();
            cout << getName() << " increased the defense of " << prevDefense << " to " << getDefense() << endl;
            break;
        case 3:
            prevSpeed = getSpeed();
            upgradeSpeed();
            cout << getName() << " increased the speed of " << prevSpeed << " to " << getSpeed() << endl;
            break;
        default:
            cout << "Invalid option." << endl;
            break;
    }
}

