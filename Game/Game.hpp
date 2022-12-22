// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "Level.hpp"
#include <iostream>
#include <fstream>
#include <map>
#include <cmath>

class Game {

private:
    sf::RenderWindow* window;
    sf::Text* clockLabel;
    sf::Text* coinCountLabel;
    sf::Text* deathCountLabel;
    sf::Font* font;

    Level* level;
    bool gameFinished;

    void loadFont();
    void initializeWindow();
    void initializeLabels();

    void inputMovement();
    void inputShooting();

    void deleteLabels();

    void updateLabels();
    void updateWindowEvents();
    void updatePlayerInput();
    void update();

    void renderLabels();
    void render();

public:
    Game();
    virtual ~Game();
    void gameLoop();
};
