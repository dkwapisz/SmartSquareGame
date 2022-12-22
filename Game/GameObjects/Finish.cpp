// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Finish.hpp"

Finish::Finish() = default;

Finish::Finish(sf::RectangleShape *wallShape, float positionX, float positionY):
        SquareObject(wallShape, positionX, positionY) {

    this -> objectShape.setFillColor(sf::Color(0, 255, 0, 200));
    this -> objectShape.setSize(sf::Vector2f(30.f, 30.f));
}
