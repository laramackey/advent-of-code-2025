//
// Created by lara on 12/3/25.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>


unsigned long long joltage(std::ifstream &file, int number_of_digits)
{
    file.clear();
    file.seekg(0);
    std::string line;
    unsigned long long total = 0;

    while (std::getline(file, line))
    {
        std::vector<char> stack;
        const int line_size = line.size();

        for (int i = 0; i < line_size; i++)
        {
            char c = line[i];
            while (!stack.empty() && c > stack.back() && (stack.size() - 1 + line_size - i) >= number_of_digits)
            {
                stack.pop_back();
            }
            if (stack.size() < number_of_digits)
            {
                stack.push_back(c);
            }
        }
        auto largest12 = std::string(stack.begin(), stack.end());
        total += std::stoull(largest12);
    }
    return total;
}

int main()
{
    std::ifstream file("input.txt");
    const long long task1 = joltage(file, 2);
    const long long task2 = joltage(file, 12);
    std::cout << "Max joltage 1: " << task1 << "\n";
    std::cout << "Max joltage 2: " << task2 << "\n";
    return 0;
}