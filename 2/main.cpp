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
    return std::log10(n) + 1;
}

bool is_invalid_part1(long long i, int number_of_digits)
{
    if (number_of_digits % 2 != 0) return false;
    long long divisor = std::pow(10, number_of_digits / 2);
    return (i / divisor) == (i % divisor);
}

bool is_invalid_part2(long long i, int number_of_digits)
{
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
        if (repeated) return true;
    }
    return false;
}

long long get_invalid_id_sum(std::ifstream &file, int part)
{
    long long total = 0;
    std::string line;

    file.clear();
    file.seekg(0);

    while (std::getline(file, line, ',')) {
        std::stringstream ss2(line);
        std::string lower, upper;

        if (std::getline(ss2, lower, '-') && std::getline(ss2, upper)) {
            long long lo = std::stoll(lower);
            long long hi = std::stoll(upper);

            for (long long i = lo; i <= hi; i++) {
                bool valid = false;
                int number_of_digits = digits(i);

                switch (part) {
                    case 1: valid = is_invalid_part1(i, number_of_digits); break;
                    case 2: valid = is_invalid_part2(i, number_of_digits); break;
                    default: break;
                }

                if (valid) total += i;
            }
        }
    }
    return total;
}

int main()
{
    std::ifstream file("input.txt");

    const long long part1 = get_invalid_id_sum(file, 1);
    const long long part2 = get_invalid_id_sum(file, 2);

    std::cout << part1 << "\n";
    std::cout << part2 << "\n";

    return 0;
}