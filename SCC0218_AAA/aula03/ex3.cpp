#include <stdio.h>
#include <vector>
#include <map>

using namespace std;

void calculateSubsetSums(const vector<int> &bees, map<int, int> &subsetSum) {
    int n = bees.size();
    int totalSubsets = 1 << n;  // Total number of subsets is 2^n

    for (int mask=0; mask < totalSubsets; ++mask) {
        int sum = 0;
        
        for (int i=0; i < n; ++i) {
            if (mask & (1 << i)) {
                sum += bees[i];
            }
        }

        subsetSum[sum] = 1;

        // Print Subset - Test only
        // printf("Sum: %d ", subsetSum);
        // printf("// Subset: ");
        // for (int i = 0; i < n; ++i) {
        //     if (mask & (1 << i)) {
        //         printf("%d ", bees[i]);
        //     }
        // }
        // printf("\n");
    }
}

int main() {
    int n, x;
    vector<int> bees;
    map<int, int> subsetSum;

    scanf("%d", &n);
    for(int i=0; i<n; i++) {
        scanf("%d", &x);
        bees.push_back(x);
    }

    calculateSubsetSums(bees, subsetSum);

    int sumSize = subsetSum.size() - 1; // -1 = empty subset
    printf("%d", sumSize);

    return 0;
}
