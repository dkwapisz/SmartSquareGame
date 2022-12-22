// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Wall.hpp"

Wall::Wall() = default;

Wall::Wall(sf::RectangleShape *wallShape, float positionX, float positionY):
SquareObject(wallShape, positionX, positionY) {

    this -> objectShape.setFillColor(sf::Color(100, 100, 100));
    this -> objectShape.setSize(sf::Vector2f(30.f, 30.f));
}

