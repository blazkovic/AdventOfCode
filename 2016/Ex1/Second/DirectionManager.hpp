#pragma once

#include <iostream>
#include <vector>
#include <tuple>

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
    void validateNewPoint();

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
        bool operator==(const Point & p_point)
        {
            return std::tie(x, y) == std::tie(p_point.x, p_point.y);
        }
    };
    Point m_position;
    Directions m_direction;
    std::vector<Point> m_visitedPoints;
};
