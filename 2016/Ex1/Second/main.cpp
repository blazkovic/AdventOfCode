#include <iostream>
#include <sstream>
#include <algorithm>
#include <vector>
#include "DirectionManager.hpp"

using Vector = std::vector<std::pair<char, int>>;

std::string input = {"R4, R5, L5, L5, L3, R2, R1, R1, L5, R5, R2, L1, L3, L4, R3, L1, L1, R2, R3, R3, R1, L3, L5, R3, "
                     "R1, L1, R1, R2, L1, L4, L5, R4, R2, L192, R5, L2, R53, R1, L5, R73, R5, L5, R186, L3, L2, R1, R3, "
                     "L3, L3, R1, L4, L2, R3, L5, R4, R3, R1, L1, R5, R2, R1, R1, R1, R3, R2, L1, R5, R1, L5, R2, L2, "
                     "L4, R3, L1, R4, L5, R4, R3, L5, L3, R4, R2, L5, L5, R2, R3, R5, R4, R2, R1, L1, L5, L2, L3, L4, "
                     "L5, L4, L5, L1, R3, R4, R5, R3, L5, L4, L3, L1, L4, R2, R5, R5, R4, L2, L4, R3, R1, L2, R5, L5, "
                     "R1, R1, L1, L5, L5, L2, L1, R5, R2, L4, L1, R4, R3, L3, R1, R5, L1, L4, R2, L3, R5, R3, R1, L3"};

void removeSpaces(std::string & p_input)
{
    p_input.erase(remove_if(p_input.begin(), p_input.end(), isspace), p_input.end());
}

void parseStringToVector(std::string & p_input, Vector & p_vector)
{
    removeSpaces(input);
    std::istringstream l_input(input);
    std::string l_item;
    while(getline(l_input, l_item, ','))
    {
        const auto l_direction = l_item[0];
        const auto l_distance = std::stoi(l_item.erase(0, 1));
        p_vector.push_back(std::make_pair(l_direction, l_distance));
    }
}

int main()
{
    std::vector<std::pair<char, int>> l_vecInput;
    parseStringToVector(input, l_vecInput);
    DirectionManager l_manager{};

    try
    {
        for (const auto & it : l_vecInput)
        {
            l_manager.move(it.first, it.second);
        }
        std::cout << l_manager.getDistance() << std::endl;
    }
    catch(int p_distance)
    {
        std::cout << p_distance << std::endl;
    }

    return 0;
}



