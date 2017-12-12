#include <iostream>

int calculateDistance(const int value)
{
    auto x = 0;
    auto y = 0;
    auto dx = 0;
    auto dy = -1;
    auto temp = 0;

    for(auto i = 0; i != value; ++i)
    {
        if (x == y || ((x > 0 && x == 1 - y ) || (x < 0 && x == -y)))
        {
            temp = dx;
            dx = -dy;
            dy = temp;
        }

        x += dx;
        y += dy;
        //std::cout << "(" << x << ", " << y << ")";
    }
    return std::abs(x) + std::abs(y) - 1;
}

int main()
{
    constexpr auto input = 361527;
    std::cout << calculateDistance(input) << std::endl;
    return 0;
}
