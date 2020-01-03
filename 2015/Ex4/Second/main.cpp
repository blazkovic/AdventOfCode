#include <iostream>
#include <chrono>
#include <../AdventOfCode/2016/MD5.hpp>

bool isFirstSixZeros(const std::string & p_md5Hash)
{
    for (auto i = 0u; i < 6; i++)
    {
        if (p_md5Hash[i] != '0') return false;
    }
    return true;
}

int main()
{
    const std::string l_input("bgvyzdsv");
    int l_password = 0;
    auto l_counter = 0u;
    const MD5 l_md5Hasher;
    const std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();

    while(true)
    {
        const std::string l_md5Hash = l_md5Hasher.getHash(l_input + std::to_string(l_counter));
        if (isFirstSixZeros(l_md5Hash))
        {
            l_password = l_counter;
            break;
        }
        l_counter++;
    }

    const std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
    std::cout << "Time difference seconds = " << std::chrono::duration_cast<std::chrono::seconds>(end - begin).count() <<std::endl;

    std::cout << "Password = " << l_password << std::endl;
    return 0;
}

/*
--- Day 4: The Ideal Stocking Stuffer ---

Santa needs help mining some AdventCoins (very similar to bitcoins) to use as
gifts for all the economically forward-thinking little girls and boys.

To do this, he needs to find MD5 hashes which, in hexadecimal, start with at least
five zeroes. The input to the MD5 hash is some secret key (your puzzle input, given below)
followed by a number in decimal. To mine AdventCoins, you must find Santa the lowest
positive number (no leading zeroes: 1, 2, 3, ...) that produces such a hash.

For example:
    If your secret key is abcdef, the answer is 609043, because the MD5 hash of
        abcdef609043 starts with five zeroes (000001dbbfa...), and it is the lowest such number to do so.
    If your secret key is pqrstuv, the lowest number it combines with to make an
        MD5 hash starting with five zeroes is 1048970; that is, the MD5 hash of pqrstuv1048970 looks like 000006136ef....

Answer: 2592

Your puzzle answer was 254575.

--- Part Two ---
Now find one that starts with six zeroes.

Your puzzle answer was 1038736.
*/
