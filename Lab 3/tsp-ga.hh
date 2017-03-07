#include "Point.hh"
#include <vector>
#include <iostream>

class TSPGenome{

private:
    double circuitLength;
    std::vector<int> visitOrder;

public:
    // Constructors
    TSPGenome(int numPoints);
    TSPGenome(const std::vector<int> &order);

    // Destructor
    ~TSPGenome();

    // Mutator Methods
    std::vector<int> getOrder() const;
    void computeCircuitLength(const std::vector<Point> &points);
    double getCircuitLength() const;
    void mutate();
};

TSPGenome crosslink(const TSPGenome &g1, const TSPGenome &g2);
TSPGenome findAShortPath(const std::vector<Point> &points,
                           int populationSize, int numGenerations,
                           int keepPopulation, int numMutations);