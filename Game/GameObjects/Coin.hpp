// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef COIN_HPP
#define COIN_HPP

#include "CircleObject.hpp"

class Coin : public CircleObject {

public:
    Coin();
    Coin(sf::CircleShape* coinShape, float positionX, float positionY);
};

#endif //COIN_HPP
