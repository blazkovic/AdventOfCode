#include <iostream>
#include <vector>
#include <string>
#include <boost/optional.hpp>
#include "MD5.hpp"

boost::optional<char> hasTriple(const std::string & p_input)
{
    const auto l_inputSize = p_input.size() - 2;
    for (auto i = 0u; i < l_inputSize; i++)
    {
        if ((p_input[i] == p_input[i+1]) and (p_input[i] == p_input[i+2]))
        {
            return boost::make_optional<char>(p_input[i]);
        }
    }
    return boost::none;
}

bool hasFive(const std::string & p_hash, const std::string & p_five)
{
    return p_hash.find(p_five) != std::string::npos;
}

int main()
{
    const std::string c_input("ihaygndm");
    const MD5 l_md5Hasher;
    auto l_currentIndex = 0u;
    auto l_temporaryIndex = 0u;
    auto l_numberOfFoundKeys = 0u;
    std::vector<std::string> l_vectorOfHashes;

    while (l_numberOfFoundKeys < 64)
    {
        if (l_vectorOfHashes.size() == l_currentIndex)
        {
            const std::string l_hash = l_md5Hasher.getHash(c_input + std::to_string(l_currentIndex));
            l_vectorOfHashes.push_back(l_hash);
        }
        const auto l_tripleChar = hasTriple(l_vectorOfHashes[l_currentIndex]);

        if (l_tripleChar)
        {
            l_temporaryIndex = l_currentIndex;
            while (l_temporaryIndex - l_currentIndex <= 1000)
            {
                l_temporaryIndex++;
                if (l_vectorOfHashes.size() == l_temporaryIndex)
                {
                    const std::string l_hash = l_md5Hasher.getHash(c_input + std::to_string(l_temporaryIndex));
                    l_vectorOfHashes.push_back(l_hash);
                }
                if (hasFive(l_vectorOfHashes[l_temporaryIndex], std::string(5, l_tripleChar.get())))
                {
                    l_numberOfFoundKeys++;
                    break;
                }
            }
        }
        l_currentIndex++;
    }

    std::cout << "Index with 64th key = " << l_currentIndex - 1 << std::endl;
    return 0;
}

/*
--- Day 14: One-Time Pad ---

In order to communicate securely with Santa while you're on this mission, you've been using a one-time pad that you generate using a pre-agreed algorithm. Unfortunately, you've run out of keys in your one-time pad, and so you need to generate some more.

To generate keys, you first get a stream of random data by taking the MD5 of a pre-arranged salt (your puzzle input) and an increasing integer index (starting with 0, and represented in decimal); the resulting MD5 hash should be represented as a string of lowercase hexadecimal digits.

However, not all of these MD5 hashes are keys, and you need 64 new keys for your one-time pad. A hash is a key only if:

    It contains three of the same character in a row, like 777. Only consider the first such triplet in a hash.
    One of the next 1000 hashes in the stream contains that same character five times in a row, like 77777.

Considering future hashes for five-of-a-kind sequences does not cause those hashes to be skipped; instead, regardless of whether the current hash is a key, always resume testing for keys starting with the very next hash.

For example, if the pre-arranged salt is abc:

    The first index which produces a triple is 18, because the MD5 hash of abc18 contains ...cc38887a5.... However, index 18 does not count as a key for your one-time pad, because none of the next thousand hashes (index 19 through index 1018) contain 88888.
    The next index which produces a triple is 39; the hash of abc39 contains eee. It is also the first key: one of the next thousand hashes (the one at index 816) contains eeeee.
    None of the next six triples are keys, but the one after that, at index 92, is: it contains 999 and index 200 contains 99999.
    Eventually, index 22728 meets all of the criteria to generate the 64th key.

So, using our example salt of abc, index 22728 produces the 64th key.

Given the actual salt in your puzzle input, what index produces your 64th one-time pad key?

Your puzzle answer was 15035.
*/
