#include <iostream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdlib>

const std::string g_input = R"(move position 2 to position 6
move position 0 to position 5
move position 6 to position 4
reverse positions 3 through 7
move position 1 to position 7
swap position 6 with position 3
swap letter g with letter b
swap position 2 with position 3
move position 4 to position 3
move position 6 to position 3
swap position 4 with position 1
swap letter b with letter f
reverse positions 3 through 4
swap letter f with letter e
reverse positions 2 through 7
rotate based on position of letter h
rotate based on position of letter a
rotate based on position of letter e
rotate based on position of letter h
rotate based on position of letter c
move position 5 to position 7
swap letter a with letter d
move position 5 to position 6
swap position 4 with position 0
swap position 4 with position 6
rotate left 6 steps
rotate right 4 steps
rotate right 5 steps
swap letter f with letter e
swap position 2 with position 7
rotate based on position of letter e
move position 4 to position 5
swap position 4 with position 2
rotate right 1 step
swap letter b with letter f
rotate based on position of letter b
reverse positions 3 through 5
move position 3 to position 1
rotate based on position of letter g
swap letter c with letter e
swap position 7 with position 3
move position 0 to position 3
rotate right 6 steps
reverse positions 1 through 3
swap letter d with letter e
reverse positions 3 through 5
move position 0 to position 3
swap letter c with letter e
move position 2 to position 7
swap letter g with letter b
rotate right 0 steps
reverse positions 1 through 3
swap letter h with letter d
move position 4 to position 0
move position 6 to position 3
swap letter a with letter c
reverse positions 3 through 6
swap letter h with letter g
move position 7 to position 2
rotate based on position of letter h
swap letter b with letter h
reverse positions 2 through 6
move position 6 to position 7
rotate based on position of letter a
rotate right 7 steps
reverse positions 1 through 6
move position 1 to position 6
rotate based on position of letter g
rotate based on position of letter d
move position 0 to position 4
rotate based on position of letter e
rotate based on position of letter d
rotate based on position of letter a
rotate based on position of letter a
rotate right 4 steps
rotate based on position of letter b
reverse positions 0 through 4
move position 1 to position 7
rotate based on position of letter e
move position 1 to position 7
swap letter f with letter h
move position 5 to position 1
rotate based on position of letter f
reverse positions 0 through 1
move position 2 to position 4
rotate based on position of letter a
swap letter b with letter d
move position 6 to position 0
swap letter e with letter b
rotate right 7 steps
move position 2 to position 7
rotate left 4 steps
swap position 6 with position 1
move position 3 to position 5
rotate right 7 steps
reverse positions 0 through 6
swap position 2 with position 1
reverse positions 4 through 6
rotate based on position of letter g
move position 6 to position 4)";

void swapPositions(const std::string & p_item, std::string & p_stringToScramble)
{
    const auto l_firstIndex = std::stoul(p_item.substr(14));
    const auto l_secondIndex = std::stoul(p_item.substr(30));
    const auto l_temp = p_stringToScramble[l_firstIndex];
    p_stringToScramble[l_firstIndex] = p_stringToScramble[l_secondIndex];
    p_stringToScramble[l_secondIndex] = l_temp;
}

void swapLetters(const std::string & p_item, std::string & p_stringToScramble)
{
    const auto l_firstLetter = p_item[12];
    const auto l_secondLetter = p_item[26];
    const auto l_firstIndex = p_stringToScramble.find(l_firstLetter);
    const auto l_secondIndex = p_stringToScramble.find(l_secondLetter);
    const auto l_temp = p_stringToScramble[l_firstIndex];
    p_stringToScramble[l_firstIndex] = p_stringToScramble[l_secondIndex];
    p_stringToScramble[l_secondIndex] = l_temp;
}

void rotateLeft(const std::string & p_item, std::string & p_stringToScramble)
{
    auto l_rotateCounter = std::stoul(p_item.substr(13)) % p_item.size();
    while(l_rotateCounter)
    {
        const auto l_temp = p_stringToScramble[0];
        p_stringToScramble.erase(0, 1);
        p_stringToScramble.push_back(l_temp);
        l_rotateCounter--;
    }
}

void rotateRight(const std::string & p_item, std::string & p_stringToScramble)
{
    auto l_rotateCounter = std::stoul(p_item.substr(12)) % p_item.size();
    while(l_rotateCounter)
    {
        const auto l_temp = p_stringToScramble.substr(p_stringToScramble.size() - 1);
        p_stringToScramble.pop_back();
        p_stringToScramble.insert(0, l_temp);
        l_rotateCounter--;
    }
}

void rotateLeft(std::string & p_stringToScramble, int p_times)
{
    while(p_times)
    {
        const auto l_temp = p_stringToScramble[0];
        p_stringToScramble.erase(0, 1);
        p_stringToScramble.push_back(l_temp);
        p_times--;
    }
}

void rotatePosition(const std::string & p_item, std::string & p_stringToScramble)
{
    const auto l_charIndex = p_stringToScramble.find(p_item[35]);
    if (l_charIndex == 0) rotateLeft(p_stringToScramble, 9);
    if (l_charIndex == 1) rotateLeft(p_stringToScramble, 1);
    if (l_charIndex == 2) rotateLeft(p_stringToScramble, 6);
    if (l_charIndex == 3) rotateLeft(p_stringToScramble, 2);
    if (l_charIndex == 4) rotateLeft(p_stringToScramble, 7);
    if (l_charIndex == 5) rotateLeft(p_stringToScramble, 3);
    // if (l_charIndex == 6) do nothing
    if (l_charIndex == 7) rotateLeft(p_stringToScramble, 4);
}

void reversePosition(const std::string & p_item, std::string & p_stringToScramble)
{
    auto l_firstIndex = std::stoul(p_item.substr(18));
    auto l_secondIndex = std::stoul(p_item.substr(28));
    while (l_firstIndex < l_secondIndex)
    {
        const auto l_temp = p_stringToScramble[l_firstIndex];
        p_stringToScramble[l_firstIndex] = p_stringToScramble[l_secondIndex];
        p_stringToScramble[l_secondIndex] = l_temp;
        l_firstIndex++;
        l_secondIndex--;
    }
}

void movePosition(const std::string & p_item, std::string & p_stringToScramble)
{
    const auto l_yIndex = std::stoul(p_item.substr(14));
    const auto l_xIndex = std::stoul(p_item.substr(28));
    const auto l_tempChar = p_stringToScramble.substr(l_xIndex, 1);
    p_stringToScramble.erase(l_xIndex, 1);
    p_stringToScramble.insert(l_yIndex, l_tempChar);
}

void parseAndExecute(const std::string & p_item, std::string & p_stringToScramble)
{
    if (p_item.find("swap position ") != std::string::npos)                         swapPositions(p_item, p_stringToScramble);
    if (p_item.find("swap letter ") != std::string::npos)                           swapLetters(p_item, p_stringToScramble);
    if (p_item.find("rotate left ") != std::string::npos)                           rotateRight(p_item, p_stringToScramble);
    if (p_item.find("rotate right ") != std::string::npos)                          rotateLeft(p_item, p_stringToScramble);
    if (p_item.find("rotate based on position of letter ") != std::string::npos)    rotatePosition(p_item, p_stringToScramble);
    if (p_item.find("reverse positions ") != std::string::npos)                     reversePosition(p_item, p_stringToScramble);
    if (p_item.find("move position ") != std::string::npos)                         movePosition(p_item, p_stringToScramble);
}

int main()
{
    std::string l_stringToScramble("fbgdceah");
    std::istringstream l_input(g_input);
    std::string l_item;
    std::vector<std::string> l_reversedInput;
    while(getline(l_input, l_item, '\n'))
    {
        l_reversedInput.insert(l_reversedInput.begin(), l_item);
    }

    for (const auto & it : l_reversedInput)
    {
        parseAndExecute(it, l_stringToScramble);
    }
    std::cout << "Scrambled input = " << l_stringToScramble << std::endl;
    return 0;
}

/*
--- Day 21: Scrambled Letters and Hash ---

The computer system you're breaking into uses a weird scrambling function to store its passwords. It shouldn't be much trouble to create your own scrambled password so you can add it to the system; you just have to implement the scrambler.

The scrambling function is a series of operations (the exact list is provided in your puzzle input). Starting with the password to be scrambled, apply each operation in succession to the string. The individual operations behave as follows:

    swap position X with position Y means that the letters at indexes X and Y (counting from 0) should be swapped.
    swap letter X with letter Y means that the letters X and Y should be swapped (regardless of where they appear in the string).
    rotate left/right X steps means that the whole string should be rotated; for example, one right rotation would turn abcd into dabc.
    rotate based on position of letter X means that the whole string should be rotated to the right based on the index of letter X (counting from 0) as determined before this instruction does any rotations. Once the index is determined, rotate the string to the right one time, plus a number of times equal to that index, plus one additional time if the index was at least 4.
    reverse positions X through Y means that the span of letters at indexes X through Y (including the letters at X and Y) should be reversed in order.
    move position X to position Y means that the letter which is at index X should be removed from the string, then inserted such that it ends up at index Y.

For example, suppose you start with abcde and perform the following operations:

    swap position 4 with position 0 swaps the first and last letters, producing the input for the next step, ebcda.
    swap letter d with letter b swaps the positions of d and b: edcba.
    reverse positions 0 through 4 causes the entire string to be reversed, producing abcde.
    rotate left 1 step shifts all letters left one position, causing the first letter to wrap to the end of the string: bcdea.
    move position 1 to position 4 removes the letter at position 1 (c), then inserts it at position 4 (the end of the string): bdeac.
    move position 3 to position 0 removes the letter at position 3 (a), then inserts it at position 0 (the front of the string): abdec.
    rotate based on position of letter b finds the index of letter b (1), then rotates the string right once plus a number of times equal to that index (2): ecabd.
    rotate based on position of letter d finds the index of letter d (4), then rotates the string right once, plus a number of times equal to that index, plus an additional time because the index was at least 4, for a total of 6 right rotations: decab.

After these steps, the resulting scrambled password is decab.

Now, you just need to generate a new scrambled password and you can access the system. Given the list of scrambling operations in your puzzle input, what is the result of scrambling abcdefgh?
Your puzzle answer was dgfaehcb.

--- Part Two ---

You scrambled the password correctly, but you discover that you can't actually modify the password file on the system. You'll need to un-scramble one of the existing passwords by reversing the scrambling process.

What is the un-scrambled version of the scrambled password fbgdceah?

Your puzzle answer was fdhgacbe.
*/
