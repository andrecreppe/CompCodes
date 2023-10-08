#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vii;

int64_t n, W;
vi weights, values;
vii memo;

int64_t backpack(int64_t n, int64_t W) {
    if (n == 0 || W == 0)
        return 0;

    if (memo[n][W] != -1)
        return memo[n][W];

    if (weights[n - 1] > W)
        memo[n][W] = backpack(n-1, W);
    else
        memo[n][W] = max(backpack(n-1, W), values[n-1] + backpack(n-1, W-weights[n-1]));

    return memo[n][W];
}

int main() {
    scanf("%lld %lld", &n, &W);

    weights.resize(n);
    values.resize(n);

    for (int64_t i=0; i<n; i++)
        scanf("%lld %lld", &weights[i], &values[i]);

    // n = 3;
    // W = 8;
    // weights = {3, 4, 5};
    // values = {30, 50, 60};

    memo.resize(n+1, vi(W+1, -1));

    int64_t ans = backpack(n, W);
    printf("%lld", ans);

    return 0;
}
