// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef MOVINGDANGER_HPP
#define MOVINGDANGER_HPP

#include "CircleObject.hpp"

class MovingDanger : public CircleObject {

private:
    float moveSpeed;
    bool isHorizontal; // if false -> it is verticalMovement
    bool isReverseDirection;

public:
    MovingDanger();
    MovingDanger(sf::CircleShape* movingDangerShape, float positionX, float positionY, bool isHorizontal);

    void reverseDirection();
    void move();
};


#endif //MOVINGDANGER_HPP
