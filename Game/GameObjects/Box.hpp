// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef BOX_HPP
#define BOX_HPP

#include "SquareObject.hpp"

class Box : public SquareObject {

public:
    Box();
    Box(sf::RectangleShape* boxShape, float positionX, float positionY);
};


#endif //BOX_HPP
