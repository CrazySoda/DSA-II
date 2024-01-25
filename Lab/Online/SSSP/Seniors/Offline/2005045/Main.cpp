#include <iostream>
#include <fstream>
#include "SSSP.cpp"

using namespace std;

int main() {
    ifstream input("input.txt");

    int numVertices, numEdges;
    input >> numVertices >> numEdges;

    Graph graph(numVertices);

    for (int i = 0; i < numEdges; i++) {
        int src, dest;
        double weight;
        input >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    int source, destination;
    input >> source >> destination;

    input.close();

    ofstream output("output.txt");
    streambuf* temp = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    graph.bellmanFord(source, destination);
    graph.dijkstra(source, destination);

    cout.rdbuf(temp);

    return 0;
}