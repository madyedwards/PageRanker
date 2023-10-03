#include <iostream>
#include <string>
#include <sstream>
#include "AdjList.h"
using namespace std;

int main() {
    /* input: first line contains the number of lines that will follow
     * and the number of power iterations that need to be performed
     * each line from 2 to n+1 will contain two URLs, from_page and to_page
     * separated by a single space
     * output: print the pagerank of all pages after p powerIterations in
     * ascending alphabetical order of webpage; round off the rank of the
     * page to two decimal places
    */

    // create all graph objects
    AdjacencyList graph;

    //read in 1st number of lines n from cin
    int n;
    cin >> n;

    //now number of power iterations
    int p;
    cin >> p;

    //for n size, read in from and to
    for(int i = 0; i < n; i++) {
        string line;
        getline(cin, line);
        istringstream in(line);

        //read in source vertex
        string from;
        cin >> from;

        //read in destination vertex
        string to;
        cin >> to;

        //ADD VERTICES/EDGE (FROM->TO) TO ADJ LIST HERE
        graph.AddEdge(from, to);


    }
    //create the default pagerank adjlists
    graph.CreateMultiplierGraph();
    graph.CreatePageRank();

    //then call pagerank on everything
    graph.CalcPageRank(p-1);
    graph.PrintPageRank();

    return 0;

}
