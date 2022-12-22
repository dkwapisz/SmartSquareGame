// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#ifndef CIRCLEOBJECT_HPP
#define CIRCLEOBJECT_HPP

#include <SFML/Graphics.hpp>

class CircleObject {

protected:
    sf::CircleShape objectShape;

public:
    CircleObject();
    CircleObject(sf::CircleShape* objectShape, float posX, float posY);

    sf::FloatRect getBounds() const;

    void render(sf::RenderTarget &target);
};


#endif //CIRCLEOBJECT_HPP
