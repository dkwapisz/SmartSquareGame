// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Bullet.hpp"

Bullet::Bullet() = default;

Bullet::Bullet(sf::RectangleShape* bulletShape,
               float positionX, float positionY,
               float directionX, float directionY,
               float moveSpeed): SquareObject(bulletShape, positionX, positionY) {

    this -> direction.x = directionX;
    this -> direction.y = directionY;
    this -> moveSpeed = moveSpeed;

    this -> objectShape.setFillColor(sf::Color::Red);
    this -> objectShape.setSize(sf::Vector2f(5.f, 5.f));
}

void Bullet::update() {
    this -> objectShape.move(this -> moveSpeed * this -> direction);

}


