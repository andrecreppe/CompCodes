#include <stdio.h>

using namespace std;

typedef long long ll;

const ll BIG_NUM = 1000000007;

ll pot(ll a, ll b) {
    if(a == 0 && b == 0) return 1;
    if(a == 0) return 0;
    
    ll res = 1;

    while(b > 0) {
        // b is odd
        if(b%2 == 1)
            res = (res * a) % BIG_NUM;
        
        // b is even
        b = b/2;
        a = (a*a) % BIG_NUM;
    }
    
    return res;
}

int main() {
    ll t, a, b;
    
    scanf("%lld", &t);
    
    while(t > 0) {
        scanf("%lld %lld", &a, &b);
        printf("%lld\n", pot(a,b));
        t--;
    }
    
    return 0;
}