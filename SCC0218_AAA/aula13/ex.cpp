#include <stdio.h>
#include <vector>

using namespace std;

typedef long long ll;
typedef vector<ll> vll;

int main() {
    int T;
    scanf("%d", &T);

    while (T--) {
        int n;
        scanf("%d", &n);

        vll piles(n);
        int xor_sum = 0;

        for (ll i=0; i<n; i++) {
            scanf("%lld", &piles[i]);
            xor_sum ^= piles[i];
        }

        bool flag = true;

        for (ll i=0; i<n; i++) {
            if ((piles[i] ^ xor_sum) < piles[i]) {
                flag = false;
                break;
            }
        }

        printf("%d\n", flag);
    }

    return 0;
}
