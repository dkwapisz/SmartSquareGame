// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "CircleObject.hpp"

CircleObject::CircleObject() = default;

CircleObject::CircleObject(sf::CircleShape *objectShape, float positionX, float positionY) {
    this -> objectShape = *objectShape;
    this -> objectShape.setRadius(10.f);
    this -> objectShape.setPosition(positionX + this -> objectShape.getRadius() / 2,
                                    positionY + this -> objectShape.getRadius() / 2);
}

sf::FloatRect CircleObject::getBounds() const {
    return this -> objectShape.getGlobalBounds();
}

void CircleObject::render(sf::RenderTarget &target) {
    target.draw(this -> objectShape);
}