#include <stdio.h>
#include <map>
#include <algorithm>

using namespace std;

void testFormat(const pair<int,int> &data) {
    printf("%d > %d\n", data.first, data.second);
}

int main() {
    // n = ammount of courses
    // k = ammount of students at that course
    // id = student ID (t)
    int n, k, id;
    map<int, int> course_list;
    map<int, int> student_enrolled;

    scanf("%d", &n);

    for(int i=1; i<=n; i++) { // courses start at 01
        scanf("%d", &k);

        course_list[i] = k;

        for(int j=0; j<k; j++) {
            scanf("%d", &id);

            if(!student_enrolled[id]) { // Student's first enrollment
                student_enrolled[id] = i;
            } else if(student_enrolled[id] == i) { // Student's second+ enrollment for the same course
                course_list[i]--; // repeated subscription
            } else if(student_enrolled[id] != i || student_enrolled[id] == -1) { // Student enrolled in multiple courses or banned (-1)
                int otherCourse = student_enrolled[id];

                course_list[i]--; // banned subscription
                course_list[otherCourse]--;
                student_enrolled[id] = -1;
            }
        }
    }

    // printf("\nstudent_enrolled:\n");
    // for_each(student_enrolled.begin(), student_enrolled.end(), testFormat);
    // printf("\ncourse_list\n");
    // for_each(course_list.begin(), course_list.end(), testFormat);

    for(int i=1; i<=n; i++) {
        printf("%d ", course_list[i]);
    }

    return 0;
}
