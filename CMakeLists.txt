cmake_minimum_required(VERSION 3.22)
project(SmartSquareGame)

set(CMAKE_CXX_STANDARD 20)

add_executable(
        SmartSquareGame Game/main.cpp
        Game/Game.cpp Game/Game.hpp
        Game/GameObjects/Player.cpp Game/GameObjects/Player.hpp
        Game/GameObjects/Bullet.cpp Game/GameObjects/Bullet.hpp
        Game/GameObjects/Wall.cpp Game/GameObjects/Wall.hpp
        Game/GameObjects/Box.cpp Game/GameObjects/Box.hpp
        Game/GameObjects/StaticDanger.cpp Game/GameObjects/StaticDanger.hpp
        Game/GameObjects/Coin.cpp Game/GameObjects/Coin.hpp
        Game/GameObjects/SquareObject.cpp Game/GameObjects/SquareObject.hpp
        Game/GameObjects/CircleObject.cpp Game/GameObjects/CircleObject.hpp
        Game/GameObjects/MovingDanger.cpp Game/GameObjects/MovingDanger.hpp
        Game/GameObjects/Finish.cpp Game/GameObjects/Finish.hpp
        Game/Level.cpp Game/Level.hpp)

set(SFML_STATIC_LIBRARIES TRUE)
set(SFML_DIR C:/SFML/lib/cmake/SFML)
find_package(SFML COMPONENTS system window graphics REQUIRED)

include_directories(c:/SFML/include)
target_link_libraries(SmartSquareGame sfml-system sfml-window sfml-graphics)
