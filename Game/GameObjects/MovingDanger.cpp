// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "MovingDanger.hpp"

MovingDanger::MovingDanger() = default;

MovingDanger::MovingDanger(sf::CircleShape *movingDangerShape, float positionX, float positionY, bool isHorizontal):
CircleObject(movingDangerShape, positionX, positionY) {

    this -> moveSpeed = 2.f;
    this -> isHorizontal = isHorizontal;
    this -> isReverseDirection = false;

    this -> objectShape.setFillColor(sf::Color(255, 0, 0));
}

void MovingDanger::move() {
    float direction;

    if (isReverseDirection) {
        direction = -1.f;
    } else {
        direction = 1.f;
    }

    if (isHorizontal) {
        this -> objectShape.move(sf::Vector2f(this -> moveSpeed * direction, 0));
    } else {
        this -> objectShape.move(sf::Vector2f(0, this -> moveSpeed * direction));
    }
}

void MovingDanger::reverseDirection() {
    isReverseDirection = !isReverseDirection;
}
