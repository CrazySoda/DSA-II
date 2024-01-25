#include <iostream>
#include <algorithm>

using namespace std;

struct Edge {
    int u, v, weight;

    Edge() {}

    Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}

    bool operator<(const Edge& other) const {
        return weight < other.weight;
    }
};

const int MAX_N = 1000;  // Adjust the maximum number of vertices as needed
const int MAX_MST_EDGES = 2 * MAX_N - 1;  // Maximum number of edges in a tree is n-1

int parent[MAX_N];
int depth[MAX_N];

int find(int x) {
    if (parent[x] != x)
        parent[x] = find(parent[x]);
    return parent[x];
}

void unite(int x, int y) {
    int rootX = find(x);
    int rootY = find(y);

    if (rootX != rootY) {
        if (depth[rootX] < depth[rootY])
            swap(rootX, rootY);
        parent[rootY] = rootX;
        if (depth[rootX] == depth[rootY])
            depth[rootX]++;
    }
}

void kruskals(Edge edges[], int m, int n, int msts[MAX_MST_EDGES][3], int& numMSTs) {
    sort(edges, edges + m);

    for (int i = 0; i < n; ++i) {
        parent[i] = i;
        depth[i] = 0;
    }

    numMSTs = 0;

    for (int i = 0; i < m; ++i) {
        int u = edges[i].u;
        int v = edges[i].v;
        int weight = edges[i].weight;

        int rootU = find(u);
        int rootV = find(v);

        if (rootU != rootV) {
            msts[numMSTs][0] = u + 1;
            msts[numMSTs][1] = v + 1;
            msts[numMSTs][2] = weight;
            numMSTs++;

            unite(rootU, rootV);
        }
    }
}

int main() {
    int n, m;
    cin >> n >> m;

    Edge edges[MAX_N];
    for (int i = 0; i < m; ++i) {
        int u, v, w;
        cin >> u >> v >> w;
        edges[i] = Edge(u - 1, v - 1, w);
    }

    int msts[MAX_MST_EDGES][3];
    int numMSTs;

    kruskals(edges, m, n, msts, numMSTs);

    cout << "MSTs:" << endl;
    for (int i = 0; i < numMSTs; ++i) {
        cout << i + 1 << " : [";
        for (int j = 0; j < 3; ++j) {
            cout << msts[i][j];
            if (j < 2) {
                cout << ", ";
            }
        }
        cout << "]" << endl;
    }

    return 0;
}
