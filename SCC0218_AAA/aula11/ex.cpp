#include <stdio.h>

using namespace std;

typedef long long ll;

ll game(ll n, ll k) {
    int count = 0;

    while(n > 0) {
        int rem = n % k;
        if(rem == 0) {
            n /= k;
            count++;
        } else {
            count += rem;
            n -= rem;
        }
    }

    return count;
}

int main() {
    int t;
    ll n, k;

    scanf("%d", &t);

    for(int i=0; i<t; i++) {
        scanf("%lld %lld", &n, &k);

        printf("%lld\n", game(n, k));
    }

    return 0;
}
