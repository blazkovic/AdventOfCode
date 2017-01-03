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

Iterator handleJnz(std::istringstream & p_stream, Iterator p_it)
{
    std::string l_item;
    while(getline(p_stream, l_item, ' '))
    {
        auto l_sourceValue = getValue(l_item);
        while(getline(p_stream, l_item, ' '))
        {
            if (!l_sourceValue) return ++p_it;
            return moveIteratorToNewPosition(l_item, p_it);
        }
    }
    return p_it;
}

void handleInc(std::istringstream & p_stream)
{
    std::string l_item;
    while(getline(p_stream, l_item, ' '))
    {
        if (l_item == "a") a++;
        else if (l_item == "b") b++;
        else if (l_item == "c") c++;
        else if (l_item == "d") d++;
    }
}

void handleDec(std::istringstream & p_stream)
{
    std::string l_item;
    while(getline(p_stream, l_item, ' '))
    {
        if (l_item == "a") a--;
        else if (l_item == "b") b--;
        else if (l_item == "c") c--;
        else if (l_item == "d") d--;
    }
}

void handleCopy(std::istringstream & p_stream)
{
    std::string l_item;
    while(getline(p_stream, l_item, ' '))
    {
        auto l_sourceValue = getValue(l_item);
        while(getline(p_stream, l_item, ' '))
        {
            copyRegisters(l_item, l_sourceValue);
        }
    }
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
    // c=1;   // SET FOR PART 2
    for(auto it = p_vector.begin(); it != p_vector.end();)
    {
        std::istringstream l_input(*it);
        std::string l_item;
        while(getline(l_input, l_item, ' '))
        {
            if(l_item == "cpy")
            {
                handleCopy(l_input);
                it++;
            }
            else if(l_item == "jnz")
            {
                it = handleJnz(l_input, it);
            }
            else if(l_item == "inc")
            {
                handleInc(l_input);
                it++;
            }
            else if(l_item == "dec")
            {
                handleDec(l_input);
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
