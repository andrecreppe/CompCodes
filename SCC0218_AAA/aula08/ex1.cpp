#include <stdio.h>
#include <vector>
#include <algorithm>
#include <cstdint>

using namespace std;

typedef vector<int64_t> vi;
typedef vector<vi> vii;

int64_t n, K;
vii shop, mem;

int64_t vinaShop(int64_t day, int64_t prevIndex) {
    if (day == n) {
        return 0;
    }

    if (mem[day][prevIndex] != -1) {
        return mem[day][prevIndex];
    }

    int64_t maxCost = 0;
    for (int64_t i=0; i<K; i++) {
        if (i != prevIndex) {
            maxCost = max(maxCost, shop[day][i] + vinaShop(day+1, i));
        }
    }

    return mem[day][prevIndex] = maxCost;
}

int main() {
    scanf("%lld %lld", &n, &K);

    shop.assign(n, vi(K));
    mem.assign(n, vi(K, -1));

    for (int64_t i=0; i<n; i++) {
        for (int64_t j=0; j<K; j++) {
            scanf("%lld", &shop[i][j]);
        }
    }

    // n = 3; K = 4;
    // shop = {
    //     {10, 40, 70, 10},
    //     {20, 50, 80, 15},
    //     {30, 60, 90, 50}
    // };

    int64_t cost = 0;
    for (int64_t i=0; i<K; i++) {
        cost = max(cost, shop[0][i] + vinaShop(1, i));
    }

    printf("%lld", cost);

    return 0;
}
