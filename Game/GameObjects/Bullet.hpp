// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef BULLET_HPP
#define BULLET_HPP

#include "SquareObject.hpp"

class Bullet : public SquareObject {

private:
    sf::Vector2f direction;
    float moveSpeed{};

public:
    Bullet();
    Bullet(sf::RectangleShape* bulletShape,
           float positionX, float positionY,
           float directionX, float directionY,
           float moveSpeed);

    void update();
};

#endif //BULLET_HPP