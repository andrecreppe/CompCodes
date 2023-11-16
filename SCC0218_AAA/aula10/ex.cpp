#include <stdio.h>
#include <vector>
#include <cmath>

#define SIEVE_LIMIT 10000000 // 10e7

using namespace std;

typedef long long ll;

vector<bool> sieve;

void createSieve(ll size) {
    sieve.resize(size + 1, true);

    sieve[0] = sieve[1] = false;  // 0 e 1 não são primos

    for (ll i=2; i*i <= size; ++i) {
        if (sieve[i]) {
            for (ll j = i*i; j <= size; j+=i)
                sieve[j] = false;
        }
    }
}

bool checkSieve(ll n) {
    if (n <= 1)
        return false;

    ll root = sqrt(n);
    return (sieve[root]) && (root * root == n);
}

bool checkDivisors(ll n) {
    int count = 0;

    for (ll i=1; i <= sqrt(n); ++i) {
        if(n % i == 0)
            count += (i*i == n) ? 1 : 2;

        if(count > 3)
            return false;
    }

    return true;
}

int main() {
    createSieve(SIEVE_LIMIT);
     
    int n;
    scanf("%d", &n);

    ll data;

    for(int i=0; i<n; i++) {
        scanf("%lld", &data);

        if(data <= SIEVE_LIMIT)
            printf("%d", checkSieve(data));
        else
            printf("%d", checkDivisors(data));
    }

    return 0;
}
