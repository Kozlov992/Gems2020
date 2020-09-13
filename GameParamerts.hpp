#pragma once
#include <SFML/Graphics.hpp>
constexpr int NUMBER_OF_COLORS = 7;
const sf::Color BACKGROUND_COLOR(78, 222, 159);
const sf::Color COLOR_MODE1(0, 74, 0);
const sf::Color COLOR_MODE2(244, 179, 0);
const sf::Color COLOR_MODE3(31, 0, 104);
const sf::Color COLOR_MODE4(0, 77, 96);
const sf::Color COLOR_MODE5(224, 100, 183);
const sf::Color COLOR_MODE6(37, 37, 37);
const sf::Color COLOR_MODE7(78, 0, 0);
const sf::Color COLOR_MODES[NUMBER_OF_COLORS] = { COLOR_MODE1 , COLOR_MODE2 , COLOR_MODE3, COLOR_MODE4, COLOR_MODE5, COLOR_MODE6, COLOR_MODE7 };
constexpr int TABLE_WIDTH = 6;
constexpr int TABLE_HEIGHT = 8;
constexpr int BLOCK_SIDE = 100;
constexpr int WINDOW_WIDTH = 800;
constexpr int WINDOW_HEIGHT = 1000;
constexpr int INITIAL_X = 100;
constexpr int INITIAL_Y = 100;
constexpr int FRAME_RATE = 60;
constexpr int SHIFT = 100;
constexpr int DELTA = 100;
constexpr int VELOCITY = 10;
constexpr int SUFFICIENT_ORDER_OF_COMBINATION = 3;
constexpr int OPACITY_FALL = 5;
constexpr int OUTLINE_THICKNESS = 1;