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
        for (const char c : line)
        {
            if (c == '@') row.push_back(1);
            else if (c == '.')  row.push_back(0);
        }
        grid.push_back(row);
    }
    return grid;
}

bool is_accessible(std::vector<std::vector<int>> grid, int x, int y)
{
    std::vector<int> x_values;
    if (x > 0) x_values.push_back(x - 1);
    if (x < grid[y].size() - 1) x_values.push_back(x + 1);
    x_values.push_back(x);

    std::vector<int> y_values;
    if (y > 0) y_values.push_back(y - 1);
    if (y < grid.size() - 1) y_values.push_back(y + 1);
    y_values.push_back(y);

    int blocking_neighbours = 0;
    for (const int check_x: x_values)
    {
        for (const int check_y: y_values)
        {
            if (!(check_x == x && check_y == y))
            {
                blocking_neighbours+= grid[check_y][check_x];
                if (blocking_neighbours == 4) return false;
            }
        }
    }
    return true;
}

struct Result {
    int accessible_count;
    std::vector<std::vector<int>> grid;
};

Result find_paper_rolls(std::vector<std::vector<int>>grid, int task)
{
    int accessible_count = 0;

    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            if (grid[y][x] == 1 && (is_accessible(grid, x, y)))
            {
                accessible_count++;
                if (task == 2) grid[y][x] = 0;
            }
        }
    }
    return { accessible_count, grid };
}

Result find_paper_rolls_and_remove(const std::vector<std::vector<int>>&grid)
{
    int accessible_count = 0;
    bool found_more = true;
    std::vector<std::vector<int>>current_grid = grid;
    while (found_more)
    {
        auto result = find_paper_rolls(current_grid, 2);
        current_grid = result.grid;
        if (result.accessible_count == 0) found_more = false;
        else accessible_count += result.accessible_count;
    }
    return { accessible_count, grid };
}

int main()
{
    std::ifstream file("input.txt");
    const auto grid = file_to_grid(file);
    const auto task1 = find_paper_rolls(grid, 1);
    std::cout << "No. of paper rolls task 1: " << task1.accessible_count << "\n";
    const auto task2 = find_paper_rolls_and_remove(grid);
    std::cout << "No. of paper rolls task 2: " << task2.accessible_count << "\n";
    return 0;
}