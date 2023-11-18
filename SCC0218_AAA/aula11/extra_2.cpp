#include <stdio.h>

using namespace std;

typedef long long ll;

const ll BIG_NUM = 1000000007;

ll pot(ll a, ll b, ll p) {
    if(a == 0 && b == 0) return 1;
    if(a == 0) return 0;
    
    ll res = 1;
    while(b > 0) {
        // b is odd
        if(b%2 == 1)
            res = (res * a) % p;
        
        // b is even
        b = b/2;
        a = (a*a) % p;
    }
    
    return res;
}

int main() {
    ll t, a, b, c;
    
    scanf("%lld", &t);
    
    while(t > 0) {
        scanf("%lld %lld %lld", &a, &b, &c);
        printf("%lld\n", pot(a, pot(b, c, BIG_NUM-1), BIG_NUM));
        t--;
    }
    
    return 0;
}