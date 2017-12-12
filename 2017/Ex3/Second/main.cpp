#include <iostream>
#include <array>

constexpr auto arraySize = 11;
constexpr auto offset = arraySize/2;

int calculateNextValue(const int value)
{
    std::array<std::array<int, arraySize>, arraySize> array{{}};
    auto x = offset;
    auto y = offset;
    auto dx = 0;
    auto dy = -1;
    auto temp = 0;
    array[x][y] = 1;

    for(auto i = 0;; ++i)
    {
        if (array[x][y] > value) return array[x][y];
        std::cout << "x = " << x << " y = " << y << " array[x][y] = " << array[x][y] << std::endl;

        if (x == y || ((x > offset && x - offset == 1 - y + offset ) || (x < offset && x - offset == -y + offset)))
        {
            temp = dx;
            dx = -dy;
            dy = temp;
        }
        x += dx;
        y += dy;
        array[x][y] = array[x+1][y] + array[x-1][y] + array[x][y+1] + array[x][y-1] +
                      array[x+1][y+1] + array[x+1][y-1] + array[x-1][y+1] + array[x-1][y-1];
    }

    return 0;
}

int main()
{
    constexpr auto input = 361527;
    std::cout << calculateNextValue(input) << std::endl;
    return 0;
}
