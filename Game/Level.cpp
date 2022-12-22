// Author:       Dawid Kwapisz (dkwapisz99@gmail.com, dkwapisz@student.agh.edu.pl)
// License:      GPLv3

#include "Level.hpp"


Level::Level() = default;

Level::Level(int levelNumber) {
    this -> initializeMapPaths();
    this -> initializeLevelAttributes(levelNumber);
    this -> initializeGameObjects();
    this -> generateMap();
}

Level::~Level() {
    delete this -> player;
    delete this -> clock;

    for (auto &gameObject : this -> squareShapes) {
        delete gameObject.second;
    }

    for (auto &gameObject : this -> circleShapes) {
        delete gameObject.second;
    }

    for (auto *bullet : this -> bullets) {
        delete bullet;
    }

    for (auto *wall : this -> walls) {
        delete wall;
    }

    for (auto *box : this -> boxes) {
        delete box;
    }

    for (auto *staticDanger : this -> staticDangers) {
        delete staticDanger;
    }

    for (auto *coin : this -> coins) {
        delete coin;
    }

    for (auto *movingDanger : this -> movingDangers) {
        delete movingDanger;
    }

    for (auto *finish : this -> finishes) {
        delete finish;
    }
}

void Level::initializeMapPaths() {
    this -> mapPath[1] = R"(..\Game\Maps\map1.txt)";
    this -> mapPath[2] = R"(..\Game\Maps\map2.txt)";
    this -> mapPath[3] = R"(..\Game\Maps\map3.txt)";
}

void Level::initializeLevelAttributes(int levelNr) {
    this -> coinsCount = 0;
    this -> playerCoinsCount = 0;
    this -> levelFinished = false;
    this -> levelNumber = levelNr;
    this -> clock = new sf::Clock();
}

void Level::initializeGameObjects() {
    this -> squareShapes["Bullet"] = new sf::RectangleShape();
    this -> squareShapes["Wall"] = new sf::RectangleShape();
    this -> squareShapes["Box"] = new sf::RectangleShape();
    this -> squareShapes["StaticDanger"] = new sf::RectangleShape();
    this -> squareShapes["Finish"] = new sf::RectangleShape();
    this -> circleShapes["Coin"] = new sf::CircleShape();
    this -> circleShapes["MovingDanger"] = new sf::CircleShape();
}

void Level::generateMap() {

    std::fstream mapFile;
    mapFile.open(mapPath[this -> levelNumber]);
    int mapSizeX = 20;
    int mapSizeY = 20;
    int number = 0;

    if (mapFile.is_open()) {
        for (int y = 0; y < mapSizeY; y++) {
            for (int x = 0; x < mapSizeX; x++) {
                mapFile >> number;

                float posX = 30.f * (float) x;
                float posY = (30.f * (float) y) + 50;

                if (number == 1) {
                    this -> walls.push_back(new Wall(this -> squareShapes["Wall"],
                                                     posX, posY));
                } else if (number == 2) {
                    this -> boxes.push_back(new Box(this -> squareShapes["Box"],
                                                    posX, posY));
                } else if (number == 3) {
                    this -> staticDangers.push_back(new StaticDanger(this -> squareShapes["StaticDanger"],
                                                                     posX, posY));
                } else if (number == 4) {
                    this -> coins.push_back(new Coin(this -> circleShapes["Coin"],
                                                     posX, posY));
                    coinsCount++;
                } else if (number == 5) {
                    this -> movingDangers.push_back(new MovingDanger(this -> circleShapes["MovingDanger"],
                                                                     posX, posY, true));
                } else if (number == 6) {
                    this -> movingDangers.push_back(new MovingDanger(this -> circleShapes["MovingDanger"],
                                                                     posX, posY, false));
                } else if (number == 7) {
                    this -> finishes.push_back(new Finish(this -> squareShapes["Finish"],
                                                          posX, posY));
                }
                else if (number == 9) {
                    this -> player = new Player(posX, posY);
                }
            }
        }
    } else {
        std::cerr << "Could not open map file" << "\n";
    }

    mapFile.close();
}

void Level::movePlayer(float directionX, float directionY) {
    float startPosX = player -> getPosX();
    float startPosY = player -> getPosY();

    this -> player -> movePlayer(directionX, directionY);

    if (checkCollision()) {
        this -> player -> setPosition(startPosX, startPosY);
    }
}

bool Level::checkCollision() {
    for (const auto& wall : walls) {
        if (wall -> getBounds().intersects(this -> player -> getBounds())) {
            return true;
        }
    }

    for (const auto& box : boxes) {
        if (box -> getBounds().intersects(this -> player -> getBounds())) {
            return true;
        }
    }

    for (const auto& staticDanger : staticDangers) {
        if (staticDanger -> getBounds().intersects(this -> player -> getBounds())) {
            this -> resetLevel();
            return false;
        }
    }

    for (const auto& finish : finishes) {
        if (finish -> getBounds().intersects(this -> player -> getBounds())) {

            if (this -> coinsCount == this -> playerCoinsCount) {
                levelFinished = true;
            }

            return false;
        }
    }

    for (int i = 0; i < coins.size(); i++) {
        if (coins[i] -> getBounds().intersects(this -> player -> getBounds())) {
            delete coins[i];
            coins.erase(coins.begin() + i);
            this -> playerCoinsCount++;
        }
    }

    return false;
}

void Level::shot(float directionX, float directionY) {
    if (player -> isShotPossible()) {
        float positionX = this -> player -> getCenterPosition() -> x - squareShapes["Bullet"] -> getSize().x / 2;
        float positionY = this -> player -> getCenterPosition() -> y - squareShapes["Bullet"] -> getSize().y / 2;

        this -> bullets.push_back(new Bullet(this -> squareShapes["Bullet"],
                                             positionX, positionY,
                                             directionX, directionY,
                                             this -> player -> getShotSpeed()));
    } else {
        player -> incrementCooldown();
    }
}

bool Level::isLevelFinished() const {
    return levelFinished;
}

void Level::resetLevel() {
    this -> player -> resetPosition();
    this -> playerCoinsCount = 0;
    this -> clock -> restart();

    for (int i = 0; i < this -> movingDangers.size(); i++) {
        delete this -> movingDangers[i];
        this -> movingDangers.clear();
    }

    for (int i = 0; i < this -> boxes.size(); i++) {
        delete this -> boxes[i];
        this -> boxes.clear();
    }

    for (int i = 0; i < this -> coins.size(); i++) {
        delete this -> coins[i];
        this -> coins.clear();
    }

    std::fstream mapFile;
    mapFile.open(mapPath[this -> levelNumber]);
    int mapSizeX = 20;
    int mapSizeY = 20;
    int number = 0;

    if (mapFile.is_open()) {
        for (int y = 0; y < mapSizeY; y++) {
            for (int x = 0; x < mapSizeX; x++) {
                mapFile >> number;

                float posX = 30.f * (float) x;
                float posY = (30.f * (float) y) + 50;

                if (number == 2) {
                    this -> boxes.push_back(new Box(this -> squareShapes["Box"],
                                                    posX, posY));
                } else if (number == 4) {
                    this -> coins.push_back(new Coin(this -> circleShapes["Coin"],
                                                     posX, posY));
                } else if (number == 5) {
                    this -> movingDangers.push_back(new MovingDanger(this -> circleShapes["MovingDanger"],
                                                                     posX, posY, true));
                } else if (number == 6) {
                    this -> movingDangers.push_back(new MovingDanger(this -> circleShapes["MovingDanger"],
                                                                     posX, posY, false));
                }
            }
        }
    } else {
        std::cerr << "Could not open map file" << "\n";
    }

    mapFile.close();
}

void Level::updateBullets() {
    for (int i = 0; i < this -> bullets.size(); i++) {
        bullets[i] -> update();

        bool bullet_deleted = false;
        bool box_deleted = false;

        for (int j = 0; j < this -> walls.size() && !bullet_deleted; j++) {
            if (bullets[i] -> getBounds().intersects(walls[j] -> getBounds())) {

                delete this -> bullets[i];
                this -> bullets.erase(this -> bullets.begin() + i);

                bullet_deleted = true;
            }
        }

        for (int j = 0; j < this -> boxes.size() && !bullet_deleted && !box_deleted; j++) {
            if (bullets[i] -> getBounds().intersects(boxes[j] -> getBounds())) {

                delete this -> bullets[i];
                this -> bullets.erase(this -> bullets.begin() + i);

                bullet_deleted = true;

                delete this -> boxes[j];
                this -> boxes.erase(this -> boxes.begin() + j);

                box_deleted = true;
            }
        }

        for (int j = 0; j < staticDangers.size() && !bullet_deleted; j++) {
            if (bullets[i] -> getBounds().intersects(staticDangers[j] -> getBounds())) {
                delete this -> bullets[i];
                this -> bullets.erase(this -> bullets.begin() + i);

                bullet_deleted = true;
            }

        }
    }
}

void Level::updateDangerMovement() {
    for (auto *movingDanger : this -> movingDangers) {
        checkDangerCollision(movingDanger);
        movingDanger -> move();
    }
}

void Level::checkDangerCollision(MovingDanger *movingDanger) {
    if (movingDanger -> getBounds().intersects(this -> player -> getBounds())) {
        this -> resetLevel();
    }

    for (auto *wall : this -> walls) {
        if (movingDanger -> getBounds().intersects(wall -> getBounds())) {
            movingDanger -> reverseDirection();
        }
    }

    for (auto *box : this -> boxes) {
        if (movingDanger -> getBounds().intersects(box -> getBounds())) {
            movingDanger -> reverseDirection();
        }
    }
}

void Level::renderGameObjects(sf::RenderTarget &target) {
    for (auto *finish : this -> finishes) {
        finish -> render(target);
    }

    this -> player -> render(target);

    for (auto *bullet : this -> bullets) {
        bullet -> render(target);
    }

    for (auto *wall : this -> walls) {
        wall -> render(target);
    }

    for (auto *box : this -> boxes) {
        box -> render(target);
    }

    for (auto *staticDanger : this -> staticDangers) {
        staticDanger -> render(target);
    }

    for (auto *coin : this -> coins) {
        coin -> render(target);
    }

    for (auto *movingDanger : this -> movingDangers) {
        movingDanger -> render(target);
    }
}

int Level::getClockTime() const {
    return (int) this -> clock -> getElapsedTime().asSeconds();
}

Player* Level::getPlayer() const {
    return this -> player;
}

int Level::getCoinsCount() const {
    return this -> coinsCount;
}

int Level::getPlayerCoinsCount() const {
    return this -> playerCoinsCount;
}

int Level::getLevelNumber() const {
    return this -> levelNumber;
}

int Level::getMapsCount() const {
    return (int) mapPath.size();
}
