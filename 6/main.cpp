//
// Created by lara on 12/6/25.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

std::string trim(const std::string &s) {
    size_t start = s.find_first_not_of(' ');
    size_t end   = s.find_last_not_of(' ');
    if (start == std::string::npos) return "";
    return s.substr(start, end - start + 1);
}

int main() {
    std::ifstream file("input.txt");
    std::vector<std::vector<std::string>> columns;
    std::string line;

    while (std::getline(file, line))
    {
        std::vector<std::string> tokens;
        std::string token;
        std::stringstream ss(line);

        while (ss >> token)
        {
            tokens.push_back(token);
        }

        if (columns.empty()) columns.resize(tokens.size());

        for (size_t i = 0; i < tokens.size(); ++i)
        {
            columns[i].push_back(tokens[i]);
        }
    }

    long long total = 0;
    for (auto & v : columns)
    {
        char op = v.back()[0];
        long long result = std::stoll(v[0]);
        for (size_t i = 1; i < v.size() - 1; ++i)
        {
            long long num = std::stoll(v[i]);
            if (op == '+') result += num;
            else if (op == '*') result *= num;
        }
        total += result;
    }

    std::cout << "Total: " << total;

    return 0;
}
