//
// Created by lara on 12/5/25.
//

#include <fstream>
#include <string>
#include <vector>
#include <iostream>
#include <ranges>
#include <algorithm>

std::string trim(const std::string& str)
{
    size_t first = str.find_first_not_of(" \t\r\n");
    if (first == std::string::npos) return "";
    size_t last = str.find_last_not_of(" \t\r\n");
    return str.substr(first, last - first + 1);
}

void merge_ranges(std::vector<std::pair<long long,long long>>& ranges)
{
    if (ranges.empty()) return;
    std::ranges::sort(ranges, {}, &std::pair<long long,long long>::first);
    size_t write = 0;
    for (size_t i = 1; i < ranges.size(); ++i)
    {
        auto& last = ranges[write];
        auto& curr = ranges[i];

        if (curr.first <= last.second + 1)
        {
            last.second = std::max(last.second, curr.second);
        }
        else
        {
            ++write;
            ranges[write] = curr;
        }
    }
    ranges.resize(write + 1);
}

bool id_in_ranges(long long id, const std::vector<std::pair<long long,long long>>& ranges)
{
    long long left = 0;
    long long right = static_cast<long long>(ranges.size()) - 1;
    while (left <= right)
    {
        long long mid = (left + right) / 2;
        const auto& [start, end] = ranges[mid];
        if (id < start) right = mid - 1;
        else if (id > end) left = mid + 1;
        else return true;
    }
    return false;
}

int main()
{
    std::ifstream file("input.txt");
    std::vector<std::pair<long long,long long>> fresh_ingredients;
    std::vector<long long> ingredient_ids;
    for (std::string line; std::getline(file, line); )
    {
        std::string s = trim(line);
        if (s.empty()) continue;
        if (auto pos = s.find('-'); pos != std::string::npos)
        {
            long long a = std::stoll(s.substr(0, pos));
            long long b = std::stoll(s.substr(pos + 1));
            fresh_ingredients.emplace_back(a, b);
        }
        else
        {
            ingredient_ids.push_back(std::stoll(s));
        }
    }

    merge_ranges(fresh_ingredients);

    int fresh_count = 0;
    for (long long id : ingredient_ids)
    {
        if (id_in_ranges(id, fresh_ingredients)) fresh_count++;
    }

    std::cout << "Fresh count: " << fresh_count << "\n";

}
