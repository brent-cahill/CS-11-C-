#include "tsp-ga.hh"
#include <cstdlib>
#include <set>
#include <algorithm>
#include <vector>
#include <assert.h>

using namespace std;

// Constructors
TSPGenome::TSPGenome(int numPoints){
    circuitLength = 1e9;

    for (int i = 0; i < numPoints; i++)
    {
        visitOrder.push_back(i);
    }

    random_shuffle(visitOrder.begin(), visitOrder.end());
}

TSPGenome::TSPGenome(const std::vector<int> &order){
    circuitLength = 1e9;

    visitOrder = order;
}

// Destructor - TSPGenome allocates no dynamic resources.
TSPGenome::~TSPGenome(){
  // no-op
}

// Mutator Methods

// Returns the order of the TSP Genome
std::vector<int> TSPGenome::getOrder() const{
    return visitOrder;
}

// Computes the total circuit length between the points given to the
// function using the current visitOrder and the distanceTo function.
void TSPGenome::computeCircuitLength(const std::vector<Point> &points){
    circuitLength = 0;
    for (int i = 0; i < points.size() - 1; i++){
        circuitLength +=
            points[visitOrder[i]].distanceTo(points[visitOrder[i + 1]]);
    }
    circuitLength +=
            points[visitOrder[points.size() - 1]].distanceTo(
                points[visitOrder[0]]);
}

// Returns the current circuit length
double TSPGenome::getCircuitLength() const{
    return circuitLength;
}

// Swaps points in the current visit order
void TSPGenome::mutate(){
    int point1 = rand() % visitOrder.size();
    int point2 = rand() % visitOrder.size();

    while(point2 == point1){
        point2 = rand() % visitOrder.size();
    }
    int pointVal2 = visitOrder[point1];

    visitOrder[point1] = visitOrder[point2];
    visitOrder[point2] = pointVal2;
}


// Creates a genomic offspring based off of two parent genomes.
// uses a random amount from the first genome and the rest from the second,
// ensuring no repetitions.
TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2){
    std::vector<int> newOrder;
    int k;
    int i = rand() % g1.getOrder().size();
    for (int j = 0; j < i; j++)
    {
        newOrder.push_back(g1.getOrder()[j]);
    }
    vector<int> sizer = g2.getOrder();
    int size = sizer.size();
    for (k = 0; k < size; k++)
    {
        if(std::find(newOrder.begin(), newOrder.end(), sizer[k]) == newOrder.end()){
            newOrder.push_back(sizer[k]);
        }
    }
    return TSPGenome(newOrder);
}

// helper function
bool isShorterPath(const TSPGenome &g1, const TSPGenome &g2){
    return (g1.getCircuitLength() < g2.getCircuitLength());
}

// Final function that incorporates all of the ones above it to find
// a short (not necessarily the shortest) path between the points.
TSPGenome findAShortPath(const vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations){
    vector<TSPGenome> genomes;
    for (int i = 0; i < populationSize; i++)
    {
        genomes.push_back(TSPGenome(points.size()));
    }
    for (int gen = 0; gen < numGenerations; gen++)
    {
        for (int i = 0; i < genomes.size(); i++)
        {
            genomes[i].computeCircuitLength(points);
        }

        sort(genomes.begin(), genomes.end(), isShorterPath);

        // gen is the generation #; it starts at 0
        // genomes is the vector of TSP genomes
        if (gen % 10 == 0) {
            cout << "Generation " << gen << ":  Shortest path is "
                 << genomes[0].getCircuitLength() << endl;
        }

        int g1, g2;
        int k;
        for (k = keepPopulation; k < populationSize; k++){
            g1 = rand() % keepPopulation;
            g2 = rand() % keepPopulation;
            while(g1 == g2){
                g2 = rand() % keepPopulation;
            }
            genomes[k] = crosslink(genomes[g1], genomes[g2]);
        }

        for (int l = 0; l < numMutations; l++)
        {
            genomes[1 + rand() % (populationSize - 1)].mutate();
        }
    }

    return genomes[0];
}








