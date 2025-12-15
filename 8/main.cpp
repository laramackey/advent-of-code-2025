//
// Created by lara on 12/14/25.
//

#include <bits/stdc++.h>
using namespace std;

struct Box
{
    int x, y, z;
};

double distance(const Box& a, const Box& b)
{
    const double dx = a.x - b.x;
    const double dy = a.y - b.y;
    const double dz = a.z - b.z;
    return dx*dx + dy*dy + dz*dz;
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

    bool unite(int a, int b)
    {
        a = find(a);
        b = find(b);
        if (a == b) return false;
        parent[b] = a;
        return true;
    }
};

vector<Box> read_input(const string& filename)
{
    ifstream file(filename);
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
    return boxes;
}

vector<pair<double, pair<int,int>>> build_distances(const vector<Box>& boxes)
{
    vector<pair<double, pair<int,int>>> distances;
    for (int i = 0; i < (int)boxes.size(); ++i)
    {
        for (int j = i + 1; j < (int)boxes.size(); ++j)
        {
            distances.push_back({
                distance(boxes[i], boxes[j]),
                {i, j}
            });
        }
    }
    ranges::sort(distances);
    return distances;
}

long long part_one(
    const vector<Box>& boxes,
    const vector<pair<double, pair<int,int>>>& distances,
    int edges_used
)
{
    DSU dsu(boxes.size());

    for (int i = 0; i < edges_used && i < static_cast<int>(distances.size()); ++i)
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


long long part_two(
    const vector<Box>& boxes,
    const vector<pair<double, pair<int,int>>>& distances
)
{
    DSU dsu(boxes.size());
    int components = boxes.size();
    pair<int,int> last_edge{-1, -1};

    for (const auto &val: distances | views::values)
    {
        auto [a, b] = val;
        if (dsu.unite(a, b))
        {
            components--;
            last_edge = {a, b};
            if (components == 1)
                break;
        }
    }

    return 1LL * boxes[last_edge.first].x * boxes[last_edge.second].x;
}

int main() {
    auto start = chrono::high_resolution_clock::now();

    vector<Box> boxes = read_input("input.txt");
    auto distances = build_distances(boxes);

    long long p1 = part_one(boxes, distances, 1000);
    long long p2 = part_two(boxes, distances);

    cout << "Part One: " << p1 << '\n';
    cout << "Part Two: " << p2 << '\n';

    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> duration = end - start;
    cout << "Execution time: " << duration.count() << " seconds.\n";

    return 0;
}
