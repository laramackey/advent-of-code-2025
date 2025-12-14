//
// Created by lara on 12/14/25.
//

#include <bits/stdc++.h>
using namespace std;

struct Box
{
    int x, y, z;
};

double euclidean_distance(const Box& a, const Box& b)
{
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    const double dz = a.z - b.z;
    return sqrt(dx*dx + dy*dy + dz*dz);
}

struct DSU
{
    vector<int> parent;

    DSU(size_t n) : parent(n)
    {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x)
    {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }

    void unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a != b)
            parent[b] = a;
    }
};

long long task_one() {
    ifstream file("input.txt");
    vector<Box> boxes;
    string line;

    while (getline(file, line))
    {
        Box v{};
        char comma;
        stringstream ss(line);
        ss >> v.x >> comma >> v.y >> comma >> v.z;
        boxes.push_back(v);
    }

    vector<pair<double, pair<int, int>>> distances;

    for (int i = 0; i < (int)boxes.size(); ++i)
    {
        for (int j = i + 1; j < (int)boxes.size(); ++j)
        {
            distances.push_back({
                euclidean_distance(boxes[i], boxes[j]),
                {i, j}
            });
        }
    }

    ranges::sort(distances);
    DSU dsu(boxes.size());

    int edges_used = min(1000, static_cast<int>(distances.size()));
    for (int i = 0; i < edges_used; ++i)
    {
        auto [a, b] = distances[i].second;
        dsu.unite(a, b);
    }

    unordered_map<int, int> component_size;
    for (int i = 0; i < static_cast<int>(boxes.size()); ++i)  component_size[dsu.find(i)]++;

    vector<int> sizes;
    for (auto &sz: component_size | views::values)
    {
        if (sz > 1)
            sizes.push_back(sz);
    }

    ranges::sort(sizes, greater<>());
    return 1LL * sizes[0] * sizes[1] * sizes[2];
}

int main() {
    const auto start = chrono::high_resolution_clock::now();

    const long long result = task_one();
    cout << "Result: " << result << '\n';

    const auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds.\n";

    return 0;
}
