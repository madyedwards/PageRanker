#include <iostream>
#include <vector>
#include <map>
using namespace std;

class AdjacencyList{
private:
    //representation of AdjList (ordered or unordered map, type thing)
    map<string , vector<string>> adjGraph;
    map<string, float> adjOutdegree;
    map<string, vector<pair< string, float>>> adjMultiplier;
    map<string, float> pageRanks;

public:
    // graph creation
    void AddEdge(string from, string to);
    void CreateMultiplierGraph();
    void CreatePageRank();
    // page rank formulas
    void CalcPageRank(int p);
    // printing
    void PrintPageRank();


};

