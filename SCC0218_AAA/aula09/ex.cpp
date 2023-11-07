#include <stdio.h>
#include <vector>
#include <algorithm>

using namespace std;

typedef pair<int, int> Edge;
typedef vector<Edge> Graph;
typedef vector<int> vi;
typedef vector<vi> vii;

const int INF = 1e9;

int main() {
    int n, m, u, v, d;

    scanf("%d %d", &n, &m);

    vector<Graph> adj(n + 1);
    vii dp(1 << n, vi(n + 1, INF));

    for(int i = 0; i < m; i++) {
        scanf("%d %d %d", &u, &v, &d);

        adj[u].emplace_back(v, d);
        adj[v].emplace_back(u, d);
    }

    // for (int u = 1; u <= n; u++) {
    //     printf("[%d] => ", u);
    //     for (auto& edge : adj[u]) {
    //         printf("%d (%d) ", edge.first, edge.second);
    //     }
    //     printf("\n");
    // }

    // for(int mask = 1; mask < (1 << n); mask++) {
    //     for (int u = 1; u <= n; u++) {
    //         printf("mask = %d, u = %d => dp = %d\n", mask, u, dp[mask][u]);
    //     }
    // }

    dp[1][1] = 0; // Begins at Lake 1

    for(int mask = 1; mask < (1 << n); mask++) {
        for(int u = 1; u <= n; u++) {
            if (!(mask & (1 << u - 1))) 
                continue;
            
            for (auto& edge : adj[u]) {
                int v = edge.first;
                int d = edge.second;
                
                if (mask & (1 << (v - 1))) 
                    continue;
                
                int new_dist = dp[mask][u] + d;
                int pos = mask | (1 << (v - 1));
                dp[pos][v] = min(dp[pos][v], new_dist);

                // printf("[%d](%d) => %d - %d\n", v, d, new_dist, dp[mask][u]);
                // printf("mask = %d, dp = %d\n", mask, dp[mask][u]);
            }
        }
    }

    // Get the smallest
    int min_dist = INF;
    for (int u = 2; u <= n; u++) {
        if (dp[(1 << n) - 1][u] != INF) {
            min_dist = min(min_dist, dp[(1 << n) - 1][u]);
        }
    }

    if (min_dist == INF) {
        printf("-1");
    } else {
        printf("%d", min_dist);
    }

    return 0;
}
