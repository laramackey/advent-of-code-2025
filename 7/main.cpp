//
// Created by lara on 12/13/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <set>
#include <chrono>

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

long long dfs(
    int x,
    int y,
    const std::vector<std::string>& rows,
    std::vector<std::vector<long long>>& memo,
    int H,
    int W
)
{
    // reached bottom
    if (y == H - 1)
        return 1;

    long long& res = memo[y][x];
    if (res != -1)
        return res;

    if (rows[y][x] == '^')
        res = dfs(x - 1, y + 1, rows, memo, H, W)
            + dfs(x + 1, y + 1, rows, memo, H, W);
    else
        res = dfs(x, y + 1, rows, memo, H, W);

    return res;
}

int task_two()
{
    std::ifstream file("input.txt");
    std::vector<std::string> rows;
    std::string line;

    while (std::getline(file, line))
        rows.push_back(line);

    int H = rows.size();
    int W = rows[0].size();

    std::vector<std::vector<long long>> memo(
        H, std::vector<long long>(W, -1)
    );

    int start_x = rows[0].find('S');
    long long path_count = dfs(start_x, 0, rows, memo, H, W);

    std::cout << path_count << "\n";
    return 0;
}
int main()
{
    auto start = std::chrono::high_resolution_clock::now();
    task_two();
    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;
    std::cout << "Execution time: " << duration.count() << " seconds." << std::endl;
    return 0;
}