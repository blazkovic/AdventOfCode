#include <iostream>
//#include <string>
//#include <sstream>
#include <vector>
#include <bitset>

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

constexpr auto g_numberOfGenerators = 2;
constexpr auto g_numberOfMicrochips = g_numberOfGenerators;
constexpr auto g_numberOfDevices = g_numberOfGenerators*g_numberOfGenerators;
constexpr auto g_numberOfFloors = 4;
constexpr auto g_numberOfElevators = 1;
constexpr auto g_floorSpace = g_numberOfDevices + g_numberOfElevators;
constexpr auto g_stateSize = g_floorSpace * g_numberOfFloors;
auto g_shortestPath = 9999;

using State = std::bitset<g_stateSize>;
using StateTable = std::vector<State>;

const State g_finalState("11111000000000000000");

void showState(const State & l_state)
{
    for (auto i = 0u; i < l_state.size(); i++)
    {
        if (!(i%5))
        {
            std::cout << std::endl;
        }
        std::cout << l_state[i];
    }
    std::cout << std::endl;
}

//bool isPossibleState(const State & p_actualState)
//{
//    if (p_actualState.count() != g_floorSpace) return false;
//    auto l_isAnyChipAlone = false;
//    auto l_isAnyGeneratorPresent = false;
//    auto l_elevatorNeighbours = 0;

//    for (auto i=0u; i < g_numberOfFloors; ++i)
//    {
//        if (p_actualState[i*g_floorSpace] == 1)
//        {
//            for (auto j=0u; j < g_floorSpace; ++j)
//            {
//                if (j != 0 and p_actualState[i*g_floorSpace + j] == 1)
//                {
//                    l_elevatorNeighbours++;
//                }
//            }
//        }
//    }
//    return l_elevatorNeighbours;
//}

bool isPossibleState(const State & p_actualState)
{
    if (p_actualState.count() != g_floorSpace) return false;
    auto l_isAnyChipAlone = false;
    auto l_isAnyGeneratorPresent = false;
    auto isElevatorPresent = false;
    auto l_elevatorNeighbours = 0;

    for (auto i=0u; i < g_numberOfFloors; ++i)
    {
        for (auto j=0u; j < g_floorSpace; ++j)
        {
            if (p_actualState[i*g_floorSpace] == 1) isElevatorPresent = true;
            if (p_actualState[i*g_floorSpace] == 1 and j != 0 and p_actualState[i*g_floorSpace + j] == 1)
            {
                l_elevatorNeighbours++;
            }
            if(j%2 and j < g_floorSpace and p_actualState[i*g_floorSpace + j] == 1)
            {
                l_isAnyGeneratorPresent = true;
            }
            if(!(j%2) and j+1 < g_floorSpace and j+2 < g_floorSpace and p_actualState[i*g_floorSpace + j + 2] == 1 and p_actualState[i*g_floorSpace + j + 1] == 0)
            {
                l_isAnyChipAlone = true;
            }
        }
//        std::cout << "l_isAnyGeneratorPresent " << l_isAnyGeneratorPresent << std::endl;
//        std::cout << "l_isAnyChipAlone " << l_isAnyChipAlone << std::endl;
//        std::cout << "l_elevatorNeighbours " << l_elevatorNeighbours << std::endl;
//        std::cout << "isElevatorPresent " << isElevatorPresent << std::endl;
        if ((l_isAnyGeneratorPresent and l_isAnyChipAlone) or (!l_elevatorNeighbours and isElevatorPresent)) return false;

        l_isAnyGeneratorPresent = false;
        l_isAnyChipAlone = false;
        isElevatorPresent = false;
    }
//    std::cout << "Zonk" << std::endl;
    return true;
}

void loopOver(int p_elementPosition, State p_actualState, StateTable & l_states)
{
    if (p_elementPosition == g_floorSpace) return;

    for (auto i = 0u; i < g_numberOfFloors; ++i)
    {
        p_actualState.set(p_elementPosition + i*g_floorSpace);
//        showState(p_actualState);
        if (isPossibleState(p_actualState))
        {
            l_states.push_back(p_actualState);
        }
        loopOver(p_elementPosition+1, p_actualState, l_states);
        p_actualState.reset(p_elementPosition + i*g_floorSpace);
    }
}

void createAllPossibleStates(StateTable & p_states)
{
    loopOver(0, State(), p_states);
}

bool isNeighbour(State p_initialState, State p_nextState)
{
    std::cout << "Initial ";
    showState(p_initialState);
    std::cout << std::endl;
    std::cout << "Next ";
    showState(p_nextState);
    if (p_nextState == p_nextState) return false;
    for (auto i=0u; i<g_numberOfFloors-1; i++)
    {
        if (p_initialState[i*g_floorSpace] == 1)
        {
            if (p_initialState[(i-1)*g_floorSpace]);
            else if (p_initialState[(i-1)*g_floorSpace]);
            else return false;
        }
    }
    return true;
}

void findShortestPath(State p_initialState, StateTable p_states, int & p_numberOfSteps)
{
    p_numberOfSteps++;
//    std::cout << "p_numberOfSteps " << p_numberOfSteps << std::endl;
    for(auto i = 0u; i<p_states.size(); i++)
    {
//            std::cout << "p_states.size() " << p_states.size() << std::endl;

        if (p_numberOfSteps >= g_shortestPath)
        {
            break;
        }
        if (p_states[i] == g_finalState and p_numberOfSteps < g_shortestPath)
        {
            g_shortestPath = p_numberOfSteps;
        }

        if (isNeighbour(p_initialState, p_states[i]))
        {
            auto l_currentState = p_states[i];
            p_states.erase(p_states.begin() + i);
            findShortestPath(l_currentState, p_states, p_numberOfSteps);
        }
        p_numberOfSteps--;
    }

}

int main()
{
    auto l_numberOfSteps = 0;

    StateTable l_states;
    createAllPossibleStates(l_states);
//    State l_initialPosition(00000000000000000011110000101000011110100000); // for my problem;
    State l_initialPosition("00000000100100010101"); // example;
    showState(l_initialPosition);
    std::cout << l_initialPosition << std::endl;
    std::cout << l_initialPosition[0] << std::endl;
    std::cout << l_initialPosition[1] << std::endl;
    std::cout << l_initialPosition[2] << std::endl;
    std::cout << l_initialPosition[3] << std::endl;
    std::cout << l_initialPosition[4] << std::endl;
    std::cout << l_initialPosition[5] << std::endl;
    std::cout << l_initialPosition[6] << std::endl;
    std::cout << l_initialPosition[20] << std::endl;

    //findShortestPath(l_initialPosition, l_states, l_numberOfSteps);

//    for(auto it : l_states)
//    {
//        showState(it);
//    }
    std::cout << "Number of states = " << l_states.size() << std::endl;
    std::cout << "g_shortestPath = " << g_shortestPath << std::endl;

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
