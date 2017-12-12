#include <iostream>
#include <map>

int calculateNextValue(const int value)
{
    std::map<std::pair<int, int>, int> matrix{{}};
    auto x = 0;
    auto y = 0;
    auto dx = 0;
    auto dy = -1;
    auto temp = 0;
    matrix[std::make_pair(x, y)] = 1;

    for(auto i = 0;; ++i)
    {
        if (matrix[std::make_pair(x, y)] > value) return matrix[std::make_pair(x, y)];
        std::cout << "x = " << x << " y = " << y << " matrix[std::make_pair(x, y)] = " << matrix[std::make_pair(x, y)] << std::endl;

        if (x == y || ((x > 0 && x == 1 - y) || (x < 0 && x  == -y)))
        {
            temp = dx;
            dx = -dy;
            dy = temp;
        }
        x += dx;
        y += dy;
        matrix[std::make_pair(x, y)] = matrix[std::make_pair(x+1, y)] + matrix[std::make_pair(x-1, y)] +
                                       matrix[std::make_pair(x, y+1)] + matrix[std::make_pair(x, y-1)] +
                                       matrix[std::make_pair(x+1, y-1)] + matrix[std::make_pair(x+1, y+1)] +
                                       matrix[std::make_pair(x-1, y+1)] + matrix[std::make_pair(x-1, y-1)];
    }

    return 0;
}

int main()
{
    constexpr auto input = 361527;
    std::cout << calculateNextValue(input) << std::endl;
    return 0;
}
