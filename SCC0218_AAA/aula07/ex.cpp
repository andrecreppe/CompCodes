#include <stdio.h>
#include <vector>
#include <cmath>

using namespace std;

long long n;
vector<long long> d;    // songs
vector<long long> dp;   // cost

long long minCost(int i) {
    if(i >= n-1)
        return 0;

    if(dp[i] != -1)
        return dp[i];

    long long cost1 = abs(d[i] - d[i+1]) + minCost(i+1);
    long long cost2 = abs(d[i] - d[i+2]) + minCost(i+2);
    dp[i] = min(cost1, cost2);

    return dp[i];
}

int main() {
    scanf("%lld", &n);

    d.resize(n);
    dp.assign(n, -1);

    for(long long i=0; i<n; i++)
        scanf("%lld", &d[i]);

    long long min_cost = minCost(0);
    printf("%lld", min_cost);

    // printf("\ndp: ");
    // for(int i=0; i<n; i++)
    //     printf("%lld ", dp[i]);

    return 0;
}
