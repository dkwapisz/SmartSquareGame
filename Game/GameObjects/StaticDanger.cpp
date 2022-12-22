// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "StaticDanger.hpp"

StaticDanger::StaticDanger() = default;

StaticDanger::StaticDanger(sf::RectangleShape *staticDangerShape, float positionX, float positionY):
SquareObject(staticDangerShape, positionX, positionY){

    this -> objectShape.setFillColor(sf::Color(170, 0, 140));
    this -> objectShape.setSize(sf::Vector2f(30.f, 30.f));
}

