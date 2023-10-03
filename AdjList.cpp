#include "AdjList.h"
#include <iostream>
#include <iomanip>
#include <queue>
using namespace std;

void AdjacencyList::CalcPageRank(int p) {
    // calcs the pageRanks of everything for p iterations; print in a separate function
    for (int i = 0; i < p; i++){
        // matrix multiplication now!
        // get to, from, outdegree from mulitplier, for tracking purposes
        string to = "null";
        string from = "null";
        float outdegree = 0;
        queue<float> newRankStorage;

        for (auto iter = adjMultiplier.begin(); iter != adjMultiplier.end(); ++iter) {
            //in the to "row"
            to = iter->first;
            float newRank = 0;

            for (auto iter2 = iter->second.begin(); iter2 != iter->second.end(); ++iter2){
                // now in the columns
                // multiply all pageranks and outdegrees in the row and sum them
                from = iter2->first;
                outdegree = iter2->second;

                // and multiply the corresponding from with the from website of pageranks
                float pageRankVal = 0.0;
                if (outdegree != 0)
                    pageRankVal = pageRanks[from];

                float product = pageRankVal * outdegree;

                // add this value to a total pagerank
                newRank = newRank + product;

                }
                //add the final sum/newRank to newRankStorage to prevent later iterations from overwriting one another
                newRankStorage.push(newRank);
            }

            // add all pageranks at the same time to prevent collision
            for (auto iter3 = pageRanks.begin(); iter3 != pageRanks.end(); ++iter3) {
                float rankToAdd = newRankStorage.front();
                iter3->second = rankToAdd;
                newRankStorage.pop();

            }
        }
}
void AdjacencyList::CreatePageRank() {
    // total size for default pagerank map: 1/totalwebsites
    float totalWebsites = adjGraph.size();

    // iterate entire thing and place in
    for(auto it = adjGraph.begin(); it != adjGraph.end(); ++it){
        string currentWebsite = it->first;

        //place in 1/totalwebsites
        pageRanks[currentWebsite]= 1/totalWebsites;

    }
}
void AdjacencyList::CreateMultiplierGraph() {
    // adjMultiplier consists of 1/outdegree of from
    // iterate for each to value, then traverse each vector

    for(auto it = adjGraph.begin(); it != adjGraph.end(); ++it){
        //case where nothing points to a website
        if (adjGraph[it->first].size() == 0)
            adjMultiplier[it->first].push_back(make_pair("null",0.0));

        for (int i = 0; i < it->second.size(); i++) {
            //first grab the name of the from value of the
            string from = it->second[i];

            //then grab its corresponding outdegree value
            float fromOutdegree = adjOutdegree[from];

            //then push the fromoutdegree into the multiplier "matrix", remembering to make it 1/outdegree
            float fromOutdegreeFraction = 1/fromOutdegree;

            // creates a matrix of to values that organize what from value is associated (the column)
            // and the outdegree with it
            adjMultiplier[it->first].push_back(make_pair(from,fromOutdegreeFraction));

        }
    }
}
void AdjacencyList::AddEdge(string from, string to){
    // per class powerpoints
    adjGraph[to].push_back(from);
    if (adjGraph.find(from)==adjGraph.end())
        adjGraph[from] = {};

    // adjOutdegree[key = from]: value = outdegree (amount of websites "from" points to)
    adjOutdegree[from]++;

}

void AdjacencyList::PrintPageRank() {
    // use iterator to traverse pageRanks
    for (auto iter = pageRanks.begin(); iter != pageRanks.end(); ++iter) {
        cout << iter->first << " ";

        float pageRank = pageRanks[iter->first];
        cout << fixed;
        cout << setprecision(2)<< pageRank << endl;


    }
}
