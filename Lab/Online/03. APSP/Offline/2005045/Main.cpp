#include <iostream>
#include <fstream>
#include "APSP.cpp"

using namespace std;

int main() {
    ifstream input("input.txt");
    int n, m;
    input >> n >> m;
    Graph graph(n);

    for (int i = 0; i < m; i++) {
        int src, dest;
        double weight;
        input >> src >> dest >> weight;
        graph.addEdge(src, dest, weight);
    }

    input.close();

    ofstream output("output.txt");
    streambuf* temp = cout.rdbuf();
    cout.rdbuf(output.rdbuf());

    graph.matrixMultiplication();
    // graph.floydWarshall();

    cout.rdbuf(temp);
    return 0;
}