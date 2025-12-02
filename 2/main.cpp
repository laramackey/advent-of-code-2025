//
// Created by lara on 12/2/25.
//

#include <iostream>
#include <ranges>
#include <string>
#include <fstream>
#include <sstream>
#include <cmath>

int digits(long long n)
{
    if (n == 0) return 1;
    return std::log10(std::llabs(n)) + 1;
}

long long part_one(std::ifstream &file)
{
    long long total = 0;
    std::string line;

    file.clear();
    file.seekg(0);

    while (std::getline(file, line, ','))
    {
        std::stringstream ss2(line);
        std::string lower, upper;
        if (std::getline(ss2, lower, '-') && std::getline(ss2, upper)) {
            for (long long i = std::stoll(lower); i <= std::stoll(upper); i++)
            {
                if (int number_of_digits = digits(i); number_of_digits % 2 == 0)
                {
                    int divisor = std::pow(10, number_of_digits / 2);
                    if (i / divisor == i % divisor) total += i;
                }
            }
        }
    }
    return total;
}

int main()
{
    std::ifstream file("input.txt");
    const long long part1 = part_one(file);
    std::cout << part1 << "\n";
    return 0;
}
