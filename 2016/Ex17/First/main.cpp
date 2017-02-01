#include <iostream>
#include <bitset>
#include <tuple>
#include <algorithm>
#include <queue>

#include "MD5.hpp"


class Node
{
public:
    Node (int p_x, int p_y, const std::string & p_direction)
        : x(p_x), y (p_y)
    {
        pathSoFar+= p_direction;
    }

    bool operator==(const Node & p_dest) const
    {
        return std::tie(x, y, pathSoFar) == std::tie(p_dest.x, p_dest.y, pathSoFar);
    }

    int x;
    int y;
    std::string pathSoFar;
};

bool isOpen(const char & p_direction, const std::string & p_hash)
{
    if (p_direction == 'U')
    {
        if (p_hash[0] == 'b' or p_hash[0] == 'c' or p_hash[0] == 'd' or p_hash[0] == 'e' or p_hash[0] == 'f') return true;
    }
    else if (p_direction == 'D')
    {
        if (p_hash[1] == 'b' or p_hash[1] == 'c' or p_hash[1] == 'd' or p_hash[1] == 'e' or p_hash[1] == 'f') return true;
    }
    else if (p_direction == 'L')
    {
        if (p_hash[2] == 'b' or p_hash[2] == 'c' or p_hash[2] == 'd' or p_hash[2] == 'e' or p_hash[2] == 'f') return true;
    }
    else if (p_direction == 'R')
    {
        if (p_hash[3] == 'b' or p_hash[3] == 'c' or p_hash[3] == 'd' or p_hash[3] == 'e' or p_hash[3] == 'f') return true;
    }
    return false;
}

bool isOpenSpace(const Node & p_topNode, const Node & p_nextNode)
{
    static const std::string l_input = "qzthpkfp";
    static const MD5 l_md5;
    const auto l_hashToDecode = l_md5.getHash(l_input + p_topNode.pathSoFar);
    return isOpen(p_nextNode.pathSoFar.back(), l_hashToDecode);
}

bool isInRange(const Node & p_node)
{
    return p_node.x >= 1 and p_node.x <= 4 and p_node.y >= 1 and p_node.y <= 4;
}

bool isDestination(const Node & p_node)
{
    static const auto s_destinationX = 4u;
    static const auto s_destinationY = 4u;
    return (p_node.x == s_destinationX) and (p_node.y == s_destinationY);
}

std::string breadthFirstSearchIterative()
{
    std::queue<Node> l_nodesToExplore;
    std::string l_shortestPath;

    Node l_startingNode(1, 1, "");
    l_nodesToExplore.push(l_startingNode);

    while(l_nodesToExplore.size())
    {
        const auto l_topNode = l_nodesToExplore.front();
        l_nodesToExplore.pop();

        const std::vector<Node> l_actualNodeNeighbours = {{l_topNode.x,     l_topNode.y + 1,    l_topNode.pathSoFar + "D"},
                                                          {l_topNode.x,     l_topNode.y - 1,    l_topNode.pathSoFar + "U"},
                                                          {l_topNode.x + 1, l_topNode.y,        l_topNode.pathSoFar + "R"},
                                                          {l_topNode.x - 1, l_topNode.y,        l_topNode.pathSoFar + "L"}};

        if (isDestination(l_topNode))
        {
            return l_topNode.pathSoFar;
        }

        for (const auto singleNode : l_actualNodeNeighbours)
        {
            if (isInRange(singleNode) and isOpenSpace(l_topNode, singleNode))
            {
                l_nodesToExplore.push(singleNode);
            }
        }
    }
    return "path not found";
}

int main()
{
    std::cout << "Shortest path = " << breadthFirstSearchIterative() << std::endl;

    return 0;
}

/*
--- Day 17: Two Steps Forward ---

You're trying to access a secure vault protected by a 4x4 grid of small rooms connected by doors. You start in the top-left room (marked S), and you can access the vault (marked V) once you reach the bottom-right room:

#########
#S| | | #
#-#-#-#-#
# | | | #
#-#-#-#-#
# | | | #
#-#-#-#-#
# | | |
####### V

Fixed walls are marked with #, and doors are marked with - or |.

The doors in your current room are either open or closed (and locked) based on the hexadecimal MD5 hash of a passcode (your puzzle input) followed by a sequence of uppercase characters representing the path you have taken so far (U for up, D for down, L for left, and R for right).

Only the first four characters of the hash are used; they represent, respectively, the doors up, down, left, and right from your current position. Any b, c, d, e, or f means that the corresponding door is open; any other character (any number or a) means that the corresponding door is closed and locked.

To access the vault, all you need to do is reach the bottom-right room; reaching this room opens the vault and all doors in the maze.

For example, suppose the passcode is hijkl. Initially, you have taken no steps, and so your path is empty: you simply find the MD5 hash of hijkl alone. The first four characters of this hash are ced9, which indicate that up is open (c), down is open (e), left is open (d), and right is closed and locked (9). Because you start in the top-left corner, there are no "up" or "left" doors to be open, so your only choice is down.

Next, having gone only one step (down, or D), you find the hash of hijklD. This produces f2bc, which indicates that you can go back up, left (but that's a wall), or right. Going right means hashing hijklDR to get 5745 - all doors closed and locked. However, going up instead is worthwhile: even though it returns you to the room you started in, your path would then be DU, opening a different set of doors.

After going DU (and then hashing hijklDU to get 528e), only the right door is open; after going DUR, all doors lock. (Fortunately, your actual passcode is not hijkl).

Passcodes actually used by Easter Bunny Vault Security do allow access to the vault if you know the right path. For example:

    If your passcode were ihgpwlah, the shortest path would be DDRRRD.
    With kglvqrro, the shortest path would be DDUDRLRRUDRD.
    With ulqzkmiv, the shortest would be DRURDRUDDLLDLUURRDULRLDUUDDDRR.

Given your vault's passcode, what is the shortest path (the actual path, not just the length) to reach the vault?

Your puzzle input is qzthpkfp.

Your puzzle answer was RDDRLDRURD.
*/
