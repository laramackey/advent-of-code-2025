//
// Created by lara on 12/3/25.
//

#include <fstream>
#include <iostream>
#include <string>

int joltage(std::ifstream &file)
{
    std::string line;
    int total = 0;

    while (std::getline(file, line))
    {
        int largest_index = 0;
        int largest_value = line[0] - '0';
        for (int i = 1; i < line.size() - 1; i++) {
            if (const int digit = line[i] - '0'; digit > largest_value) {
                largest_value = digit;
                largest_index = i;
            }
        }
        int second_largest_value = line[largest_index + 1] - '0';
        for (int i = largest_index + 2; i < line.size(); i++) {
            if (const int digit = line[i] - '0'; digit > second_largest_value) {
                second_largest_value = digit;
            }
        }
        const int combined = largest_value * 10 + second_largest_value;
        total += combined;
    }

    return total;
}

int main()
{
    std::ifstream file("input.txt");
    const int j = joltage(file);
    std::cout << "Max joltage: " << j << "\n";

    return 0;
}
