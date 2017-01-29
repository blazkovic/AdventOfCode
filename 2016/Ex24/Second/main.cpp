#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>
#include <queue>

std::string l_input = R"(###################################################################################################################################################################################
#.....#.#.....#...#....4#.....#.#...#.........#...#...............#...................#...#.#...........#.#...........#.#.#.#.........#.#.......#...#...........#.....#...#7..#.#.#
###.#.#.###.#.#.###.#.#.#.#.#.#.#.#.#.#.#.#.#.#.#.###.#.###.#.###.#.#.#.###.###.#.#####.###.#.#.###.#.#.#.#.#.#.#.#.#.#.#.#.###.#####.#.#.#.#.#####.#.#.#.###.#.#.#.#.#####.#.#.#.#
#.#.....#.#.#...#.........#.....#.....#.......#.#.#.............#.#.#.#.....#.#.......#.....#.........#...#.......#.....#.#.#.............#...........#.#.....#.#.....#.......#.#.#
#.#.#.#.#.#.#.#.#.#.#####.#####.###.###.#.###.#.###.###.#.#####.#.#.#.#.#.###.#.#.###.#.#.#.#.###.#########.###########.#.#.###.#.#.###.###.#.###.###.#.#.#####.#.###.#.#####.#.###
#...........#...#...#.....#.....#...#.#...#.#.....#.........#...#...#.....#.....#.#.#...#...#...#...#.....#.......#...#...#...............#...#...#.............#.....#.#.....#...#
###.#.#.###.#.#.#.#.###.#.###.#####.#.#.#.#.#.###.###.###.#.#.#.###.#.#.#.#.###.#.#.#.###.#####.#########.#.#.#.#.#.###.#.#.#.#.#####.#.#.#.#.###.#.#.#.#.#.#.#.#####.#.###.#.#.#.#
#3#...#.#.#.#.........#...............#...#.#.....#...#.....#...#.......#...#.....#.#.#...#.....#...#.....#.#.#.....#.....#...........#.#.#.#.....#.#.........#.#...#.#.#.#...#...#
#.###.###.#######.###.#.###.#.#.#.###.###.#######.###.#.#####.#####.#.#.#.#.#######.###.###.###.###.###.#.#########.#.#.#.#.#.#####.###.#.###.#.###.#.#####.###.###.###.#.#.#.###.#
#.#...#.....#.#.............#.....#.#.....#.#.....#.#.#.....#.....#.......#.....#.................#...........#...#.#.....#...#.....#...#.......#.#.....#...#...#.#.#...#...#...#.#
#.###.###.###.#.#.#.#####.#.###.#.#.###.#.#.#.#.#.#.#.#.#.#####.#####.#.#.#.#.#.#.###########.#.#.#.#.#.###.#.#.#.#.#.#.#.#.#.###.#.#.#####.#####.#.###.#.#.#.#.#.#.#####.#.###.#.#
#.....#.......#.#.#.#.#...............#...#.#.#.#...#...........#.....#.#...#.................#...#.#.#...#.............#...#.........#...............#...#.#.#.....#.....#.....#.#
#####.#.#######.#.###.#.#.#.#.###.#.#.#.###.###.###.#.#.#.#.#.#.###.#.#.#.#.#######.###.#.###.#.#.#.###.#.#.###.###.#.#.#.#.#####.#####.#.###.#####.###.#.#.#####.#.#.#####.#.#.#.#
#.#...#.........#...#.#...#.......#...#.#.......#...#.#.........#.#.#...#.#.#.#.........#.#.#.......#...#...#...#.#...#.......#...#.....#...#...#.#...#...#...#...........#...#.#.#
#.#####.#.###.#.#.#######.#.###.#.#.#.#########.#.#.#.#.#####.#.#.#######.#.#.###########.#.#########.###.#.#.#.#.###.#.#.###.#########.#.#.#.###.#.#.###.#.#.###.#####.#.###.#.#.#
#.......#.......#...#.#.#...#...#.....#.#...#...#.#.#.#.#...#.....#.#...#...#.............#.......#.......#...#.#.............#.......#.....#...#...#.#.....#.............#...#.#.#
#.#####.###.#####.#.#.#.#.#.#.#.#.#.#.#.#.###.###.#.###.###.#.#.###.#.#.#.#.###.#.###.#.#.#.#.#.#.#.#######.#.#.###.#.#.#.#.###.#.###.###.#####.#.#.#.#.#####.###.#.###.#####.###.#
#..6#...#...#...#...#.#.....#...#.#.#...#...........#.#.#...#.#.#.....#.....#.#.#.....#.......#.................#.#.....#.#.........#...#...#...........#.#2....#.#.......#.#.#.#.#
#.###.###.#.###.#####.#####.#.###.###.#.###.#.#####.#.#.#.#.#.#.###.#.#.#.#.#.#.#.#.#.#.###.#######.#.#.#.#.#####.#.#.#######.###.#####.###.#####.#####.#.#####.###.#######.###.###
#.#.....#...#...#...........#.#.......#.#...#.#.............#...#...#.....#...#.....#.......#.......#.......#...#...#.......#...#.......#.#...#...#.........#...#...#...#.......#.#
#.#.###.#.#.#.#.###.#######.#.#.###.###.#####.###.#.###.#######.#####.#####.#.#####.#.###.#.#.#.#.#####.###.#.#.#.#.#.#.#.#.#############.###.#.#.#.###.#.#.###.#.#.#.#.#####.#.#.#
#...#.........#.....#...#.#...#.....#...#...#.......#.....#...#...#...#...#.............#.#...#.............#.....#...#.#.#.......#.....#.....#.....#...........#...#...#.....#...#
#.#######.#.#.###.#.#.#.#.#.###.#.#.#.###.#.###.#.#.#.#####.#.#.#.#.#.#.#.#.#####.#####.#####.#.#######.###.#.#.###.#.###.#.#.#.#.#.###.#.#.###.#.#.#######.###.#.###.#.#.#.#.###.#
#.....#.......#...#.#...#.....#...#.#...........#.....#.....#.#.#...#.....#.................#.........#.#.......#...........#...#...#.......#0#...#.....#.......#.#...........#...#
#.#.#.#.#.###.#.#.#.###.###.#.#.###.#.#.#####.#######.#.#.#.#.#.###.###.###.#.#####.###.#####.#.#.###.###.###.###.#####.###.#.#.#.#.#.###.#.#.#.#.#.###.#.###.#.#.#.#.#.#.#####.###
#.#.#...#...#.#.......#.............#...........................#.......#...........#.#...#...#.#...#.....#...#.#.#.#.#.#.......#.#...#...#...#...............#.......#.....#.....#
#.#.###.#.#.#.#.#.#####.#.#####.#.#.###.#.#.#.#.#############.#.###.#.#.#.#.#####.#.#.###.#.###.#.#.#######.###.#.#.#.#.#.###.#.#####.#.###.###.#######.#.###.#####.#.#.#.#######.#
#...#.......#.....#...#...#...#.....#5....#...#.......#.#.#...#...........#.#.......#.#...#.#.......#.#.#...#...#.....#.............#...#...#.....#.................#.....#.#...#.#
#######.#.#.#######.#####.###.#.#.#######.#.#.#.#.#.#.#.#.#.###.#.###.#.#.#.###.###.#.#.#.###.#.###.#.#.###.#.###.#####.###.#######.#.#.#.#.#.#.#.#########.###.#.#.#.#.#.#.#.#.###
#.#.........#...........#.........#.........#.#.#...........#...#.....#...................#...........#...#...#...#.#.......#...#.....#.#.#.....#.#.............#.........#.#...#.#
#.#.#.###.#.###.#.###.#.###.#.#######.#.###.#.#.#.#########.#.###.#.#####.###.#.#.###.#.#.#.###.#.#####.###.#.###.#.#.###.#.#.#.#.#.#.#.#.###.#.#.###.#.#####.#.#.#######.#.#####.#
#.........#.#.....#.....#...#...#.......#.....#.................#...#...#.....#...#...#.#.#.#...#...........#.#.....#.#.....#...#.#...#.......#.........#.....#.....#.......#...#.#
#.#####.#.#.#.#.#.#.#####.###.###.#.#####.###.#####.###.#.#.#.#.#.###.#.#.#.#.#.#####.###.###.#.#.#.#.#.###.#.#.#.#.#.#.#.#####.#.#.#.#.#.#########.#.#.#.###.#.###.#.#.#.#.#.#.###
#.......#...#...#.....#.#...#...#...#.#.............#.....#.............#.#.......#.......#...#...#...#.....#.......#...#...........#.#...#.#.......#...........#.#.....#.....#...#
#.#.#.#.#.###.#.#.#.#.#.#.#.#.#.#.#.#.#.###.#.#.#####.#.###.#.#.#####.#.#.#.#####.#.#.###.###.#.#.#.#.#.#.#.#####.#.#.#####.###.###.###.###.#.#.#.#.#.#.#########.#####.#.#.#.#.#.#
#.#.#.#.............#...#...#.#.....#...........#.........#...#.#.#...#.#.........#.........#.........#.....#.........#...#...#...#..1#.....#.#.#...#.#.....#...#...........#.....#
###################################################################################################################################################################################)";

//std::string l_input = R"(###########
//#0.1.....2#
//#.#######.#
//#4.......3#
//###########)";

class Node
{
public:
    Node (int p_x, int p_y, int p_distance, char p_insides = ' ')
        : m_x(p_x), m_y(p_y), m_distance(p_distance), m_insides(p_insides)
    {}

    bool operator==(const Node & p_dest) const
    {
        return std::tie(m_x, m_y, m_insides) == std::tie(p_dest.m_x, p_dest.m_y, m_insides);
    }

    int m_x;
    int m_y;
    int m_distance;
    char m_insides;
};

class Path
{
public:
    Path(const Node p_first, const Node p_second)
        : m_firstNode(p_first), m_secondNode(p_second), m_distance(0)
    {}

public:
    const Node m_firstNode;
    const Node m_secondNode;
    int m_distance;
};

bool isDestination(const Node & p_current, const Node & p_destination)
{
    return (p_current.m_x == p_destination.m_x) and (p_current.m_y == p_destination.m_y);
}

int breadFirstSearch(const Node & p_source, const Node & p_destination, const std::vector<Node> & p_allNodes)
{
    std::queue<Node> l_nodesToExplore;
    std::vector<Node> l_visitedNodes;

    l_nodesToExplore.push(p_source);
    l_visitedNodes.push_back(p_source);

    while(l_nodesToExplore.size())
    {
        const auto l_topNode = l_nodesToExplore.front();
        l_nodesToExplore.pop();

        const std::vector<Node> l_actualNodeNeighbours = {{l_topNode.m_x,     l_topNode.m_y + 1, l_topNode.m_distance + 1},
                                                          {l_topNode.m_x,     l_topNode.m_y - 1, l_topNode.m_distance + 1},
                                                          {l_topNode.m_x + 1, l_topNode.m_y,     l_topNode.m_distance + 1},
                                                          {l_topNode.m_x - 1, l_topNode.m_y,     l_topNode.m_distance + 1}};

        if (isDestination(l_topNode, p_destination))
        {
            return l_topNode.m_distance;
        }

        for (const auto singleNode : l_actualNodeNeighbours)
        {
            auto l_it = std::find_if(p_allNodes.begin(), p_allNodes.end(), [&singleNode](const Node & p_nodeToCheck)
            {
                return (p_nodeToCheck.m_x == singleNode.m_x) and (p_nodeToCheck.m_y == singleNode.m_y) and (p_nodeToCheck.m_insides != '#');
            });

            auto l_visitedIt = std::find_if(l_visitedNodes.begin(), l_visitedNodes.end(), [&singleNode](const Node & p_nodeToCheck)
            {
                return (p_nodeToCheck.m_x == singleNode.m_x) and (p_nodeToCheck.m_y == singleNode.m_y);
            });

            if (l_it != p_allNodes.end() and l_visitedIt == l_visitedNodes.end())
            {
                l_nodesToExplore.push(singleNode);
                l_visitedNodes.push_back(singleNode);
            }
        }
    }
    return 0;
}

void constructNodesFromString(std::vector<Node> & p_allNodes, std::vector<Node> & p_targetNodes)
{
    for (auto i = 0u, x = 0u, y = 0u; i < l_input.size(); i++)
    {
        if(l_input[i] == '\n')
        {
            y++;
            x = 0;
            continue;
        }
        const Node l_currentNode{x, y, 0, l_input[i]};
        p_allNodes.push_back(l_currentNode);
        if (std::isdigit(l_currentNode.m_insides))
        {
            p_targetNodes.push_back(l_currentNode);
        }
        x++;
    }
}

void createAllPaths(std::vector<Path> & p_paths,
                    const std::vector<Node> & p_allNodes,
                    std::vector<Node> p_targetNodes)
{
    for (const auto l_lastTarget : p_targetNodes)
    {
        for (const auto it : p_targetNodes)
        {
            Path l_path{l_lastTarget, it};

            if (not (l_lastTarget == it))
            {
                l_path.m_distance = breadFirstSearch(l_lastTarget, it, p_allNodes);
                p_paths.push_back(l_path);
            }
        }
    }
}

int findLengthBetweenNodes(const std::vector<Path> & p_paths, const Node & p_source, const Node & p_destination)
{
    const auto l_length = std::find_if(p_paths.begin(), p_paths.end(), [&p_source, &p_destination](const Path & p_path)
    {
        return ((p_path.m_firstNode == p_source) and (p_path.m_secondNode == p_destination));
    });
    return l_length->m_distance;
}

void findPath(const std::vector<Path> & p_paths,
              std::vector<Node> p_targetNodes,
              const Node p_zeroNode,
              const Node p_source,
              int p_pathSoFar,
              int & p_shortestPath)
{
    if (p_targetNodes.size() == 0) p_pathSoFar += findLengthBetweenNodes(p_paths, p_source, p_zeroNode);
    for (const auto & destination : p_targetNodes)
    {
        const auto l_length = findLengthBetweenNodes(p_paths, p_source, destination);
        p_pathSoFar += l_length;

        auto l_newTargets = p_targetNodes;
        auto l_it = std::find_if(l_newTargets.begin(), l_newTargets.end(), [&destination](const Node & p_nodeToCheck)
        {
            return (p_nodeToCheck.m_x == destination.m_x) and (p_nodeToCheck.m_y == destination.m_y);
        });
        l_newTargets.erase(l_it);
        findPath(p_paths, l_newTargets, p_zeroNode, destination, p_pathSoFar, p_shortestPath);
        p_pathSoFar -= l_length;
    }
    if ((p_targetNodes.size() == 0) and (p_pathSoFar < p_shortestPath)) p_shortestPath = p_pathSoFar;
}

int findShortestPath(const std::vector<Path> & p_paths, std::vector<Node> p_targetNodes)
{
    std::sort(p_targetNodes.begin(), p_targetNodes.end(), [](const Node & p_first, const Node & p_second){ return p_first.m_insides > p_second.m_insides; });

    auto l_shortestPath = INT32_MAX;
    const auto l_rootNode = p_targetNodes.back();
    p_targetNodes.pop_back();
    findPath(p_paths, p_targetNodes, l_rootNode, l_rootNode, 0, l_shortestPath);
    return l_shortestPath;
}

int main()
{
    std::vector<Node> l_allNodes;
    std::vector<Node> l_targetNodes;
    std::vector<Path> l_paths;
    constructNodesFromString(l_allNodes, l_targetNodes);
    createAllPaths(l_paths, l_allNodes, l_targetNodes);
    const auto l_shortestPath = findShortestPath(l_paths, l_targetNodes);

    std::cout << "Shortest path = " << l_shortestPath << std::endl;

    return 0;
}

/*
--- Day 24: Air Duct Spelunking ---

You've finally met your match; the doors that provide access to the roof are locked tight, and all of the controls and related electronics are inaccessible. You simply can't reach them.

The robot that cleans the air ducts, however, can.

It's not a very fast little robot, but you reconfigure it to be able to interface with some of the exposed wires that have been routed through the HVAC system. If you can direct it to each of those locations, you should be able to bypass the security controls.

You extract the duct layout for this area from some blueprints you acquired and create a map with the relevant locations marked (your puzzle input). 0 is your current location, from which the cleaning robot embarks; the other numbers are (in no particular order) the locations the robot needs to visit at least once each. Walls are marked as #, and open passages are marked as .. Numbers behave like open passages.

For example, suppose you have a map like the following:

###########
#0.1.....2#
#.#######.#
#4.......3#
###########

To reach all of the points of interest as quickly as possible, you would have the robot take the following path:

    0 to 4 (2 steps)
    4 to 1 (4 steps; it can't move diagonally)
    1 to 2 (6 steps)
    2 to 3 (2 steps)

Since the robot isn't very fast, you need to find it the shortest route. This path is the fewest steps (in the above example, a total of 14) required to start at 0 and then visit every other location at least once.

Given your actual map, and starting from location 0, what is the fewest number of steps required to visit every non-0 number marked on the map at least once?

To begin, get your puzzle input.

Your puzzle answer was 460.

--- Part Two ---

Of course, if you leave the cleaning robot somewhere weird, someone is bound to notice.

What is the fewest number of steps required to start at 0, visit every non-0 number marked on the map at least once, and then return to 0?

Your puzzle answer was 668.
*/
