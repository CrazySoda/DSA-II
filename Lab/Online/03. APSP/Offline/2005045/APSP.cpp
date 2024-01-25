#include <iostream>
#include <vector>
#include <limits>
using namespace std;
typedef vector<vector<double>> Matrix;
typedef vector<double> Array;

class Graph {
private:
    int numVertices;
    const double INF = numeric_limits<double>::max(); // Infinity
    Matrix W; // Adjacency Matrix

    Matrix extended_shortest_paths(Matrix L, Matrix W) {
        int n = L.size();
        Matrix A(n, Array(n, INF));

        for (int i = 0; i < n; i++) 
            for (int j = 0; j < n; j++) 
                for (int k = 0; k < n; k++) 
                    A[i][j] = min(A[i][j], L[i][k] + W[k][j]);

        return A;
    }
    
    void print(Matrix A){
        cout << "Shortest distance matrix" << endl;
        for (int i = 0; i < A.size(); i++){
            for (int j = 0; j < A.size(); j++){
                if (A[i][j] == INF) cout << "INF ";
                else cout << A[i][j] << ' '; 
            }
            cout << endl;
        }
    }

public:
    Graph(int n) {
        numVertices = n;
        W.resize(n, Array(n, INF));
        for(int i = 0; i < n; i++) W[i][i] = 0;
    }

    void addEdge(int src, int dest, double weight) {
        W[src-1][dest-1] = weight;
    }

    Matrix matrixMultiplication(){
        int n = numVertices;
        Matrix L(W);

        for(int i = 1; i < n - 1; i *= 2) // log V
            L = extended_shortest_paths(L, L); // V^3

        print(L);
        return L;
    }

    Matrix floydWarshall() {
        int n = numVertices;
        Matrix D(W);

        for (int k = 0; k < n; k++)  // V^3
            for (int i = 0; i < n; i++) 
                for (int j = 0; j < n; j++) 
                    D[i][j] = min(D[i][j], D[i][k] + D[k][j]);

        print(D);
        return D;
    }
};
