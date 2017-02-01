#include <iostream>
#include <set>
#include <tuple>
#include <string>
#include <queue>
#include <algorithm>

using State = std::multiset<std::pair<int, int>> ;

class Node
{
public:
    Node(unsigned p_elevatorFloor, State p_State, int p_pathLength = 0)
        : m_elevatorFloor(p_elevatorFloor), m_state(p_State), m_pathLength(p_pathLength)
    {}

    unsigned m_elevatorFloor;
    State m_state;
    int m_pathLength;
};

//static const Node g_finalNode{3, {{3, 3}, {3, 3}}};                                             // Example
static const Node g_finalNode{3, {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}}, 0};                  // First part
//static const Node g_finalNode{3, {{3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}, {3, 3}}, 0};    // Second part


//const Node g_initialNode{0, {{1, 0}, {2, 0}}, 0};                                               // Example
const Node g_initialNode{0, {{0, 0}, {0, 1}, {0, 1}, {2, 2}, {2, 2}}, 0};                       // First part
//const Node g_initialNode{0, {{0, 0}, {0, 1}, {0, 1}, {2, 2}, {2, 2}, {0, 0}, {0, 0}}, 0};         // Second part

bool isDestination(const Node & p_state)
{
    static const Node l_finalNode = g_finalNode;
    return (l_finalNode.m_state == p_state.m_state) and (l_finalNode.m_elevatorFloor == p_state.m_elevatorFloor);
}

bool isValidState(const std::vector<unsigned> & p_stateVector, unsigned p_elevatorFloor)
{
    auto isAnyGenerator = false;
    auto isAnyUnprotectedChip = false;
    constexpr auto l_numberOfFloors = 4;
    for (auto i = 0u; i < l_numberOfFloors; ++i)
    {
        isAnyGenerator = false;
        isAnyUnprotectedChip = false;
        for (auto j = 0u; j < p_stateVector.size(); ++j)
        {
            if (j%2)
            {
                if ((p_stateVector[j] == i) and (p_stateVector[j-1] != i))
                {
                    isAnyUnprotectedChip = true;
                }
            }
            else
            {
                if (p_stateVector[j] == i)
                {
                    isAnyGenerator = true;
                }
            }
        }
        if (isAnyGenerator and isAnyUnprotectedChip) return false;
    }
    return true;
}

void generateUpNeighbours(std::vector<Node> & p_nodes, const Node & p_node, unsigned p_elevatorFloor)
{
    std::vector<unsigned> l_stateVector;
    // handle one elements move
    for (auto i = 0u; i < p_node.m_state.size()*2; ++i)
    {
        for (auto it : p_node.m_state)
        {
            l_stateVector.push_back(it.first);
            l_stateVector.push_back(it.second);
        }
        if (l_stateVector[i] == p_elevatorFloor)
        {
            ++l_stateVector[i];
            if (isValidState(l_stateVector, p_elevatorFloor + 1))
            {
                State l_newState;
                for (auto j = 0u; j < l_stateVector.size(); j+=2)
                {
                    l_newState.insert(std::make_pair(l_stateVector[j], l_stateVector[j+1]));
                }
                Node l_newNode{p_elevatorFloor + 1, l_newState, p_node.m_pathLength + 1};
                p_nodes.push_back(l_newNode);
            }
        }
        l_stateVector.clear();
    }
    // handle two elements move
    for (auto i = 0u; i < p_node.m_state.size()*2; ++i)
    {
        for (auto j = i+1; j < p_node.m_state.size()*2; ++j)
        {
            for (auto it : p_node.m_state)
            {
                l_stateVector.push_back(it.first);
                l_stateVector.push_back(it.second);
            }
            if (l_stateVector[i] == p_elevatorFloor)
            {
                if (l_stateVector[j] == p_elevatorFloor)
                {
                    ++l_stateVector[i];
                    ++l_stateVector[j];
                    if (isValidState(l_stateVector, p_elevatorFloor + 1))
                    {
                        State l_newState;
                        for (auto j = 0u; j < l_stateVector.size(); j+=2)
                        {
                            l_newState.insert(std::make_pair(l_stateVector[j], l_stateVector[j+1]));
                        }
                        Node l_newNode{p_elevatorFloor + 1, l_newState, p_node.m_pathLength + 1};
                        p_nodes.push_back(l_newNode);
                    }
                }
            }
            l_stateVector.clear();
        }
    }
}

void generateDownNeighbours(std::vector<Node> & p_nodes, const Node & p_node, unsigned p_elevatorFloor)
{
    std::vector<unsigned> l_stateVector;
    // handle one elements move
    for (auto i = 0u; i < p_node.m_state.size()*2; ++i)
    {
        for (auto it : p_node.m_state)
        {
            l_stateVector.push_back(it.first);
            l_stateVector.push_back(it.second);
        }
        if (l_stateVector[i] == p_elevatorFloor)
        {
            --l_stateVector[i];
            if (isValidState(l_stateVector, p_elevatorFloor - 1))
            {
                State l_newState;
                for (auto j = 0u; j < l_stateVector.size(); j+=2)
                {
                    l_newState.insert(std::make_pair(l_stateVector[j], l_stateVector[j+1]));
                }
                Node l_newNode{p_elevatorFloor - 1, l_newState, p_node.m_pathLength + 1};
                p_nodes.push_back(l_newNode);
            }
        }
        l_stateVector.clear();
    }
    // handle two elements move
    for (auto i = 0u; i < p_node.m_state.size()*2; ++i)
    {
        for (auto j = i+1; j < p_node.m_state.size()*2; ++j)
        {
            for (auto it : p_node.m_state)
            {
                l_stateVector.push_back(it.first);
                l_stateVector.push_back(it.second);
            }
            if (l_stateVector[i] == p_elevatorFloor)
            {
                if (l_stateVector[j] == p_elevatorFloor)
                {
                    --l_stateVector[i];
                    --l_stateVector[j];
                    if (isValidState(l_stateVector, p_elevatorFloor - 1))
                    {
                        State l_newState;
                        for (auto j = 0u; j < l_stateVector.size(); j+=2)
                        {
                            l_newState.insert(std::make_pair(l_stateVector[j], l_stateVector[j+1]));
                        }
                        Node l_newNode{p_elevatorFloor - 1, l_newState, p_node.m_pathLength + 1};
                        p_nodes.push_back(l_newNode);
                    }
                }
            }
            l_stateVector.clear();
        }
    }
}

std::vector<Node> generateNodeNeighbours(const Node & p_node)
{
    static const auto l_zeroFloor = 0;
    static const auto l_firstFloor = 1;
    static const auto l_secondFloor = 2;
    static const auto l_thirdFloor = 3;
    std::vector<Node> l_nodes;
    if (p_node.m_elevatorFloor == l_zeroFloor)
    {
        generateUpNeighbours(l_nodes, p_node, l_zeroFloor);
    }
    else if (p_node.m_elevatorFloor == l_firstFloor)
    {
        generateUpNeighbours(l_nodes, p_node, l_firstFloor);
        generateDownNeighbours(l_nodes, p_node, l_firstFloor);
    }
    else if (p_node.m_elevatorFloor == l_secondFloor)
    {
        generateUpNeighbours(l_nodes, p_node, l_secondFloor);
        generateDownNeighbours(l_nodes, p_node, l_secondFloor);
    }
    else if (p_node.m_elevatorFloor == l_thirdFloor)
    {
        generateDownNeighbours(l_nodes, p_node, l_thirdFloor);
    }
    return l_nodes;
}

int breadthFirstSearchIterative()
{
    std::queue<Node> l_nodesToExplore;
    std::vector<Node> l_visitedNodes;

    const Node l_initialNode = g_initialNode;
    l_nodesToExplore.push(l_initialNode);

    while(l_nodesToExplore.size())
    {
        const auto l_topNode = l_nodesToExplore.front();
        l_nodesToExplore.pop();

        const std::vector<Node> l_actualNodeNeighbours = generateNodeNeighbours(l_topNode);

        if (isDestination(l_topNode))
        {
            return l_topNode.m_pathLength;
        }

        for (const auto singleNode : l_actualNodeNeighbours)
        {
            auto l_visitedIt = std::find_if(l_visitedNodes.begin(), l_visitedNodes.end(), [&singleNode](const Node & p_nodeToCheck)
            {
                return (p_nodeToCheck.m_state == singleNode.m_state) and (p_nodeToCheck.m_elevatorFloor == singleNode.m_elevatorFloor);
            });
            if (l_visitedIt == l_visitedNodes.end())
            {
                l_nodesToExplore.push(singleNode);
                l_visitedNodes.push_back(singleNode);
            }
        }
    }
    return 0;
}

int main()
{
    std::cout << "breadthFirstSearchIterative = " << breadthFirstSearchIterative() << std::endl;
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

Your puzzle answer was 31.

--- Part Two ---

You step into the cleanroom separating the lobby from the isolated area and put on the hazmat suit.

Upon entering the isolated containment area, however, you notice some extra parts on the first floor that weren't listed on the record outside:

    An elerium generator.
    An elerium-compatible microchip.
    A dilithium generator.
    A dilithium-compatible microchip.

These work just like the other generators and microchips. You'll have to get them up to assembly as well.

What is the minimum number of steps required to bring all of the objects, including these four new ones, to the fourth floor?

Your puzzle answer was 55.
*/
