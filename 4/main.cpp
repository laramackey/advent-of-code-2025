//
// Created by lara on 12/4/25.
//

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

std::vector<std::vector<int>> file_to_grid(std::ifstream &file)
{
    std::string line;
    std::vector<std::vector<int>> grid;
    while (std::getline(file, line))
    {
        std::vector<int> row;
        row.reserve(line.size());
        for (char c : line)
        {
            if (c == '@') row.push_back(1);
            else if (c == '.')  row.push_back(0);
        }
        grid.push_back(std::move(row));
    }
    return grid;
}

bool is_accessible(const std::vector<std::vector<int>> &grid, size_t x, size_t y)
{
    int count = 0;
    for (int delta_x = -1; delta_x <= 1; ++delta_x)
    {
        for (int delta_y = -1; delta_y <= 1; ++delta_y)
        {
            if (delta_x == 0 && delta_y == 0) continue;
            int new_x = static_cast<int>(x) + delta_x;
            int new_y = static_cast<int>(y) + delta_y;
            if (new_y >= 0 && new_y < grid.size() &&
                new_x >= 0 && new_x < grid[new_y].size())
            {
                if (grid[new_y][new_x] == 1)
                {
                    count++;
                    if (count == 4) return false;
                }
            }
        }
    }
    return true;
}

struct Result {
    int accessible_count;
    std::vector<std::vector<int>> grid;
};

Result find_paper_rolls(std::vector<std::vector<int>> &grid, int task)
{
    int accessible_count = 0;
    for (size_t y = 0; y < grid.size(); ++y)
    {
        for (size_t x = 0; x < grid[y].size(); ++x)
        {
            if (grid[y][x] == 1 && is_accessible(grid, x, y))
            {
                accessible_count++;
                if (task == 2) grid[y][x] = 0;
            }
        }
    }
    return { accessible_count, grid };
}

Result find_paper_rolls_and_remove(const std::vector<std::vector<int>> &grid)
{
    std::vector<std::vector<int>> current = grid;
    int accessible_count = 0;
    while (true)
    {
        auto result = find_paper_rolls(current, 2);
        if (result.accessible_count == 0)
            break;
        accessible_count += result.accessible_count;
    }
    return { accessible_count, grid };
}

int main()
{
    std::ifstream file("input.txt");
    auto grid = file_to_grid(file);

    auto task1 = find_paper_rolls(grid, 1);
    std::cout << "No. of paper rolls task 1: " << task1.accessible_count << "\n";

    auto task2 = find_paper_rolls_and_remove(grid);
    std::cout << "No. of paper rolls task 2: " << task2.accessible_count << "\n";
}
