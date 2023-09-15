#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdint> // int64_t

using namespace std;

typedef pair<int64_t, int64_t> Edge;  // (src, dest)
typedef pair<int64_t, Edge> WeightedEdge;  // (weight, Edge)

vector<WeightedEdge> edges;  // graph

int64_t findParent(vector<int64_t>& parent, int64_t vertex) {
    if (parent[vertex] == -1)
        return vertex;
    return findParent(parent, parent[vertex]);
}

void unionSets(vector<int64_t>& parent, int64_t x, int64_t y) {
    int64_t xRoot = findParent(parent, x);
    int64_t yRoot = findParent(parent, y);
    parent[xRoot] = yRoot;
}

int64_t kruskalMST(int64_t n) {
    vector<Edge> result;
    int64_t totalWeight = 0; // Total weight of the MST
    sort(edges.begin(), edges.end(), [](const WeightedEdge& a, const WeightedEdge& b) {
        return a.first < b.first;
    });

    vector<int64_t> parent(n, -1);

    int64_t numComponents = n;

    for (WeightedEdge weightedEdge : edges) {
        Edge edge = weightedEdge.second;
        int64_t weight = weightedEdge.first;
        int64_t x = findParent(parent, edge.first);
        int64_t y = findParent(parent, edge.second);

        if (x != y) {
            result.push_back(edge);
            totalWeight += weight;
            unionSets(parent, x, y);
            numComponents--;

            if (numComponents == 1) {
                break;  // All vertices are connected
            }
        }
    }

    if (numComponents > 1) {
        return -1;
    } else {
        return totalWeight;
    }
}

int main() {
    int64_t n, m, u, v, c;
    scanf("%lld %lld", &n, &m);

    for(int64_t i=0; i<m; i++) {
        scanf("%lld %lld %lld", &u, &v, &c);
        edges.push_back({c, {u-1, v-1}});
    }

    int64_t ans = kruskalMST(n);
    printf("%d", ans);

    return 0;
}
