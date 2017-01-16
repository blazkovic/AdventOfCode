#pragma once

#include <vector>
#include <bitset>
#include <cmath>
#include <sstream>
#include <iomanip>
#include <chrono>

class MD5
{
public:
    MD5(const std::string & p_input)
        : m_input(p_input),
          m_sinVector(generateSinValues()),
          m_32BitWordVector(generateVectorOf32BitWords())
    {}

    std::string getHash()
    {
        return createMD5Sum();
    }

private:
    using BitsetVector = std::vector<std::bitset<8>>;

    std::string createMD5Sum()
    {
        const auto l_xTableSize = 16;
        std::vector<uint32_t> l_xTable;

        uint32_t A_WORD = 0x67452301;
        uint32_t B_WORD = 0xefcdab89;
        uint32_t C_WORD = 0x98badcfe;
        uint32_t D_WORD = 0x10325476;

        for (auto i = 0u; i < m_32BitWordVector.size() / 16; i++)
        {
            for (auto j = 0u; j < l_xTableSize; j++)
            {
                l_xTable.emplace_back(m_32BitWordVector[i*16 + j]);
            }

            const uint32_t l_aa = A_WORD;
            const uint32_t l_bb = B_WORD;
            const uint32_t l_cc = C_WORD;
            const uint32_t l_dd = D_WORD;

            /* Round 1. */
            A_WORD = B_WORD + rotateLeft((A_WORD + fun_F(B_WORD, C_WORD, D_WORD) + l_xTable[0] + m_sinVector[0]), 7);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_F(A_WORD, B_WORD, C_WORD) + l_xTable[1] + m_sinVector[1]), 12);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_F(D_WORD, A_WORD, B_WORD) + l_xTable[2] + m_sinVector[2]), 17);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_F(C_WORD, D_WORD, A_WORD) + l_xTable[3] + m_sinVector[3]), 22);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_F(B_WORD, C_WORD, D_WORD) + l_xTable[4] + m_sinVector[4]), 7);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_F(A_WORD, B_WORD, C_WORD) + l_xTable[5] + m_sinVector[5]), 12);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_F(D_WORD, A_WORD, B_WORD) + l_xTable[6] + m_sinVector[6]), 17);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_F(C_WORD, D_WORD, A_WORD) + l_xTable[7] + m_sinVector[7]), 22);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_F(B_WORD, C_WORD, D_WORD) + l_xTable[8] + m_sinVector[8]), 7);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_F(A_WORD, B_WORD, C_WORD) + l_xTable[9] + m_sinVector[9]), 12);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_F(D_WORD, A_WORD, B_WORD) + l_xTable[10] + m_sinVector[10]), 17);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_F(C_WORD, D_WORD, A_WORD) + l_xTable[11] + m_sinVector[11]), 22);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_F(B_WORD, C_WORD, D_WORD) + l_xTable[12] + m_sinVector[12]), 7);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_F(A_WORD, B_WORD, C_WORD) + l_xTable[13] + m_sinVector[13]), 12);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_F(D_WORD, A_WORD, B_WORD) + l_xTable[14] + m_sinVector[14]), 17);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_F(C_WORD, D_WORD, A_WORD) + l_xTable[15] + m_sinVector[15]), 22);

            /* Round 2. */
            A_WORD = B_WORD + rotateLeft((A_WORD + fun_G(B_WORD, C_WORD, D_WORD) + l_xTable[1] + m_sinVector[16]), 5);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_G(A_WORD, B_WORD, C_WORD) + l_xTable[6] + m_sinVector[17]), 9);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_G(D_WORD, A_WORD, B_WORD) + l_xTable[11] + m_sinVector[18]), 14);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_G(C_WORD, D_WORD, A_WORD) + l_xTable[0] + m_sinVector[19]), 20);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_G(B_WORD, C_WORD, D_WORD) + l_xTable[5] + m_sinVector[20]), 5);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_G(A_WORD, B_WORD, C_WORD) + l_xTable[10] + m_sinVector[21]), 9);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_G(D_WORD, A_WORD, B_WORD) + l_xTable[15] + m_sinVector[22]), 14);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_G(C_WORD, D_WORD, A_WORD) + l_xTable[4] + m_sinVector[23]), 20);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_G(B_WORD, C_WORD, D_WORD) + l_xTable[9] + m_sinVector[24]), 5);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_G(A_WORD, B_WORD, C_WORD) + l_xTable[14] + m_sinVector[25]), 9);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_G(D_WORD, A_WORD, B_WORD) + l_xTable[3] + m_sinVector[26]), 14);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_G(C_WORD, D_WORD, A_WORD) + l_xTable[8] + m_sinVector[27]), 20);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_G(B_WORD, C_WORD, D_WORD) + l_xTable[13] + m_sinVector[28]), 5);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_G(A_WORD, B_WORD, C_WORD) + l_xTable[2] + m_sinVector[29]), 9);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_G(D_WORD, A_WORD, B_WORD) + l_xTable[7] + m_sinVector[30]), 14);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_G(C_WORD, D_WORD, A_WORD) + l_xTable[12] + m_sinVector[31]), 20);

            /* Round 3. */
            A_WORD = B_WORD + rotateLeft((A_WORD + fun_H(B_WORD, C_WORD, D_WORD) + l_xTable[5] + m_sinVector[32]), 4);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_H(A_WORD, B_WORD, C_WORD) + l_xTable[8] + m_sinVector[33]), 11);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_H(D_WORD, A_WORD, B_WORD) + l_xTable[11] + m_sinVector[34]), 16);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_H(C_WORD, D_WORD, A_WORD) + l_xTable[14] + m_sinVector[35]), 23);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_H(B_WORD, C_WORD, D_WORD) + l_xTable[1] + m_sinVector[36]), 4);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_H(A_WORD, B_WORD, C_WORD) + l_xTable[4] + m_sinVector[37]), 11);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_H(D_WORD, A_WORD, B_WORD) + l_xTable[7] + m_sinVector[38]), 16);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_H(C_WORD, D_WORD, A_WORD) + l_xTable[10] + m_sinVector[39]), 23);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_H(B_WORD, C_WORD, D_WORD) + l_xTable[13] + m_sinVector[40]), 4);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_H(A_WORD, B_WORD, C_WORD) + l_xTable[0] + m_sinVector[41]), 11);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_H(D_WORD, A_WORD, B_WORD) + l_xTable[3] + m_sinVector[42]), 16);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_H(C_WORD, D_WORD, A_WORD) + l_xTable[6] + m_sinVector[43]), 23);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_H(B_WORD, C_WORD, D_WORD) + l_xTable[9] + m_sinVector[44]), 4);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_H(A_WORD, B_WORD, C_WORD) + l_xTable[12] + m_sinVector[45]), 11);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_H(D_WORD, A_WORD, B_WORD) + l_xTable[15] + m_sinVector[46]), 16);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_H(C_WORD, D_WORD, A_WORD) + l_xTable[2] + m_sinVector[47]), 23);

            /* Round 4. */
            A_WORD = B_WORD + rotateLeft((A_WORD + fun_I(B_WORD, C_WORD, D_WORD) + l_xTable[0] + m_sinVector[48]), 6);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_I(A_WORD, B_WORD, C_WORD) + l_xTable[7] + m_sinVector[49]), 10);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_I(D_WORD, A_WORD, B_WORD) + l_xTable[14] + m_sinVector[50]), 15);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_I(C_WORD, D_WORD, A_WORD) + l_xTable[5] + m_sinVector[51]), 21);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_I(B_WORD, C_WORD, D_WORD) + l_xTable[12] + m_sinVector[52]), 6);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_I(A_WORD, B_WORD, C_WORD) + l_xTable[3] + m_sinVector[53]), 10);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_I(D_WORD, A_WORD, B_WORD) + l_xTable[10] + m_sinVector[54]), 15);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_I(C_WORD, D_WORD, A_WORD) + l_xTable[1] + m_sinVector[55]), 21);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_I(B_WORD, C_WORD, D_WORD) + l_xTable[8] + m_sinVector[56]), 6);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_I(A_WORD, B_WORD, C_WORD) + l_xTable[15] + m_sinVector[57]), 10);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_I(D_WORD, A_WORD, B_WORD) + l_xTable[6] + m_sinVector[58]), 15);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_I(C_WORD, D_WORD, A_WORD) + l_xTable[13] + m_sinVector[59]), 21);

            A_WORD = B_WORD + rotateLeft((A_WORD + fun_I(B_WORD, C_WORD, D_WORD) + l_xTable[4] + m_sinVector[60]), 6);
            D_WORD = A_WORD + rotateLeft((D_WORD + fun_I(A_WORD, B_WORD, C_WORD) + l_xTable[11] + m_sinVector[61]), 10);
            C_WORD = D_WORD + rotateLeft((C_WORD + fun_I(D_WORD, A_WORD, B_WORD) + l_xTable[2] + m_sinVector[62]), 15);
            B_WORD = C_WORD + rotateLeft((B_WORD + fun_I(C_WORD, D_WORD, A_WORD) + l_xTable[9] + m_sinVector[63]), 21);

            A_WORD += l_aa;
            B_WORD += l_bb;
            C_WORD += l_cc;
            D_WORD += l_dd;
            l_xTable.clear();
        }
        return transformResult(A_WORD, B_WORD, C_WORD, D_WORD);
    }

    BitsetVector stringToBinaryWithPadding(const std::string & p_input)
    {
        const auto l_inputSize = p_input.size();
        BitsetVector l_bitsetVector;
        for (auto i = 0u; i < l_inputSize; i++)
        {
            l_bitsetVector.emplace_back(p_input[i]);
        }
        addPadding(l_bitsetVector);
        return l_bitsetVector;
    }

    void appendMessageLength(BitsetVector & p_bitsetVector, int p_initialMessageLength)
    {
        const uint64_t l_initialMsgSizeInBits = p_initialMessageLength*8;
        for (auto i = 0u; i < 8; i++)
        {
            p_bitsetVector.emplace_back(l_initialMsgSizeInBits >> i*8);
        }
    }

    void addPadding(BitsetVector & p_bitsetVector)
    {
        const auto l_paddingLimit = 448u;
        const auto l_desiredDataSize = 512u;
        const auto l_bitsetSize = p_bitsetVector[0].size();
        p_bitsetVector.emplace_back(10000000);

        while(((p_bitsetVector.size()*l_bitsetSize)%l_desiredDataSize) != l_paddingLimit)
        {
            p_bitsetVector.emplace_back(00000000);
        }
    }

    std::string transformResult(uint32_t p_a, uint32_t p_b, uint32_t p_c, uint32_t p_d)
    {
        const auto l_firstMask = 0xff00ff00;
        const auto l_secondMask = 0x00ff00ff;

        p_a = ((rotateLeft(p_a, 24) & l_firstMask) | (rotateLeft(p_a, 8) & l_secondMask));
        p_b = ((rotateLeft(p_b, 24) & l_firstMask) | (rotateLeft(p_b, 8) & l_secondMask));
        p_c = ((rotateLeft(p_c, 24) & l_firstMask) | (rotateLeft(p_c, 8) & l_secondMask));
        p_d = ((rotateLeft(p_d, 24) & l_firstMask) | (rotateLeft(p_d, 8) & l_secondMask));

        std::string result;
        std::stringstream ss;
        ss << std::setw(8) << std::setfill('0') << std::hex << p_a;
        ss << std::setw(8) << std::setfill('0') << std::hex << p_b;
        ss << std::setw(8) << std::setfill('0') << std::hex << p_c;
        ss << std::setw(8) << std::setfill('0') << std::hex << p_d;
        result += ss.str();
        return result;
    }

    std::vector<uint32_t> generateSinValues()
    {
        std::vector<uint32_t> l_output;
        const auto l_power = std::pow(2, 32);
        for (auto i = 0u; i < 64; i++)
        {
            l_output.emplace_back(std::floor(l_power * std::abs(std::sin(i + 1))));
        }
        return l_output;
    }

    std::vector<uint32_t> generateVectorOf32BitWords()
    {
        auto l_bitsetVector = stringToBinaryWithPadding(m_input);
        appendMessageLength(l_bitsetVector, m_input.size());

        std::vector<uint32_t> l_output;
        const auto l_bitsetVectorSize = l_bitsetVector.size();

        for (auto i = 0u; i < l_bitsetVectorSize; i+=4)
        {
            uint32_t l_output1 = 0;

            l_output1 |= ( l_bitsetVector[i+3].to_ulong() << 24);
            l_output1 |= ( l_bitsetVector[i+2].to_ulong() << 16);
            l_output1 |= ( l_bitsetVector[i+1].to_ulong() << 8);
            l_output1 |= l_bitsetVector[i].to_ulong();

            l_output.push_back(l_output1);
        }
        return l_output;
    }

    std::bitset<32> concat(const std::bitset<8> & p_1, const std::bitset<8> & p_2,
                           const std::bitset<8> & p_3, const std::bitset<8> & p_4)
    {
        return std::bitset<32>(p_1.to_string() + p_2.to_string() + p_3.to_string() + p_4.to_string());
    }

    uint32_t fun_F(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    {
        return (p_x & p_y) | ((~p_x) & p_z);
    }

    uint32_t fun_G(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    {
        return (p_x & p_z) | (p_y & (~p_z));
    }

    uint32_t fun_H(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    {
        return p_x ^ p_y ^ p_z;
    }

    uint32_t fun_I(uint32_t p_x, uint32_t p_y, uint32_t p_z)
    {
        return p_y ^ (p_x | (~p_z));
    }

    uint32_t rotateLeft(uint32_t p_x, int p_n)
    {
        return ((p_x << p_n) | (p_x >> (32-p_n)));
    }

    const std::string m_input;
    const std::vector<uint32_t> m_sinVector;
    const std::vector<uint32_t> m_32BitWordVector;
};
