#include <iostream>
#include <vector>
#include <sstream>

std::string input = {R"(cpy a d
cpy 15 c
cpy 170 b
inc d
dec b
jnz b -2
dec c
jnz c -5
cpy d a
jnz 0 0
cpy a b
cpy 0 a
cpy 2 c
jnz b 2
jnz 1 6
dec b
dec c
jnz c -4
inc a
jnz 1 -7
cpy 2 b
jnz c 2
jnz 1 4
dec b
dec c
jnz 1 -4
jnz 0 0
out b
jnz a -19
jnz 1 -21)"};

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
    const auto l_value = getValue(p_input);
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

unsigned handleOut(const std::string & p_input)
{
    return getValue(&p_input[4]);
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

bool parseVector(std::vector<std::string> & p_vector)
{
    std::vector<unsigned> l_output;
    auto l_outputCounter = 0;
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
            else if(l_item[0] == 'o')
            {
                l_output.push_back(handleOut(l_item));
                if (l_outputCounter%2)
                {
                    if (!l_output[l_outputCounter]) return true;
                }
                else
                {
                    if (l_output[l_outputCounter]) return true;
                }
                if (l_outputCounter > 1000) return false;
                it++;
                l_outputCounter++;
            }
        }
    }
    return true;
}

int main()
{
    // To do - implement pattern finding in input instead of limit
    std::vector<std::string> l_vector;
    parseToVector(l_vector, input);

    auto l_initialize = 0;
    while(parseVector(l_vector))
    {
        a = l_initialize;
        l_initialize++;
        std::cout << a << std::endl;
    }

    std::cout << "A register should be initialized to = " << l_initialize - 1 << std::endl;
    return 0;
}

/*
--- Day 25: Clock Signal ---

You open the door and find yourself on the roof. The city sprawls away from you for miles and miles.

There's not much time now - it's already Christmas, but you're nowhere near the North Pole, much too far to deliver these stars to the sleigh in time.

However, maybe the huge antenna up here can offer a solution. After all, the sleigh doesn't need the stars, exactly; it needs the timing data they provide, and you happen to have a massive signal generator right here.

You connect the stars you have to your prototype computer, connect that to the antenna, and begin the transmission.

Nothing happens.

You call the service number printed on the side of the antenna and quickly explain the situation. "I'm not sure what kind of equipment you have connected over there," he says, "but you need a clock signal." You try to explain that this is a signal for a clock.

"No, no, a clock signal - timing information so the antenna computer knows how to read the data you're sending it. An endless, alternating pattern of 0, 1, 0, 1, 0, 1, 0, 1, 0, 1...." He trails off.

You ask if the antenna can handle a clock signal at the frequency you would need to use for the data from the stars. "There's no way it can! The only antenna we've installed capable of that is on top of a top-secret Easter Bunny installation, and you're definitely not-" You hang up the phone.

You've extracted the antenna's clock signal generation assembunny code (your puzzle input); it looks mostly compatible with code you worked on just recently.

This antenna code, being a signal generator, uses one extra instruction:

    out x transmits x (either an integer or the value of a register) as the next value for the clock signal.

The code takes a value (via register a) that describes the signal to generate, but you're not sure how it's used. You'll have to find the input to produce the right signal through experimentation.

What is the lowest positive integer that can be used to initialize register a and cause the code to output a clock signal of 0, 1, 0, 1... repeating forever?

Your puzzle answer was 180.
*/
