// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3
#include "Box.hpp"

Box::Box() = default;

Box::Box(sf::RectangleShape *boxShape, float positionX, float positionY):
SquareObject(boxShape, positionX, positionY) {

    this -> objectShape.setFillColor(sf::Color(50, 0, 0));
    this -> objectShape.setSize(sf::Vector2f(30.f, 30.f));
}
