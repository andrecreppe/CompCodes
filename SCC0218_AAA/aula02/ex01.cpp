#include <stdio.h>
#include <map>
#include <vector>
#include <algorithm>

using namespace std;

// void testFormat(const pair<int, pair<int,int>> &data) {
//     printf("%d > (%d - %d)\n", data.first, data.second.first, data.second.second);
// }

bool sortbysec(const pair<int,int> &a,
              const pair<int,int> &b) {
    return (a.second < b.second);
}

int main() {
    int n, start, end, endTime;
    int size = 0;

    pair<int,int> seminar, best;
    vector<pair<int,int>> calendar;

    scanf("%d", &n);

    for(int i=0; i<n; i++) {
        scanf("%d %d", &start, &end);

        seminar.first = start;
        seminar.second = end;

        calendar.push_back(seminar);
    }

    // sort(calendar.begin(), calendar.end()); // sort start time
    sort(calendar.begin(), calendar.end(), sortbysec);  // sort end time

    // printf("\nCalendar Sorted:\n");
    // for(int i=0; i<n; i++) {
    //     printf("(%d - %d)\n", calendar[i].first, calendar[i].second);
    // }

    // ===========================================

    best.first = calendar[0].second; // ending time
    best.second = 1; // seminar counting

    for(int i=1; i<n; i++) {
        if(best.first <= calendar[i].first) {
            best.first = calendar[i].second;
            best.second++;
        }
    }

    printf("%d", best.second);

    return 0;
}
