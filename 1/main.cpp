//
// Created by lara on 12/1/25.
//

#include <fstream>
#include <iostream>
#include <string>
#include <cmath>

int password_one(std::ifstream &file)
{
    int dial_value = 50;
    int zero_counter = 0;
    std::string line;

    file.clear();
    file.seekg(0);

    while (std::getline(file, line))
    {
        constexpr int dial_size = 100;
        const char rotation_direction = line[0];
        const int rotation_distance = std::stoi(line.substr(1));
        const int direction_multiplier = (rotation_direction == 'R') ? 1 : -1;
        const int partial_distance = rotation_distance % dial_size;

        dial_value = dial_value + direction_multiplier * partial_distance;
        dial_value = (dial_value % dial_size + dial_size) % dial_size;
        if (dial_value == 0) zero_counter++;
    }
    return zero_counter;
}

int password_two(std::ifstream &file)
{
    int dial_value = 50;
    int zero_pass_counter = 0;
    std::string line;

    file.clear();
    file.seekg(0);

    while (std::getline(file, line))
    {
        constexpr int dial_size = 100;
        const char rotation_direction = line[0];
        const int rotation_distance = std::stoi(line.substr(1));
        const int direction_multiplier = (rotation_direction == 'R') ? 1 : -1;
        const int partial_distance = rotation_distance % dial_size;
        const int full_rotations = std::abs(rotation_distance) / dial_size;

        dial_value = dial_value + direction_multiplier * partial_distance;
        const bool crossed_zero = !((0 < dial_value) && (dial_value < dial_size)) &&
                            ((std::abs(dial_value - direction_multiplier * partial_distance) % dial_size) > 0);
        zero_pass_counter += full_rotations + (crossed_zero ? 1 : 0);
        dial_value = (dial_value % dial_size + dial_size) % dial_size;
    }
    return zero_pass_counter;
}

int main()
{
    std::ifstream file("input.txt");

    const int pw1 = password_one(file);
    const int pw2 = password_two(file);

    std::cout << "Password method 1: " << pw1 << "\n";
    std::cout << "Password method 0x434C49434B: " << pw2 << "\n";

    return 0;
}