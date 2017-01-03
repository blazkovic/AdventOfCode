#include <algorithm>
#include "DirectionManager.hpp"

DirectionManager::DirectionManager()
    : m_position{0, 0}, m_direction{Directions::ZERO}
{}

void DirectionManager::move(char p_direction, int p_value)
{
    switch(m_direction)
    {
    case Directions::ZERO :
        handleZero(p_direction, p_value);
        break;
    case Directions::NORTH :
        handleNorth(p_direction, p_value);
        break;
    case Directions::WEST :
        handleWest(p_direction, p_value);
        break;
    case Directions::SOUTH :
        handleSouth(p_direction, p_value);
        break;
    case Directions::EAST :
        handleEast(p_direction, p_value);
        break;
    }
}

void DirectionManager::validateNewPoint()
{
    const auto l_newPoint = Point{m_position.x, m_position.y};
    const auto l_wasVisited = std::find(m_visitedPoints.begin(), m_visitedPoints.end(), l_newPoint);
    if (l_wasVisited != m_visitedPoints.end())
    {
        throw (std::abs(l_newPoint.x) + std::abs(l_newPoint.y));
    }
    m_visitedPoints.push_back(l_newPoint);
}

void DirectionManager::handleZero(char p_direction, int p_value)
{
    m_visitedPoints.push_back(Point{0, 0});
    if (p_direction == 'R')
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x += 1;
            validateNewPoint();
            m_direction = Directions::EAST;
        }
    }
    else
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x -= 1;
            validateNewPoint();
            m_direction = Directions::WEST;
        }
    }
}

void DirectionManager::handleNorth(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x += 1;
            validateNewPoint();
            m_direction = Directions::EAST;
        }
    }
    else
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x -= 1;
            validateNewPoint();
            m_direction = Directions::WEST;
        }
    }
}

void DirectionManager::handleSouth(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x -= 1;
            validateNewPoint();
            m_direction = Directions::WEST;
        }
    }
    else
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.x += 1;
            validateNewPoint();
            m_direction = Directions::EAST;
        }
    }
}

void DirectionManager::handleWest(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.y += 1;
            validateNewPoint();
            m_direction = Directions::NORTH;
        }
    }
    else
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.y -= 1;
            validateNewPoint();
            m_direction = Directions::SOUTH;
        }
    }
}

void DirectionManager::handleEast(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.y -= 1;
            validateNewPoint();
            m_direction = Directions::SOUTH;
        }
    }
    else
    {
        for(auto i = 0; i < p_value; i++)
        {
            m_position.y += 1;
            validateNewPoint();
            m_direction = Directions::NORTH;
        }
    }
}

int DirectionManager::getDistance()
{
    return std::abs(m_position.x) + std::abs(m_position.y);
}
