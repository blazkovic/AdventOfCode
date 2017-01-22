#include <iostream>
#include <vector>
#include <sstream>
#include <string>

/* input was changed to improve performance
cpy b c
inc a
dec c
jnz c -2
dec d
jnz d -5

into

s
jnz 0 0
jnz 0 0
jnz 0 0
jnz 0 0
jnz 0 0

where s =
    a += b*d;
    c = 0;
    d = 0;
*/

std::string input = {R"(cpy a b
dec b
cpy a d
cpy 0 a
s
jnz 0 0
jnz 0 0
jnz 0 0
jnz 0 0
jnz 0 0
dec b
cpy b c
cpy c d
dec d
inc c
jnz d -2
tgl c
cpy -16 c
jnz 1 c
cpy 79 c
jnz 77 d
inc a
inc d
jnz d -2
inc c
jnz c -5)"};

//std::string original_input = {R"(cpy a b
//dec b
//cpy a d
//cpy 0 a
//s
//dec b
//cpy b c
//cpy c d
//dec d
//inc c
//jnz d -2
//tgl c
//cpy -16 c
//jnz 1 c
//cpy 79 c
//jnz 77 d
//inc a
//inc d
//jnz d -2
//inc c
//jnz c -5)"};

long a, b, c, d;
using Iterator = std::vector<std::string>::iterator;

long getValue(const std::string & p_input)
{
    if (p_input == "a") return a;
    else if (p_input == "b") return b;
    else if(p_input == "c") return c;
    else if (p_input == "d") return d;
    else return std::stoll(p_input);
}

void copyRegisters(const std::string & p_input, int p_value)
{
    if (p_input == "a") a = p_value;
    else if (p_input == "b") b = p_value;
    else if(p_input == "c") c = p_value;
    else if (p_input == "d") d = p_value;
}

Iterator handleJnz(const std::string & p_input, std::vector<std::string> & p_vector, Iterator p_it)
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

    const auto l_value = getValue(l_destination);

    if ((l_value < 0))
    {
        if ((p_it + l_value) < p_vector.begin())
        {
            return ++p_it;
        }
    }

    if (l_value == 0) return ++p_it;

    p_it += l_value;
    return p_it;
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

void handleTgl(const std::string & p_input, std::vector<std::string> & p_vector, Iterator & p_it)
{
    std::string l_distanceString;
    auto l_position = 4u;

    for (; p_input[l_position] != *p_input.end() ; l_position++)
    {
        l_distanceString.push_back(p_input[l_position]);
    }

    const auto l_distance = getValue(l_distanceString);

    if (std::distance(p_it, p_vector.end()) <= l_distance) return;
    p_it+=l_distance;
    if ((*p_it)[0] == 'd')
    {
        (*p_it)[0] = 'i';
        (*p_it)[1] = 'n';
        (*p_it)[2] = 'c';
    }
    else if ((*p_it)[0] == 'i')
    {
        (*p_it)[0] = 'd';
        (*p_it)[1] = 'e';
        (*p_it)[2] = 'c';
    }
    else if ((*p_it)[0] == 'c')
    {
        (*p_it)[0] = 'j';
        (*p_it)[1] = 'n';
        (*p_it)[2] = 'z';
    }
    else if ((*p_it)[0] == 'j')
    {
        (*p_it)[0] = 'c';
        (*p_it)[1] = 'p';
        (*p_it)[2] = 'y';
    }
    else if ((*p_it)[0] == 't')
    {
        (*p_it)[0] = 'i';
        (*p_it)[1] = 'n';
        (*p_it)[2] = 'c';
    }
    p_it-=l_distance;
}

void handleSpecial()
{
    a += b*d;
    c = 0;
    d = 0;
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
//    a = 7;
    a = 12; // PART TWO
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
                it = handleJnz(l_item, p_vector, it);
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
            else if(l_item[0] == 't')
            {
                handleTgl(l_item, p_vector, it);
                it++;
            }
            else if(l_item[0] == 's')
            {
                handleSpecial();
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

/*
 * --- Day 23: Safe Cracking ---

This is one of the top floors of the nicest tower in EBHQ. The Easter Bunny's private office is here, complete with a safe hidden behind a painting, and who wouldn't hide a star in a safe behind a painting?

The safe has a digital screen and keypad for code entry. A sticky note attached to the safe has a password hint on it: "eggs". The painting is of a large rabbit coloring some eggs. You see 7.

When you go to type the code, though, nothing appears on the display; instead, the keypad comes apart in your hands, apparently having been smashed. Behind it is some kind of socket - one that matches a connector in your prototype computer! You pull apart the smashed keypad and extract the logic circuit, plug it into your computer, and plug your computer into the safe.

Now, you just need to figure out what output the keypad would have sent to the safe. You extract the assembunny code from the logic chip (your puzzle input).

The code looks like it uses almost the same architecture and instruction set that the monorail computer used! You should be able to use the same assembunny interpreter for this as you did there, but with one new instruction:

tgl x toggles the instruction x away (pointing at instructions like jnz does: positive means forward; negative means backward):

    For one-argument instructions, inc becomes dec, and all other one-argument instructions become inc.
    For two-argument instructions, jnz becomes cpy, and all other two-instructions become jnz.
    The arguments of a toggled instruction are not affected.
    If an attempt is made to toggle an instruction outside the program, nothing happens.
    If toggling produces an invalid instruction (like cpy 1 2) and an attempt is later made to execute that instruction, skip it instead.
    If tgl toggles itself (for example, if a is 0, tgl a would target itself and become inc a), the resulting instruction is not executed until the next time it is reached.

For example, given this program:

cpy 2 a
tgl a
tgl a
tgl a
cpy 1 a
dec a
dec a

    cpy 2 a initializes register a to 2.
    The first tgl a toggles an instruction a (2) away from it, which changes the third tgl a into inc a.
    The second tgl a also modifies an instruction 2 away from it, which changes the cpy 1 a into jnz 1 a.
    The fourth line, which is now inc a, increments a to 3.
    Finally, the fifth line, which is now jnz 1 a, jumps a (3) instructions ahead, skipping the dec a instructions.

In this example, the final value in register a is 3.

The rest of the electronics seem to place the keypad entry (the number of eggs, 7) in register a, run the code, and then send the value left in register a to the safe.

What value should be sent to the safe?

Your puzzle answer was 11123.

--- Part Two ---

The safe doesn't open, but it does make several angry noises to express its frustration.

You're quite sure your logic is working correctly, so the only other thing is... you check the painting again. As it turns out, colored eggs are still eggs. Now you count 12.

As you run the program with this new input, the prototype computer begins to overheat. You wonder what's taking so long, and whether the lack of any instruction more powerful than "add one" has anything to do with it. Don't bunnies usually multiply?

Anyway, what value should actually be sent to the safe?

Your puzzle answer was 479007683.
*/
