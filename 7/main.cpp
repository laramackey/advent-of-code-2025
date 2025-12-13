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
    std::ifstream file("input.txt");
    std::vector<std::string> rows;
    std::string line;
    std::vector<std::pair<int, int>> dfs_stack;
    std::pair<int, int> pos = {0,0};
    int path_count = 0;

    while (std::getline(file, line))
    {
        rows.push_back(line);
    };

    while (true)
    {
        // start position
        if (pos.first == 0 and pos.second == 0) pos = {rows[0].find('S'), 0};
        else
        {
            if (rows[pos.second][pos.first] == '^')
            {
                // add splitter to dfs stack
                dfs_stack.push_back(pos);
                // go left and down
                pos.first--;
                pos.second++;
            } else if (pos.second == rows.size() - 1)
            {
                // reached bottom, increment path count
                path_count++;
                // if no more paths to follow, break out of loop
                if (dfs_stack.empty()) break;
                // if more paths to follow, go back to last splitter and go right and down
                auto last_splitter = dfs_stack.back();
                pos.first = last_splitter.first + 1;
                pos.second = last_splitter.second + 1;
                // both paths followed for splitter, remove it
                dfs_stack.pop_back();
            } else
            {
                // go straight down
                pos.second++;
            }
        }
    }
    std::cout << path_count << std::endl;
    return 0;
}

int main()
{
    task_two();
    return 0;
}