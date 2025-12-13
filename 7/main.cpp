//
// Created by lara on 12/13/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>

int task_one()
{
    std::ifstream file("input.txt");
    std::vector<std::string> rows;
    std::string line;
    std::set<int> beams;
    int split_count = 0;

    while (std::getline(file, line))
    {
        if (beams.empty()) beams.insert(line.find('S'));
        else
        {
            std::set<int> next_row;
            for (auto beam : beams)
            {
                if (line[beam] == '^')
                {
                    next_row.insert(beam - 1);
                    next_row.insert(beam + 1);
                    split_count++;
                } else next_row.insert(beam);
            }
            beams = next_row;
        }
    };

    std::cout << split_count << std::endl;

    return 0;
}

int task_two()
{

    return 0;
}

int main()
{
    task_one();
}