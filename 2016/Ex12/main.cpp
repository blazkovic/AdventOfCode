#include <iostream>
#include <vector>
#include <sstream>

std::string input = {R"(cpy 1 a
cpy 1 b
cpy 26 d
jnz c 2
jnz 1 5
cpy 7 c
inc d
dec c
jnz c -2
cpy a c
inc a
dec b
jnz b -2
cpy c b
dec d
jnz d -6
cpy 16 c
cpy 12 d
inc a
dec d
jnz d -2
dec c
jnz c -5)"};

int a, b, c, d;
using Iterator = std::vector<std::string>::iterator;

int getValue(const std::string & p_input)
{
    if (p_input == "a") return a;
    else if (p_input == "b") return b;
    else if(p_input == "c") return c;
    else if (p_input == "d") return d;
    else return std::stoul(p_input);
}

void copyRegisters(const std::string & p_input, int p_value)
{
    if (p_input == "a") a = p_value;
    else if (p_input == "b") b = p_value;
    else if(p_input == "c") c = p_value;
    else if (p_input == "d") d = p_value;
}

Iterator moveIteratorToNewPosition(const std::string & p_input, Iterator p_it)
{
    const auto l_value = std::stoi(p_input);
    p_it+= l_value;
    return p_it;
}

Iterator handleJnz(const std::string & p_input, Iterator p_it)
{
    std::string l_source;
    std::string l_destination;
    auto l_position = 4u;

    for (; p_input[l_position] != ' '; l_position++)
    {
        l_source.push_back(p_input[l_position]);
    }

    const auto l_sourceValue = getValue(l_source);

    l_position++;
    for (; p_input[l_position] != *p_input.end(); l_position++)
    {
        l_destination.push_back(p_input[l_position]);
    }

    if (!l_sourceValue) return ++p_it;
    return moveIteratorToNewPosition(l_destination, p_it);
}

void handleInc(const std::string & p_input)
{
    if (p_input[4] == 'a') a++;
    else if (p_input[4] == 'b') b++;
    else if (p_input[4] == 'c') c++;
    else if (p_input[4] == 'd') d++;
}

void handleDec(const std::string & p_input)
{
    if (p_input[4] == 'a') a--;
    else if (p_input[4] == 'b') b--;
    else if (p_input[4] == 'c') c--;
    else if (p_input[4] == 'd') d--;
}

void handleCopy(const std::string & p_input)
{
    std::string l_source;
    std::string l_destination;
    auto l_position = 4u;

    for (; p_input[l_position] != ' '; l_position++)
    {
        l_source.push_back(p_input[l_position]);
    }

    const auto l_sourceValue = getValue(l_source);
    l_position++;
    for (; p_input[l_position] != *p_input.end() ; l_position++)
    {
        l_destination.push_back(p_input[l_position]);
    }

    copyRegisters(l_destination, l_sourceValue);
}

void parseToVector(std::vector<std::string> & p_vector, std::string & p_input)
{
    std::istringstream l_input(p_input);
    std::string l_item;
    while(getline(l_input, l_item))
    {
        p_vector.push_back(l_item);
    }
}

void parseVector(std::vector<std::string> & p_vector)
{
//     c=1;   // SET FOR PART 2
    for(auto it = p_vector.begin(); it != p_vector.end();)
    {
        std::istringstream l_input(*it);
        std::string l_item;
        while(getline(l_input, l_item, '\n'))
        {
            if(l_item[0] == 'c')
            {
                handleCopy(l_item);
                it++;
            }
            else if(l_item[0] == 'j')
            {
                it = handleJnz(l_item, it);
            }
            else if(l_item[0] == 'i')
            {
                handleInc(l_item);
                it++;
            }
            else if(l_item[0] == 'd')
            {
                handleDec(l_item);
                it++;
            }
        }
    }
}

int main()
{
    std::vector<std::string> l_vector;
    parseToVector(l_vector, input);
    parseVector(l_vector);

    std::cout << a << std::endl;

    return 0;
}
