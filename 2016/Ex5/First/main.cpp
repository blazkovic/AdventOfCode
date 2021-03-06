#include <iostream>
#include "MD5.hpp"
#include <chrono>

bool isFirstFiveZeros(const std::string & p_md5Hash)
{
    for (auto i = 0u; i < 5; i++)
    {
        if (p_md5Hash[i] != '0') return false;
    }
    return true;
}

int main()
{
    const std::string c_input("reyedfim");
    std::string l_password;
    auto l_counter = 0u;
    const MD5 l_md5Hasher;
    std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    for (auto i = 0u; i < 8; i++)
    {
        while(true)
        {
            std::string l_md5Hash = l_md5Hasher.getHash(c_input + std::to_string(l_counter));
            l_counter++;
            if (isFirstFiveZeros(l_md5Hash))
            {
                l_password += l_md5Hash[5];
                break;
            }
        }
    }

    std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference seconds = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() <<std::endl;

    std::cout << "Password = " << l_password << std::endl;
    return 0;
}

/*
--- Day 5: How About a Nice Game of Chess? ---

You are faced with a security door designed by Easter Bunny engineers that seem to have acquired most of their security knowledge by watching hacking movies.

The eight-character password for the door is generated one character at a time by finding the MD5 hash of some Door ID (your puzzle input) and an increasing integer index (starting with 0).

A hash indicates the next character in the password if its hexadecimal representation starts with five zeroes. If it does, the sixth character in the hash is the next character of the password.

For example, if the Door ID is abc:

    The first index which produces a hash that starts with five zeroes is 3231929, which we find by hashing abc3231929; the sixth character of the hash, and thus the first character of the password, is 1.
    5017308 produces the next interesting hash, which starts with 000008f82..., so the second character of the password is 8.
    The third time a hash starts with five zeroes is for abc5278568, discovering the character f.

In this example, after continuing this search a total of eight times, the password is 18f47a30.

Given the actual Door ID, what is the password?

Your puzzle input is reyedfim.

Your puzzle answer was f97c354d
*/
