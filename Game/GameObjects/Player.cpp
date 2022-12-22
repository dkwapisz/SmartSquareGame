// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Player.hpp"

Player::Player() = default;

Player::Player(float positionX, float positionY) {
    this -> moveSpeed = 5.f;
    this -> shotCooldown = 10;
    this -> shotCooldownMax = 10;
    this -> shotSpeed = 4.f;
    this -> deaths = 0;

    this -> respawnPosX = positionX;
    this -> respawnPosY = positionY;

    this -> playerShape.setPosition(positionX, positionY);
    this -> playerShape.setFillColor(sf::Color::Blue);
    this -> playerShape.setSize(sf::Vector2f(20.f, 20.f));
}

void Player::render(sf::RenderTarget &target) {
    target.draw(this -> playerShape);
}

void Player::resetPosition() {
    this -> playerShape.setPosition(respawnPosX, respawnPosY);
    deaths++;
}

void Player::movePlayer(float directionX, float directionY) {
    this -> playerShape.move(this -> moveSpeed * directionX, this -> moveSpeed * directionY);
}

const sf::Vector2f* Player::getCenterPosition() const {
    float x = this -> playerShape.getPosition().x + playerShape.getSize().x / 2;
    float y = this -> playerShape.getPosition().y + playerShape.getSize().y / 2;

    auto *centerPosition = new sf::Vector2f(x, y);

    return centerPosition;
}

void Player::incrementCooldown() {
    shotCooldown++;
}

float Player::getShotSpeed() const {
    return shotSpeed;
}

sf::FloatRect Player::getBounds() const {
    return this -> playerShape.getGlobalBounds();
}


bool Player::isShotPossible() {
    if (shotCooldown >= shotCooldownMax) {
        shotCooldown = 0;
        return true;
    } else {
        return false;
    }
}

float Player::getPosX() const {
    return this -> playerShape.getPosition().x;
}

float Player::getPosY() const {
    return this -> playerShape.getPosition().y;
}

void Player::setPosition(float positionX, float positionY) {
    this -> playerShape.setPosition(positionX, positionY);
}

int Player::getDeathsCount() const {
    return this -> deaths;
}

void Player::increaseDeathCount() {
    this -> deaths++;
}
