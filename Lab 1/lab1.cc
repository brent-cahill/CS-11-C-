#include "Point.hh"
#include <cmath>
#include <iostream>

using namespace std;

/* This function computes the area of the triangle created by
 * three points using Heron's formula.
 */
double computeArea (Point &a, Point &b, Point &c) {
    double semi = (a.distanceTo(b) + b.distanceTo(c) +
        c.distanceTo(a)) / 2;
    double squared = semi * (semi - a.distanceTo(b)) * (semi -
        b.distanceTo(c)) * (semi - c.distanceTo(a));
    return sqrt(squared);
}

int main() {
    double x, y, z;
    cout << "Enter x, y, and z coordinates for first point: ";
    cin >> x >> y >> z;
    Point p1 = Point(x, y, z);

    cout << "Enter x, y, and z coordinates for second point: ";
    cin >> x >> y >> z;
    Point p2 = Point(x, y, z);

    cout << "Enter x, y, and z coordinates for third point: ";
    cin >> x >> y >> z;
    Point p3 = Point(x, y, z);

    cout << "Point 1:  <" << p1.getX() << " " << p1.getY() << " " << p1.getZ() << ">" << endl;
    cout << "Point 1:  <" << p2.getX() << " " << p2.getY() << " " << p2.getZ() << ">" << endl;
    cout << "Point 1:  <" << p3.getX() << " " << p3.getY() << " " << p3.getZ() << ">" << endl;
    cout << "Area is:  <" << computeArea(p1, p2, p3) << ">" << endl;
    return 1;
}