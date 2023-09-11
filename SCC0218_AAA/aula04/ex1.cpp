#include <stdio.h>
#include <vector>

using namespace std;

pair<long long, vector<int>> mergeCount(vector<int> v1, vector<int> v2) {
    vector<int> sorted;
    int i = 0, j = 0;
    long long inversions = 0;

    int len1 = v1.size();
    int len2 = v2.size();
    
    while(i<len1 && j<len2) {
        if(v1[i] <= v2[j]) {
            sorted.push_back(v1[i]);
            i++;
        } else {
            sorted.push_back(v2[j]);
            j++;
            inversions += (len1 - i);
        }
    }

    while (i < len1) {
        sorted.push_back(v1[i]);
        i++;
    }

    while (j < len2) {
        sorted.push_back(v2[j]);
        j++;
    }

    return {inversions, sorted};
}

pair<long long, vector<int>> divideCount(vector<int> data) {
    int n = data.size();

    if(n == 1) {
        return {0, data};
    }

    vector<int> v1 (data.begin(), data.begin() + n/2);
    vector<int> v2 (data.begin() + n/2, data.end());

    auto res1 = divideCount(v1);
    auto res2 = divideCount(v2);

    v1 = res1.second;
    v2 = res2.second;

    auto resMerge = mergeCount(v1, v2);

    long long inversions = res1.first + res2.first + resMerge.first;
    vector<int> merged = resMerge.second;
    
    return {inversions, merged};
}

int main() {
    int n, x;
    vector<int> data;
    pair<long long, vector<int>> ans;
    
    scanf("%d", &n);
    
    for(int i=0; i<n; i++) {
        scanf("%d", &x);
        data.push_back(x);
    }
    
    ans = divideCount(data);
    
    printf("%lld", ans.first);
    
    return 0;
}