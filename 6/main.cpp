//
// Created by lara on 12/6/25.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

struct ColumnParseResult
{
    std::vector<size_t> starts;
    std::vector<char> operators;
};

ColumnParseResult find_column_starts_and_operators(const std::string& line)
{
    ColumnParseResult result;
    for (size_t i = 0; i < line.size(); ++i)
    {
        if (line[i] == '*' || line[i] == '+')
            result.operators.push_back(line[i]);

        if (line[i] != ' ' && (i == 0 || line[i - 1] == ' '))
            result.starts.push_back(i);
    }
    result.starts.push_back(line.size() + 2); //hack cause clion won't save file with trailing space
    return result;
}

std::vector<std::string> split_by_columns(const std::string& line,
                                        const std::vector<size_t>& starts)
{
    std::vector<std::string> out;
    out.reserve(starts.size() - 1);
    for (size_t i = 0; i + 1 < starts.size(); ++i)
    {
        out.push_back(line.substr(starts[i], starts[i + 1] - starts[i] - 1));
    }
    return out;
}

int main()
{
    std::ifstream file("input.txt");
    std::vector<std::string> rows;
    std::string line;

    // read file
    while (std::getline(file, line)) rows.push_back(line);

    // get column start points based on bottom row, and list of operator
    auto starts_and_operators = find_column_starts_and_operators(rows.back());
    std::vector<std::vector<std::string>> table;
    // split columns by the start points calculated from the bottom row in order to retain spaces
    for (auto& r : rows) table.push_back(split_by_columns(r, starts_and_operators.starts));


    long long total = 0;
    for (int i = 0; i < table[0].size(); i++)
    {
        char op = starts_and_operators.operators[i];
        long long column_res = op == '+' ? 0 : 1;
        //iterate through number right to left, if it's not a space, add it to number for that col index
        for (int j = table[0][i].size() - 1; j >= 0; --j)
        {
            std::string column_number;
            // check col index for all 4 number rows
            for (int k = 0; k < 4; k++)  if (table[k][i][j] != ' ') column_number += table[k][i][j];
            if (op == '+') column_res += std::stoi(column_number);
            else if (op == '*') column_res *= std::stoi(column_number);
        }
        total += column_res;
    }

    std::cout << total << std::endl;

    return 0;
}
