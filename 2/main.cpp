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

long long part_two(std::ifstream &file)
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
                int number_of_digits = digits(i);

                for (int block_size = 1; block_size <= number_of_digits / 2; block_size++) {
                    if (number_of_digits % block_size != 0) continue;

                    int number_of_blocks = number_of_digits / block_size;
                    long long first_block = i / static_cast<long long>(std::pow(10, number_of_digits - block_size));
                    bool repeated = false;

                    for (int j = 1; j < number_of_blocks; j++) {
                        const long long block =
                            (i / static_cast<long long>(std::pow(10, number_of_digits - (j + 1) * block_size))) %
                            static_cast<long long>(std::pow(10, block_size));
                        if (block != first_block) { repeated = false; break; }
                        repeated = true;
                    }
                    if (repeated) { total += i; break; }
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
    const long long part2 = part_two(file);
    std::cout << part1 << "\n";
    std::cout << part2 << "\n";
    return 0;
}
