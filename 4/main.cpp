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

int find_paper_rolls(std::ifstream &file)
{
    file.clear();
    file.seekg(0);

    auto grid = file_to_grid(file);
    int accessible_count = 0;

    for (int y = 0; y < grid.size(); ++y)
    {
        for (int x = 0; x < grid[y].size(); ++x)
        {
            if (grid[y][x] == 1) accessible_count += (is_accessible(grid, x, y) ? 1 : 0);
        }
    }
    return accessible_count;
}

int main()
{
    std::ifstream file("input.txt");
    const int task1 = find_paper_rolls(file);
    std::cout << "No. of paper rolls: " << task1 << "\n";
    return 0;
}