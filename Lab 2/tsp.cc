#include "Point.hh"
#include <cmath>
#include <iostream>
#include <vector>


using namespace std;

/* This function takes a vector of points, and the order
 * in which those points are visited, and it computes the
 * total length of the path when the points are traveled
 * in the specified order.
 */
double circuitLength(const vector<Point> &points, const vector<int> &order){
    double totalDistance = 0;
    int i;
    for (i = 0; i < points.size() - 1; i++){
        totalDistance += points[order[i]].distanceTo(points[order[i + 1]]);
    }
    totalDistance += points[order[points.size() - 1]].distanceTo(points[order[0]]);
    return totalDistance;
}

/* This function takes a vector of points and finds the 
 * shortest path between them using a simple brute-force method
 * of comparing every single path to each other. It uses the
 * next_permutation algorithm to change the visitOrder between
 * points.
 */
vector<int> findShortestPath(const vector<Point> &points){
    vector<int> visitOrder;
    double shortestDistance = numeric_limits<double>::infinity();
    vector<int> currentBest;
    int i;

    for (i = 0; i < points.size(); i++){
        visitOrder.push_back(i);
    }
    do{
        if (circuitLength(points, visitOrder) < shortestDistance)
        {
            shortestDistance = circuitLength(points, visitOrder);
            currentBest = visitOrder;
        }
    }
    while (next_permutation(visitOrder.begin(), visitOrder.end()));
    return currentBest;
}

int main(){
    int numPoints;
    double x, y, z;
    vector<Point> points;
    vector<int> finalPoints;
    Point p1;
    int i, j;

    cout << "How many points? ";
    cin >> numPoints;

    for (i = 0; i <= numPoints - 1; i++){
        cout << "Point " << i << ": ";
        cin >> x >> y >> z;
        p1 = Point(x, y, z);
        points.push_back(p1);
    }

    finalPoints = findShortestPath(points);

    cout << "Best order:  [";

    for (j = 0; j < points.size(); j++){
        cout << ' ' << finalPoints[j];
    }

    cout << ']' << endl;
    
    double length = circuitLength(points, finalPoints);
    cout << "Shortest distance: " << length << endl;
}







