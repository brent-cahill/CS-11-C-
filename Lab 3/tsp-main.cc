#include "tsp-ga.hh"
#include <cmath>
#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <string>

using namespace std;

void usage(string error){
    cerr << error << endl;
}

int main(int argc, char** argv){
    if (argc > 5) {
        usage("Too many arguments");
        return 1; // Indicate there was an issue
    }

    int n1 = (int) atoi(argv[1]);
    int n2 = (int) atoi(argv[2]);
    float f1 = (float) atof(argv[3]);
    float f2 = (float) atof(argv[4]);
    if (n1 < 0 || n2 < 0 || f1 < 0 || f1 > 1 || f2 < 0) {
        usage("One or more of the arguments to tsp-ga was an invalid value");
        return 1; // Indicate there was an issue
    }
    int numPoints;
    int i, j, x, y, z;
    Point p1;
    vector<Point> points;

    srand(time(nullptr));

    cout << "Number of points?: ";
    cin >> numPoints;

    for (i = 0; i < numPoints; i++){
        cout << "Point " << i << ": " << endl;
        cin >> x >> y >> z;
        p1 = Point(x, y, z);
        points.push_back(p1);
    }


    float keepPop2 = atof(argv[3]) * atoi(argv[1]);

    int keepPop = keepPop2;

    TSPGenome genome = findAShortPath(points, atoi(argv[1]), atoi(argv[2]),
                           keepPop, atoi(argv[4]));
    
    cout << "Shortest distance: " << genome.getCircuitLength() << endl;
    cout << "Best Order: [";

    std::vector <int> finalPoints = genome.getOrder();
    for (j = 0; j < finalPoints.size(); j++){
        cout << ' ' << finalPoints[j];
    }
    cout << "]" << endl;
}