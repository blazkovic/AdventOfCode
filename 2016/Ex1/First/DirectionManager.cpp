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

void DirectionManager::handleZero(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        m_position.x += p_value;
        m_direction = Directions::EAST;
    }
    else
    {
        m_position.x -= p_value;
        m_direction = Directions::WEST;
    }
}

void DirectionManager::handleNorth(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        m_position.x += p_value;
        m_direction = Directions::EAST;
    }
    else
    {
        m_position.x -= p_value;
        m_direction = Directions::WEST;
    }
}

void DirectionManager::handleSouth(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        m_position.x -= p_value;
        m_direction = Directions::WEST;
    }
    else
    {
        m_position.x += p_value;
        m_direction = Directions::EAST;
    }
}

void DirectionManager::handleWest(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        m_position.y += p_value;
        m_direction = Directions::NORTH;
    }
    else
    {
        m_position.y -= p_value;
        m_direction = Directions::SOUTH;
    }
}

void DirectionManager::handleEast(char p_direction, int p_value)
{
    if (p_direction == 'R')
    {
        m_position.y -= p_value;
        m_direction = Directions::SOUTH;
    }
    else
    {
        m_position.y += p_value;
        m_direction = Directions::NORTH;
    }
}

int DirectionManager::getDistance()
{
    return std::abs(m_position.x) + std::abs(m_position.y);
}
