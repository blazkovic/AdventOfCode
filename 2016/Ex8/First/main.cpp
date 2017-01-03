#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <algorithm>

std::string input =
        R"(rect 1x1
        rotate row y=0 by 20
        rect 1x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 3
        rect 2x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 3
        rect 2x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 4
        rect 2x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 3
        rect 2x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 5
        rect 1x1
        rotate row y=0 by 2
        rect 1x1
        rotate row y=0 by 6
        rect 5x1
        rotate row y=0 by 2
        rect 1x3
        rotate row y=2 by 8
        rotate row y=0 by 8
        rotate column x=0 by 1
        rect 7x1
        rotate row y=2 by 24
        rotate row y=0 by 20
        rotate column x=5 by 1
        rotate column x=4 by 2
        rotate column x=2 by 2
        rotate column x=0 by 1
        rect 7x1
        rotate column x=34 by 2
        rotate column x=22 by 1
        rotate column x=15 by 1
        rotate row y=2 by 18
        rotate row y=0 by 12
        rotate column x=8 by 2
        rotate column x=7 by 1
        rotate column x=5 by 2
        rotate column x=2 by 1
        rotate column x=0 by 1
        rect 9x1
        rotate row y=3 by 28
        rotate row y=1 by 28
        rotate row y=0 by 20
        rotate column x=18 by 1
        rotate column x=15 by 1
        rotate column x=14 by 1
        rotate column x=13 by 1
        rotate column x=12 by 2
        rotate column x=10 by 3
        rotate column x=8 by 1
        rotate column x=7 by 2
        rotate column x=6 by 1
        rotate column x=5 by 1
        rotate column x=3 by 1
        rotate column x=2 by 2
        rotate column x=0 by 1
        rect 19x1
        rotate column x=34 by 2
        rotate column x=24 by 1
        rotate column x=23 by 1
        rotate column x=14 by 1
        rotate column x=9 by 2
        rotate column x=4 by 2
        rotate row y=3 by 5
        rotate row y=2 by 3
        rotate row y=1 by 7
        rotate row y=0 by 5
        rotate column x=0 by 2
        rect 3x2
        rotate column x=16 by 2
        rotate row y=3 by 27
        rotate row y=2 by 5
        rotate row y=0 by 20
        rotate column x=8 by 2
        rotate column x=7 by 1
        rotate column x=5 by 1
        rotate column x=3 by 3
        rotate column x=2 by 1
        rotate column x=1 by 2
        rotate column x=0 by 1
        rect 9x1
        rotate row y=4 by 42
        rotate row y=3 by 40
        rotate row y=1 by 30
        rotate row y=0 by 40
        rotate column x=37 by 2
        rotate column x=36 by 3
        rotate column x=35 by 1
        rotate column x=33 by 1
        rotate column x=32 by 1
        rotate column x=31 by 3
        rotate column x=30 by 1
        rotate column x=28 by 1
        rotate column x=27 by 1
        rotate column x=25 by 1
        rotate column x=23 by 3
        rotate column x=22 by 1
        rotate column x=21 by 1
        rotate column x=20 by 1
        rotate column x=18 by 1
        rotate column x=17 by 1
        rotate column x=16 by 3
        rotate column x=15 by 1
        rotate column x=13 by 1
        rotate column x=12 by 1
        rotate column x=11 by 2
        rotate column x=10 by 1
        rotate column x=8 by 1
        rotate column x=7 by 2
        rotate column x=5 by 1
        rotate column x=3 by 3
        rotate column x=2 by 1
        rotate column x=1 by 1
        rotate column x=0 by 1
        rect 39x1
        rotate column x=44 by 2
        rotate column x=42 by 2
        rotate column x=35 by 5
        rotate column x=34 by 2
        rotate column x=32 by 2
        rotate column x=29 by 2
        rotate column x=25 by 5
        rotate column x=24 by 2
        rotate column x=19 by 2
        rotate column x=15 by 4
        rotate column x=14 by 2
        rotate column x=12 by 3
        rotate column x=9 by 2
        rotate column x=5 by 5
        rotate column x=4 by 2
        rotate row y=5 by 5
        rotate row y=4 by 38
        rotate row y=3 by 10
        rotate row y=2 by 46
        rotate row y=1 by 10
        rotate column x=48 by 4
        rotate column x=47 by 3
        rotate column x=46 by 3
        rotate column x=45 by 1
        rotate column x=43 by 1
        rotate column x=37 by 5
        rotate column x=36 by 5
        rotate column x=35 by 4
        rotate column x=33 by 1
        rotate column x=32 by 5
        rotate column x=31 by 5
        rotate column x=28 by 5
        rotate column x=27 by 5
        rotate column x=26 by 3
        rotate column x=25 by 4
        rotate column x=23 by 1
        rotate column x=17 by 5
        rotate column x=16 by 5
        rotate column x=13 by 1
        rotate column x=12 by 5
        rotate column x=11 by 5
        rotate column x=3 by 1
        rotate column x=0 by 1
)";

class Display
{
public:
    void rotateColumnDown(int p_column, int p_value)
    {
        std::string l_stringToShift(m_rowsNumber, '0');
        for (auto i = 0; i < m_rowsNumber; i++)
        {
            l_stringToShift[i] = m_display[p_column + i*m_columnsNumber];
        }
        for (auto i = 0; i < p_value; i++)
        {
            l_stringToShift.insert(0, 1, *(l_stringToShift.end() -1));
            l_stringToShift.pop_back();
        }
        for (auto i = 0; i < m_rowsNumber; i++)
        {
            m_display[p_column + i*m_columnsNumber] = l_stringToShift[i];
        }
    }

    void rotateRowRight(int p_row, int p_value)
    {
        std::string l_stringToShift(m_display, p_row*m_columnsNumber, m_columnsNumber);
        for (auto i = 0; i < p_value; i++)
        {
            l_stringToShift.insert(0, 1, *(l_stringToShift.end()-1));
            l_stringToShift.pop_back();
        }
        for(auto i = 0; i < m_columnsNumber; i++)
        {
            m_display[p_row*m_columnsNumber + i] = l_stringToShift[i];
        }
    }

    void setRectangle(int p_columns, int p_rows)
    {
        for (auto i = 0; i < p_rows; i++)
        {
            for (auto j = 0; j < p_columns; j++)
            {
                m_display[i*m_columnsNumber + j] = '1';
            }
        }
    }

    int countSetValues() const
    {
        return std::count(m_display.begin(), m_display.end(), '1');
    }

private:
    const static auto m_rowsNumber = 6;
    const static auto m_columnsNumber = 50;
    std::string m_display = std::string(m_rowsNumber*m_columnsNumber, '0');
};

class DisplayManager
{
public:
    void parseCommand(const std::string & p_command)
    {
        if (p_command.find("rotate", 0) != std::string::npos)
        {
            if (p_command.find("column", 0) != std::string::npos)
            {
                    auto l_it = std::find(p_command.begin()+14, p_command.end(), 'b');
                    auto l_columnNumber = std::string(p_command.begin()+14, l_it);
                    auto l_offset = std::string(l_it+2, p_command.end());
                    m_display.rotateColumnDown(std::stoul(l_columnNumber), std::stoul(l_offset));
            }
            if (p_command.find("row", 0) != std::string::npos)
            {
                auto l_it = std::find(p_command.begin()+11, p_command.end(), 'b');
                auto l_rowNumber = std::string(p_command.begin()+11, l_it);
                auto l_offset = std::string(l_it+2, p_command.end());
                m_display.rotateRowRight(std::stoul(l_rowNumber), std::stoul(l_offset));
            }
        }
        if (p_command.find("rect", 0) != std::string::npos)
        {
            auto l_it = std::find(p_command.begin()+4, p_command.end(), 'x');
            auto l_columns = std::string(p_command.begin()+4, l_it);
            auto l_rows = std::string(l_it+1, p_command.end());
            m_display.setRectangle(std::stoul(l_columns), std::stoul(l_rows));
        }
    }

    int countSetValues() const
    {
        return m_display.countSetValues();
    }

private:
    Display m_display;
};

void removeSpaces(std::string & p_input)
{
    p_input.erase(remove_if(p_input.begin(), p_input.end(), isblank), p_input.end());
}

int main()
{
    DisplayManager l_displayManager;
    removeSpaces(input);
    std::istringstream l_input(input);
    std::string l_item;
    while(getline(l_input, l_item, '\n'))
    {
        l_displayManager.parseCommand(l_item);
    }

    std::cout << "Number of set pixels = " << l_displayManager.countSetValues() << std::endl;

    return 0;
}

/*
--- Day 8: Two-Factor Authentication ---

You come across a door implementing what you can only assume is an implementation of two-factor authentication after a long game of requirements telephone.

To get past the door, you first swipe a keycard (no problem; there was one on a nearby desk). Then, it displays a code on a little screen, and you type that code on a keypad. Then, presumably, the door unlocks.

Unfortunately, the screen has been smashed. After a few minutes, you've taken everything apart and figured out how it works. Now you just have to work out what the screen would have displayed.

The magnetic strip on the card you swiped encodes a series of instructions for the screen; these instructions are your puzzle input. The screen is 50 pixels wide and 6 pixels tall, all of which start off, and is capable of three somewhat peculiar operations:

    rect AxB turns on all of the pixels in a rectangle at the top-left of the screen which is A wide and B tall.
    rotate row y=A by B shifts all of the pixels in row A (0 is the top row) right by B pixels. Pixels that would fall off the right end appear at the left end of the row.
    rotate column x=A by B shifts all of the pixels in column A (0 is the left column) down by B pixels. Pixels that would fall off the bottom appear at the top of the column.

For example, here is a simple sequence on a smaller screen:

    rect 3x2 creates a small rectangle in the top-left corner:

    ###....
    ###....
    .......

    rotate column x=1 by 1 rotates the second column down by one pixel:

    #.#....
    ###....
    .#.....

    rotate row y=0 by 4 rotates the top row right by four pixels:

    ....#.#
    ###....
    .#.....

    rotate column x=1 by 1 again rotates the second column down by one pixel, causing the bottom pixel to wrap back to the top:

    .#..#.#
    #.#....
    .#.....

As you can see, this display technology is extremely powerful, and will soon dominate the tiny-code-displaying-screen market. That's what the advertisement on the back of the display tries to convince you, anyway.

There seems to be an intermediate check of the voltage used by the display: after you swipe your card, if the screen did work, how many pixels should be lit?
*/
