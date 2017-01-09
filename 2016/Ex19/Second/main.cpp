#include <iostream>
#include <map>

constexpr int g_numberOfElves = 3001330;

using ElfList = std::map<int, int>;

int findLastElfIndex(ElfList & p_elfList)
{
    auto l_firstIt = p_elfList.begin();
    const int l_halfSize = p_elfList.size()/2;
    std::advance(l_firstIt, l_halfSize);
    const auto l_isOdd = g_numberOfElves%2;
    auto l_counter = l_isOdd ? l_isOdd : 2;

    while(true)
    {
        while(l_counter)
        {
            auto l_tempIterator = l_firstIt;
            l_firstIt++;
            if (l_firstIt == p_elfList.end()) l_firstIt = p_elfList.begin();
            p_elfList.erase(l_tempIterator);
            if(p_elfList.size() == 1) return p_elfList.begin()->second;
            if(p_elfList.size() == 2) return l_firstIt->second;
            l_counter--;
        }
        l_firstIt++;
        if (l_firstIt == p_elfList.end()) l_firstIt = p_elfList.begin();
        l_counter = 2;
    }
}

int main()
{
    ElfList l_elfList;
    for (auto i = 1; i < g_numberOfElves+1; i++)
    {
        l_elfList.insert(std::make_pair(i, i));
    }

    std::cout << "Last elf number = " << findLastElfIndex(l_elfList) << std::endl;

    return 0;
}

/*
--- Day 19: An Elephant Named Joseph ---

The Elves contact you over a highly secure emergency channel. Back at the North Pole, the Elves are busy misunderstanding White Elephant parties.

Each Elf brings a present. They all sit in a circle, numbered starting with position 1. Then, starting with the first Elf, they take turns stealing all the presents from the Elf to their left. An Elf with no presents is removed from the circle and does not take turns.

For example, with five Elves (numbered 1 to 5):

  1
5   2
 4 3

    Elf 1 takes Elf 2's present.
    Elf 2 has no presents and is skipped.
    Elf 3 takes Elf 4's present.
    Elf 4 has no presents and is also skipped.
    Elf 5 takes Elf 1's two presents.
    Neither Elf 1 nor Elf 2 have any presents, so both are skipped.
    Elf 3 takes Elf 5's three presents.

So, with five Elves, the Elf that sits starting in position 3 gets all the presents.

With the number of Elves given in your puzzle input, which Elf gets all the presents?

Puzzle input : 3001330

--- Part Two ---

Realizing the folly of their present-exchange rules, the Elves agree to instead steal presents from the Elf directly across the circle. If two Elves are across the circle, the one on the left (from the perspective of the stealer) is stolen from. The other rules remain unchanged: Elves with no presents are removed from the circle entirely, and the other elves move in slightly to keep the circle evenly spaced.

For example, with five Elves (again numbered 1 to 5):

    The Elves sit in a circle; Elf 1 goes first:

      1
    5   2
     4 3

    Elves 3 and 4 are across the circle; Elf 3's present is stolen, being the one to the left. Elf 3 leaves the circle, and the rest of the Elves move in:

      1           1
    5   2  -->  5   2
     4 -          4

    Elf 2 steals from the Elf directly across the circle, Elf 5:

      1         1
    -   2  -->     2
      4         4

    Next is Elf 4 who, choosing between Elves 1 and 2, steals from Elf 1:

     -          2
        2  -->
     4          4

    Finally, Elf 2 steals from Elf 4:

     2
        -->  2
     -

So, with five Elves, the Elf that sits starting in position 2 gets all the presents.

With the number of Elves given in your puzzle input, which Elf now gets all the presents?

Your puzzle input is still 3001330.

*/
