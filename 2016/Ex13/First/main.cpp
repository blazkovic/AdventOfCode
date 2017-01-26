#include <iostream>
#include <string>
#include <vector>
#include <bitset>
#include <stack>
#include <algorithm>
#include <tuple>

constexpr auto g_favoriteNumber = 1362u;
constexpr auto g_destinationX = 31u;
constexpr auto g_destinationY = 39u;

class Node
{
public:
    Node (int p_x, int p_y, int p_distane)
        : x(p_x), y (p_y), distance(p_distane)
    {}

    bool operator==(const Node & p_dest) const
    {
        return std::tie(x, y) == std::tie(p_dest.x, p_dest.y);
    }

    int x;
    int y;
    int distance;
};
using Nodes = std::vector<Node>;

bool isOpenSpace(const Node & p_node)
{
    static const auto l_input = g_favoriteNumber;
    const auto l_polynomial = p_node.x*p_node.x + 3*p_node.x + 2*p_node.x*p_node.y + p_node.y + p_node.y*p_node.y + l_input;
    const std::bitset<sizeof(l_polynomial)*8> l_binaryPolynomial(l_polynomial);
    return l_binaryPolynomial.count() % 2 ? false : true;
}

bool isInRange(const Node & p_node)
{
    return p_node.x >= 0 and p_node.y >= 0;
}

bool wasVisited(const Node & p_node, const std::vector<Node> & p_visitedNodes)
{
    return std::find(p_visitedNodes.begin(), p_visitedNodes.end(), p_node) != p_visitedNodes.end();
}

bool isDestination(const Node & p_node)
{
    return (p_node.x == g_destinationX) and (p_node.y == g_destinationY);
}

int deepFirstSearchIterative()
{
    std::stack<Node> l_nodesToExplore;
    std::vector<Node> l_visitedNodes;
    auto l_shortestPath = INT64_MAX;

    Node l_startingNode(1, 1, 0);
    l_nodesToExplore.push(l_startingNode);
    l_visitedNodes.push_back(l_startingNode);

    while(l_nodesToExplore.size())
    {
        const auto & l_topNode = l_nodesToExplore.top();
        l_nodesToExplore.pop();

        const std::vector<Node> l_actualNodeNeighbours = {{l_topNode.x,     l_topNode.y + 1,    l_topNode.distance + 1},
                                                          {l_topNode.x,     l_topNode.y - 1,    l_topNode.distance + 1},
                                                          {l_topNode.x + 1, l_topNode.y,        l_topNode.distance + 1},
                                                          {l_topNode.x - 1, l_topNode.y,        l_topNode.distance + 1}};

        for (const auto & singleNode : l_actualNodeNeighbours)
        {
            if (isDestination(singleNode) and (singleNode.distance < l_shortestPath))
            {
                l_shortestPath = singleNode.distance;
            }
            if (isOpenSpace(singleNode) and isInRange(singleNode) and not wasVisited(singleNode, l_visitedNodes))
            {
                l_nodesToExplore.push(singleNode);
                l_visitedNodes.push_back(singleNode);
            }
        }
    }
    return l_shortestPath;
}

int main()
{
    std::cout << "DeepFirstSearchIterative = " << deepFirstSearchIterative() << std::endl;
    return 0;
}

/*
--- Day 13: A Maze of Twisty Little Cubicles ---

You arrive at the first floor of this new building to discover a much less welcoming environment than the shiny atrium of the last one. Instead, you are in a maze of twisty little cubicles, all alike.

Every location in this area is addressed by a pair of non-negative integers (x,y). Each such coordinate is either a wall or an open space. You can't move diagonally. The cube maze starts at 0,0 and seems to extend infinitely toward positive x and y; negative values are invalid, as they represent a location outside the building. You are in a small waiting area at 1,1.

While it seems chaotic, a nearby morale-boosting poster explains, the layout is actually quite logical. You can determine whether a given x,y coordinate will be a wall or an open space using a simple system:

    Find x*x + 3*x + 2*x*y + y + y*y.
    Add the office designer's favorite number (your puzzle input).
    Find the binary representation of that sum; count the number of bits that are 1.
        If the number of bits that are 1 is even, it's an open space.
        If the number of bits that are 1 is odd, it's a wall.

For example, if the office designer's favorite number were 10, drawing walls as # and open spaces as ., the corner of the building containing 0,0 would look like this:

  0123456789
0 .#.####.##
1 ..#..#...#
2 #....##...
3 ###.#.###.
4 .##..#..#.
5 ..##....#.
6 #...##.###

Now, suppose you wanted to reach 7,4. The shortest route you could take is marked as O:

  0123456789
0 .#.####.##
1 .O#..#...#
2 #OOO.##...
3 ###O#.###.
4 .##OO#OO#.
5 ..##OOO.#.
6 #...##.###

Thus, reaching 7,4 would take a minimum of 11 steps (starting from your current location, 1,1).

What is the fewest number of steps required for you to reach 31,39?

Your puzzle answer was 82.
*/
