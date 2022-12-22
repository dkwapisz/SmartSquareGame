// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef WALL_HPP
#define WALL_HPP

#include "SquareObject.hpp"

class Wall : public SquareObject {

public:
    Wall();
    Wall(sf::RectangleShape* wallShape, float positionX, float positionY);
};


#endif //WALL_HPP
