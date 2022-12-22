// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef FINISH_HPP
#define FINISH_HPP

#include "SquareObject.hpp"

class Finish : public SquareObject {

public:
    Finish();
    Finish(sf::RectangleShape* wallShape, float positionX, float positionY);
};

#endif //FINISH_HPP
