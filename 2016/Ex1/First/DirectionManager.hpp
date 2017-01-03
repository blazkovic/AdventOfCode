#pragma once

#include <iostream>

class DirectionManager
{
public:
    DirectionManager();
    int getDistance();
    void move(char p_direction, int p_value);

private:
    void handleZero(char p_direction, int p_value);
    void handleNorth(char p_direction, int p_value);
    void handleSouth(char p_direction, int p_value);
    void handleWest(char p_direction, int p_value);
    void handleEast(char p_direction, int p_value);

    enum class Directions
    {
        ZERO,
        NORTH,
        WEST,
        SOUTH,
        EAST
    };
    struct Point
    {
        int x;
        int y;
    };
    Point m_position;
    Directions m_direction;
};
