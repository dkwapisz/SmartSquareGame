// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Coin.hpp"


Coin::Coin() = default;

Coin::Coin(sf::CircleShape *coinShape, float positionX, float positionY):
CircleObject(coinShape, positionX, positionY) {

    this -> objectShape.setFillColor(sf::Color(255, 255, 0));

}
