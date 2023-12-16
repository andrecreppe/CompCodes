#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
#include <stack>
#include <iomanip>

using namespace std;

struct Point {
    long long x, y;
};

typedef vector<Point> vP;

bool compare(Point p1, Point p2) {
    double angle1 = atan2(p1.y, p1.x);
    double angle2 = atan2(p2.y, p2.x);

    if (angle1 < angle2) return true;
    else if (angle1 == angle2 && p1.x < p2.x) return true;
    
    return false;
}

// Graham's scan algorithm
vP convexHull(vP& points) {
    int n = points.size();

    int lowest = 0;
    for (int i = 1; i < n; i++) {
        if (points[i].y < points[lowest].y || (points[i].y == points[lowest].y && points[i].x < points[lowest].x))
            lowest = i;
    }

    swap(points[0], points[lowest]);
	
    sort(points.begin() + 1, points.end(), compare);

    stack<Point> hull;
    hull.push(points[0]);
    hull.push(points[1]);
    hull.push(points[2]);

    for (int i = 3; i < n; i++) {
        while (hull.size() > 1) {
            Point top = hull.top();
            hull.pop();
            Point nextToTop = hull.top();

            if ((points[i].x - nextToTop.x) * (top.y - nextToTop.y) -
                (points[i].y - nextToTop.y) * (top.x - nextToTop.x) < 0) {
                hull.push(top);
                break;
            }
        }
        hull.push(points[i]);
    }

    vP result;
    while (!hull.empty()) {
        result.push_back(hull.top());
        hull.pop();
    }

    reverse(result.begin(), result.end());

    return result;
}

double distance(Point p1, Point p2) {
    return hypot(p2.x - p1.x, p2.y - p1.y);
}

int main() {
	int n;
	cin >> n;

	vP points(n);
	for(int i = 0; i < n; i++) {
		cin >> points[i].x >> points[i].y;
	}

    vP convexHullPoints = convexHull(points);

    // cout << "Convex Hull Points:\n";
    // for (const Point& p : convexHullPoints) {
    //     cout << "(" << p.x << ", " << p.y << ")\n";
    // }

    long double perimeterSum = 0.0;
    for (int i = 0; i < convexHullPoints.size(); i++) {
        int next = (i + 1) % convexHullPoints.size();
        perimeterSum += distance(convexHullPoints[i], convexHullPoints[next]);
    }

    cout << fixed << setprecision(6) << perimeterSum;

    return 0;
}
