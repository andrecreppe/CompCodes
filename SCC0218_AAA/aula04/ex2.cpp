#include <iostream>
#include <vector>
#include <algorithm>

bool canDestroyAll(const std::vector<int>& positions, int k, int radius) {
    int count = 0;
    int lastPosition = positions[0];
    
    for (int i = 1; i < positions.size(); ++i) {
        if (positions[i] - lastPosition > radius) {
            int gap = positions[i] - lastPosition;
            // Calculate how many explosives are needed for this gap
            count += (gap - 1) / radius;
        }
        
        lastPosition = positions[i];
    }
    
    return (count <= k);
}

int smallestRadiusToDestroyAll(std::vector<int>& positions, int k) {
    int left = 0;
    int right = positions.back() - positions.front();
    
    while (left < right) {
        int mid = left + (right - left) / 2;
        
        if (canDestroyAll(positions, k, mid)) {
            right = mid;
        } else {
            left = mid + 1;
        }
    }
    
    return left;
}

int main() {
    int n, k;
    std::cin >> n >> k;
    std::vector<int> positions(n);
    
    for (int i = 0; i < n; ++i) {
        std::cin >> positions[i];
    }
    
    int smallestRadius = smallestRadiusToDestroyAll(positions, k);
    std::cout << smallestRadius << std::endl;
    
    return 0;
}
