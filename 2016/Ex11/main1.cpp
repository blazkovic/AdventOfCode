#include <iostream>
#include <vector>
//#include <string>
//#include <sstream>
#include <bitset>
#include <cmath>

/*
The first floor contains a thulium generator, a thulium-compatible microchip, a plutonium generator, and a strontium generator.
The second floor contains a plutonium-compatible microchip and a strontium-compatible microchip.
The third floor contains a promethium generator, a promethium-compatible microchip, a ruthenium generator, and a ruthenium-compatible microchip.
The fourth floor contains nothing relevant.

F4  .   .   .   .   .   .   .   .   .   .   .
F3  .   .   .   .   .   .   .   PRG PRM RG  RM
F2  .   .   .   .   PLM .   SM  .   .   .   .
F1  E   TG  TM  PLG .   SG  .   .   .   .   .
*/


//F4 .  .  .  .  .
//F3 .  .  .  LG .
//F2 .  HG .  .  .
//F1 E  .  HM .  LM

class State
{
public:
    State(const unsigned p_input)
        : m_currentState(std::bitset<m_inputSize>(p_input).to_string())
    {}

    bool isValidState() const
    {
        for (auto i = 0u; i < m_numberOfFloors; ++i)
        {
            if (not isValidFloor(m_currentState.substr(i*m_floorSpace, m_floorSpace))) return false;
        }
        if (not isValidNumberOfEquipement()) return false;
        if (not isUniqueEquipement()) return false;
        return true;
    }

    void showState() const
    {
        for (auto i = 0u; i < m_inputSize; ++i)
        {
            if ((i != 0) and (i%m_floorSpace == 0)) std::cout << std::endl;
            std::cout << m_currentState[i];
        }
        std::cout << std::endl;
        std::cout << std::endl;
    }

private:
    bool isValidFloor(const std::string & p_singleFloor) const
    {
        bool isGeneratorOnFloor = isAnyGeneratorPresent(p_singleFloor);
        bool isAnyUnprotectedMicrochipPresent = false;

        for (auto i = 1u; i < m_floorSpace; ++i)
        {
            if ((p_singleFloor[i] == '1') and ((i % 2) == 0))
            {
                if ((p_singleFloor[i-1] == '0') and isGeneratorOnFloor)
                {
                    isAnyUnprotectedMicrochipPresent = true;
                }
            }
        }
        return /*!isElevatorAlone(p_singleFloor) and*/ !isAnyUnprotectedMicrochipPresent;
    }

//    bool isElevatorAlone(const std::string & p_singleFloor) const
//    {
//        if (p_singleFloor[0] == '1')
//        {
//            for (auto i = 1u; i < m_floorSpace; ++i)
//            {
//                if (p_singleFloor[i] == '1') return false;
//            }
//            return true;
//        }
//        return false;
//    }

    bool isValidNumberOfEquipement() const
    {
        auto l_counter = 0u;
        const auto l_numberOfElements = m_floorSpace;
        for (auto i = 0u; i < m_inputSize; ++i)
        {
            if (m_currentState[i] == '1') ++l_counter;
            if (l_counter > l_numberOfElements) return false;
        }
        return l_counter == l_numberOfElements;
    }

    bool isUniqueEquipement() const
    {
        for (auto i = 0u; i < m_floorSpace; ++i)
        {
            auto l_counter = 0u;
            for (auto j = 0u; j < m_numberOfFloors; ++j)
            {
                if (m_currentState[i + j*m_floorSpace] == '1') ++l_counter;
                if (l_counter > 1) return false;
            }
        }
        return true;
    }

    bool isAnyGeneratorPresent(const std::string & p_floor) const
    {
        for (auto i = 1u; i < m_floorSpace; i+=2)
        {
            if(p_floor[i] == '1') return true;
        }
    }

    static const unsigned m_inputSize = 20;
    const std::string m_currentState;
    const unsigned m_numberOfFloors = 4;
    const unsigned m_numberOfGenerators = 2;
    const unsigned m_floorSpace = m_numberOfGenerators*2 + 1;
};

void createAllPossibleStates(std::vector<State> & p_allStates, const std::string & p_input)
{
    const auto l_numberOfAllStates = std::pow(2, p_input.size());
    for (unsigned i = 0u; i < l_numberOfAllStates; ++i)
    {
        const State l_state{i};
        if (l_state.isValidState())
        {
//            std::cout << i << std::endl;
            p_allStates.push_back(l_state);
        }
    }
}

int main()
{
    const std::string l_initialState = "00000000100100010101";
//    const std::string l_initialState = "00000000000000000011110000101000011110100000";
    std::vector<State> l_allStates;
    createAllPossibleStates(l_allStates, l_initialState);



//    for (auto i = 0u; i < 16; ++i)
//    {
//        std::cout << std::bitset<16>(i).to_string() << std::endl;
//    }


//    State l_state{29};
//    l_state.showState();
//    std::cout << l_state.isValidState() << std::endl;

    for (auto i = 0u; i < l_allStates.size(); ++i)
    {
        l_allStates[i].showState();
    }
    std::cout << "l_allStates = " << l_allStates.size() << std::endl;

    return 0;
}

/*
--- Day 11: Radioisotope Thermoelectric Generators ---

You come upon a column of four floors that have been entirely sealed off from the rest of the building except for a small dedicated lobby. There are some radiation warnings and a big sign which reads "Radioisotope Testing Facility".

According to the project status board, this facility is currently being used to experiment with Radioisotope Thermoelectric Generators (RTGs, or simply "generators") that are designed to be paired with specially-constructed microchips. Basically, an RTG is a highly radioactive rock that generates electricity through heat.

The experimental RTGs have poor radiation containment, so they're dangerously radioactive. The chips are prototypes and don't have normal radiation shielding, but they do have the ability to generate an electromagnetic radiation shield when powered. Unfortunately, they can only be powered by their corresponding RTG. An RTG powering a microchip is still dangerous to other microchips.

In other words, if a chip is ever left in the same area as another RTG, and it's not connected to its own RTG, the chip will be fried. Therefore, it is assumed that you will follow procedure and keep chips connected to their corresponding RTG when they're in the same room, and away from other RTGs otherwise.

These microchips sound very interesting and useful to your current activities, and you'd like to try to retrieve them. The fourth floor of the facility has an assembling machine which can make a self-contained, shielded computer for you to take with you - that is, if you can bring it all of the RTGs and microchips.

Within the radiation-shielded part of the facility (in which it's safe to have these pre-assembly RTGs), there is an elevator that can move between the four floors. Its capacity rating means it can carry at most yourself and two RTGs or microchips in any combination. (They're rigged to some heavy diagnostic equipment - the assembling machine will detach it for you.) As a security measure, the elevator will only function if it contains at least one RTG or microchip. The elevator always stops on each floor to recharge, and this takes long enough that the items within it and the items on that floor can irradiate each other. (You can prevent this if a Microchip and its Generator end up on the same floor in this way, as they can be connected while the elevator is recharging.)

You make some notes of the locations of each component of interest (your puzzle input). Before you don a hazmat suit and start moving things around, you'd like to have an idea of what you need to do.

When you enter the containment area, you and the elevator will start on the first floor.

For example, suppose the isolated area has the following arrangement:

The first floor contains a hydrogen-compatible microchip and a lithium-compatible microchip.
The second floor contains a hydrogen generator.
The third floor contains a lithium generator.
The fourth floor contains nothing relevant.

As a diagram (F# for a Floor number, E for Elevator, H for Hydrogen, L for Lithium, M for Microchip, and G for Generator), the initial state looks like this:

F4 .  .  .  .  .
F3 .  .  .  LG .
F2 .  HG .  .  .
F1 E  .  HM .  LM

Then, to get everything up to the assembling machine on the fourth floor, the following steps could be taken:

    Bring the Hydrogen-compatible Microchip to the second floor, which is safe because it can get power from the Hydrogen Generator:

    F4 .  .  .  .  .
    F3 .  .  .  LG .
    F2 E  HG HM .  .
    F1 .  .  .  .  LM

    Bring both Hydrogen-related items to the third floor, which is safe because the Hydrogen-compatible microchip is getting power from its generator:

    F4 .  .  .  .  .
    F3 E  HG HM LG .
    F2 .  .  .  .  .
    F1 .  .  .  .  LM

    Leave the Hydrogen Generator on floor three, but bring the Hydrogen-compatible Microchip back down with you so you can still use the elevator:

    F4 .  .  .  .  .
    F3 .  HG .  LG .
    F2 E  .  HM .  .
    F1 .  .  .  .  LM

    At the first floor, grab the Lithium-compatible Microchip, which is safe because Microchips don't affect each other:

    F4 .  .  .  .  .
    F3 .  HG .  LG .
    F2 .  .  .  .  .
    F1 E  .  HM .  LM

    Bring both Microchips up one floor, where there is nothing to fry them:

    F4 .  .  .  .  .
    F3 .  HG .  LG .
    F2 E  .  HM .  LM
    F1 .  .  .  .  .

    Bring both Microchips up again to floor three, where they can be temporarily connected to their corresponding generators while the elevator recharges, preventing either of them from being fried:

    F4 .  .  .  .  .
    F3 E  HG HM LG LM
    F2 .  .  .  .  .
    F1 .  .  .  .  .

    Bring both Microchips to the fourth floor:

    F4 E  .  HM .  LM
    F3 .  HG .  LG .
    F2 .  .  .  .  .
    F1 .  .  .  .  .

    Leave the Lithium-compatible microchip on the fourth floor, but bring the Hydrogen-compatible one so you can still use the elevator; this is safe because although the Lithium Generator is on the destination floor, you can connect Hydrogen-compatible microchip to the Hydrogen Generator there:

    F4 .  .  .  .  LM
    F3 E  HG HM LG .
    F2 .  .  .  .  .
    F1 .  .  .  .  .

    Bring both Generators up to the fourth floor, which is safe because you can connect the Lithium-compatible Microchip to the Lithium Generator upon arrival:

    F4 E  HG .  LG LM
    F3 .  .  HM .  .
    F2 .  .  .  .  .
    F1 .  .  .  .  .

    Bring the Lithium Microchip with you to the third floor so you can use the elevator:

    F4 .  HG .  LG .
    F3 E  .  HM .  LM
    F2 .  .  .  .  .
    F1 .  .  .  .  .

    Bring both Microchips to the fourth floor:

    F4 E  HG HM LG LM
    F3 .  .  .  .  .
    F2 .  .  .  .  .
    F1 .  .  .  .  .

In this arrangement, it takes 11 steps to collect all of the objects at the fourth floor for assembly. (Each elevator stop counts as one step, even if nothing is added to or removed from it.)

In your situation, what is the minimum number of steps required to bring all of the objects to the fourth floor?


*/
