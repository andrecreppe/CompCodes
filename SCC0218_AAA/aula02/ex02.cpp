#include <stdio.h>
#include <map>

using namespace std;

int main() {
    int n, dist, pos, walkSize;
    int guards = 0, walkCount = 0;
    map<int,int> museum;

    scanf("%d %d", &n, &dist);

    walkSize = (dist*2) + 1; // true covered distance

    for(int i=0; i<n; i++) {
        scanf("%d", &pos);
        
        museum[pos] = 1;
    }

    while(pos >= 1) {
        if(museum[pos]) { // if there is a statue at this position
            guards++;
            pos -= walkSize;
        } else {
            pos--;
        }
    }

    printf("%d", guards);

    return 0;
}
