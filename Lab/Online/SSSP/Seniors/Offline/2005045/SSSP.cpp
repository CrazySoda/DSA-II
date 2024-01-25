#include <bits/stdc++.h>

using namespace std;

class Graph {
private:
    int numVertices;
    list<pair<double,int>>* adjacencyList;
    vector<pair<int,int>> edges;

public:
    Graph(int n) {
        numVertices = n;
        adjacencyList = new list<pair<double, int>>[n];
    }

    void addEdge(int src, int dest, double weight) {
        adjacencyList[src].push_back(make_pair(weight, dest));
        edges.push_back(make_pair(src, dest));
    }

    void bellmanFord(int source, int destination) {
        vector<double> distance(numVertices, numeric_limits<double>::max());
        vector<int> parent(numVertices, -1);

        distance[source] = 0;

        // Relax all edges numVertices - 1 times
        for (int i = 1; i < numVertices; i++) {
            for (int j = 0; j < numVertices; j++) {
                list<pair<double,int>> :: iterator v;
                for (v = adjacencyList[j].begin(); v != adjacencyList[j].end(); v++) {
                    double weight = v->first;
                    int dest = v->second;
                    if (distance[j] + weight < distance[dest]) {
                        distance[dest] = distance[j] + weight;
                        parent[dest] = j;
                    }
                }
            }
        }

        // Check for negative weight cycles
        for (int i = 0; i < numVertices; i++) {
            list<pair<double,int>> :: iterator v;
            for (v = adjacencyList[i].begin(); v != adjacencyList[i].end(); v++) {
                double weight = v->first;
                int dest = v->second;
                if (distance[i] + weight < distance[dest]) {
                    cout << "Bellman Ford Algorithm:\n";
                    cout << "Negative weight cycle present\n";
                    return;
                }
            }
        }

        // Print shortest distance and path
        cout << "Bellman Ford Algorithm:\n";
        cout << distance[destination] << endl;
        printPath(parent, destination);
        cout << endl << endl;
    }

    void dijkstra(int source, int destination) {
        vector<double> distance(numVertices, numeric_limits<double>::max());
        vector<int> parent(numVertices, -1);
        vector<bool> visited(numVertices, false);

        distance[source] = 0.0;

        priority_queue<pair<double, int>, vector<pair<double, int>>, greater<pair<double, int>>> pq;
        pq.push({0.0, source});

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            visited[u] = true;

            for (const auto& edge : adjacencyList[u]) {
                int v = edge.second;
                double weight = abs(edge.first);

                if (!visited[v] && distance[u] + weight < distance[v]) {
                    distance[v] = distance[u] + weight;
                    parent[v] = u;
                    pq.push({distance[v], v});
                }
            }
        }

        // Print shortest distance and path
        cout << "Dijkstra Algorithm:\n";
        cout << distance[destination] << endl;
        printPath(parent, destination);
    }

private:
    void printPath(const vector<int>& parent, int destination) {
        if (parent[destination] == -1) {
            cout << destination;
            return;
        }

        printPath(parent, parent[destination]);
        cout << " -> " << destination;
    }
};

