#include "Game.hpp"

Game::Game() {
    this -> loadFont();
    this -> initializeWindow();
    this -> initializeLabels();

    this -> gameFinished = false;
    this -> level = new Level(1);
}

Game::~Game() {
    delete this -> level;
    deleteLabels();
    delete this -> window;
    exit(0);
}

void Game::loadFont() {
    this -> font = new sf::Font();

    if (!font -> loadFromFile("../Game/Upheaval-font.ttf")) {
        std::cout << "Font cannot be loaded";
    }
}

void Game::initializeWindow() {
    this -> window = new sf::RenderWindow(sf::VideoMode(600, 650),
                                          "SmartSquareGame",
                                          sf::Style::Close | sf::Style::Titlebar);
    this -> window -> setFramerateLimit(75);
    this -> window -> setVerticalSyncEnabled(false);
}

void Game::initializeLabels() {
    this -> clockLabel = new sf::Text();
    this -> deathCountLabel = new sf::Text();
    this -> coinCountLabel = new sf::Text();

    clockLabel -> setFont(*font);
    deathCountLabel -> setFont(*font);
    coinCountLabel -> setFont(*font);

    clockLabel -> setPosition(10.f, 10.f);
    deathCountLabel -> setPosition(240.f, 10.f);
    coinCountLabel -> setPosition(480.f, 10.f);

    clockLabel -> setFillColor(sf::Color::White);
    deathCountLabel -> setFillColor(sf::Color::White);
    coinCountLabel -> setFillColor(sf::Color::White);

    clockLabel -> setCharacterSize(22);
    deathCountLabel -> setCharacterSize(22);
    coinCountLabel -> setCharacterSize(22);
}

void Game::deleteLabels() {
    delete this -> clockLabel;
    delete this -> deathCountLabel;
    delete this -> coinCountLabel;
    delete this -> font;
}

void Game::updateLabels() {
    std::string time = std::to_string(this -> level -> getClockTime());
    clockLabel -> setString("Time: " + time + " [s]");

    std::string deaths = std::to_string(this -> level -> getPlayer() -> getDeathsCount());
    deathCountLabel -> setString("Deaths: " + deaths);

    std::string coinsCollected = std::to_string(this -> level -> getPlayerCoinsCount());
    std::string allCoins = std::to_string(this -> level -> getCoinsCount());
    coinCountLabel -> setString(coinsCollected + "/" + allCoins + " coins");
}

void Game::renderLabels() {
    this -> window -> draw(*clockLabel);
    this -> window -> draw(*deathCountLabel);
    this -> window -> draw(*coinCountLabel);
}

void Game::updateWindowEvents() {
    sf::Event e;

    while (this -> window -> pollEvent(e)) {
        if (e.Event::type == sf::Event::Closed) {
            this -> window -> close();
        }
    }
}

void Game::updatePlayerInput() {
    inputMovement();
    inputShooting();
}

void Game::inputMovement() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::A)) {
        this -> level -> movePlayer(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::D)) {
        this -> level -> movePlayer(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::W)) {
        this -> level -> movePlayer(0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::S)) {
        this -> level -> movePlayer(0.f, 1.f);
    }
}

void Game::inputShooting() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        this -> level -> shot(-1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        this -> level -> shot(1.f, 0.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Up)) {
        this -> level -> shot(0.f, -1.f);
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Down)) {
        this -> level -> shot(0.f, 1.f);
    }
}

void Game::run() {
    while (this -> window -> isOpen()) {
        if (!gameFinished) {
            this -> gameLoop();
            this -> render();
        } else {
            this -> window -> close();
            delete this;
            return;
        }
    }
}

void Game::gameLoop() {
    this -> updateWindowEvents();
    this -> updatePlayerInput();
    this -> updateLabels();
    this -> level -> updateBullets();
    this -> level -> updateDangerMovement();

    if (this -> level -> isLevelFinished()) {
        int lastLevelNum = this -> level -> getLevelNumber();
        int mapsCount = this -> level -> getMapsCount();

        if (lastLevelNum + 1 > mapsCount) {
            std::cout << "Player wins \n";
            gameFinished = true;
        } else {
            delete this -> level;
            this -> level = new Level(lastLevelNum + 1);
        }

    }
}

void Game::render() {
    this -> window -> clear();
    this -> level -> renderGameObjects(*this -> window);
    this -> renderLabels();
    this -> window -> display();
}
