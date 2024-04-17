// NOJ Problem #470 - Rabbit Hole

// Reference:
// https://web.ntnu.edu.tw/~algo/Polygon.html
// https://web.ntnu.edu.tw/~algo/ConvexHull.html
// https://en.wikibooks.org/wiki/Algorithm_Implementation/Geometry/Convex_hull/Monotone_chain
// https://chat.openai.com/chat
// https://rechneronline.de/pi/simple-polygon.php

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class Point
{
    public:
        long long x;
        long long y;

    bool operator <(const Point &p) const 
    {
		return x < p.x || (x == p.x && y < p.y);
	}
};

long long cross(Point a, Point b, Point c) 
{
    return (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
}

int main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0);
    cout.tie(0);

    long long n;
    cin >> n;
    vector<Point> p(n);
    for(int i = 0; i < n; i++)
    {
        cin >> p[i].x >> p[i].y;
    }

    // Convex Hull: Andrew's Monotone Chain
    sort(p.begin(), p.end());
    vector<Point> convex;
    for (int i = 0; i < n; i++) 
    {
        while (convex.size() >= 2 && cross(convex[convex.size()-2], convex.back(), p[i]) <= 0) convex.pop_back();
        convex.push_back(p[i]);
    }
    for (int i = n-1, t = convex.size()+1; i > 0; i--) 
    {
        while (convex.size() >= t && cross(convex[convex.size()-2], convex.back(), p[i-1]) <= 0) convex.pop_back();
        convex.push_back(p[i-1]);
    }
    convex.pop_back();

    // Polygon Area: Surveyor's Formula
    long long area = 0;
    long long c_n = convex.size();
    for (int i = 0; i < c_n; i++) 
    {
        area += convex[i].x * convex[(i+1)%c_n].y - convex[i].y * convex[(i+1)%c_n].x;
    }
    string point_str =  (area%2) ? ".5" : "";
    area = abs(area) / 2;
    cout << area << point_str << endl;
    return 0;
}