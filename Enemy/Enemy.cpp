//
// Created by Victor Navarro on 15/02/24.
//

#include "Enemy.h"
#include "../Utils.h"
#include <iostream>


using namespace std;
using namespace combat_utils;

Enemy::Enemy(string _name, int _health, int _attack, int _defense, int _speed, int _experience) : Character(_name, _health, _attack, _defense, _speed, false) {
    experience = _experience;
}

void Enemy::doAttack(Character *target) {
    target->takeDamage(getRolledAttack(attack));
}

void Enemy::takeDamage(int damage) {
    int trueDamage = damage - defense;
    if (trueDamage < 0) {
        trueDamage = 0;
    }
    health-= trueDamage;

    if(health <= 0) {
        health = 0;
    }

    cout << name << " ha tomado " << trueDamage << " danio!" << endl;
    cout << name << " le queda " << health << " salud restante!" << endl;
    if(health <= 0) {
        cout << name << " ha sido derrotado!" << endl;
    }
}

int Enemy::getExperience() {
    return experience;
}

Character* Enemy::selectTarget(vector<Player*> possibleTargets) {
    //target with less health
    int lessHealth = 9999999;
    Character* target = nullptr;
    for(auto character : possibleTargets) {
        if(character->getHealth() < lessHealth) {
            lessHealth = character->getHealth();
            target = character;
        }
    }
    return target;
}

Action Enemy::takeAction(vector<Player*> partyMembers) {
    Action currentAction;

    if (getIsDefending()) {
        resetDefense();
    }

    if (getHealth() < getOriginalHealth() * 0.4 && (rand() % 100) < 50) {
        currentAction.target = this;
        currentAction.action = [this](){
            defend();
        };
        currentAction.speed = DEFENSE_SPEED_PRIORITY;
    } else {
        Character *target = selectTarget(partyMembers);
        currentAction.target = target;
        currentAction.action = [this, target]() {
            doAttack(target);
        };
        currentAction.speed = getSpeed();
    }

    return currentAction;
}