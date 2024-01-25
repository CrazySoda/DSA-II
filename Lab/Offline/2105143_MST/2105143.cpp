#include <bits/stdc++.h>

using namespace std;

class DSU
{
private:
    int *parent;

public:
    DSU(int vertices)
    {
        parent = new int[vertices];
        for (int i = 0; i < vertices; i++)
        {
            parent[i] = i;
        }
    }

    int find(int i)
    {
        if (parent[i] == i)
        {
            return i;
        }
        return parent[i] = find(parent[i]);
    }

    bool isCycle(int u, int v)
    {
        int parent1 = find(u);
        int parent2 = find(v);

        return (parent1 == parent2);
    }

    void unite(int u, int v)
    {
        int parent1 = find(u);
        int parent2 = find(v);
        if (!isCycle(u, v))
        {
            if (parent1 < parent2)
            {
                parent[v] = parent1;
            }
            else if (parent1 > parent2)
            {
                parent[u] = parent2;
            }
        }
    }
};
class Edge
{
public:
    int u, v, w, flag;

    Edge(int u, int v, int w) : u(u), v(v), w(w), flag(0) {}
};
class Graph
{
private:
    vector<Edge> edgelist;
    int vertices;

public:
    Graph(int vertices)
    {
        this->vertices = vertices;
    };

    void addEdge(int u, int v, int w)
    {
        edgelist.push_back(Edge(u, v, w));
    }
    void sortEdges()
    {
        sort(edgelist.begin(), edgelist.end(), [](const Edge &a, const Edge &b)
             { return a.w < b.w; });
    }
    int findMSTWeight()
    {
        int edgesadded = 0;
        DSU s(vertices);
        int MSTw = 0;
        for (auto edge : edgelist)
        {
            int u = edge.u;
            int v = edge.v;
            int w = edge.w;
            if (s.find(u) != s.find(v))
            {
                s.unite(u, v);
                edgesadded++;
                MSTw += w;
            }

            if (edgesadded == vertices - 1)
            {
                break;
            }
        }
        return MSTw;
    }
};

class House
{
public:
    int x;
    int y;

    House(int x, int y)
    {
        this->x = x;
        this->y = y;
    }
};
int main()
{
    int n;
    cout << "Give inputs:" << endl;
    cin >> n;
    // cout<<n<<" "<<m;
    vector<House> houses;
    for (int i = 0; i < n; i++)
    {
        int x, y;
        cin >> x >> y;
        houses.push_back(House(x, y));
    }
    Graph g(n);
    for (size_t i = 0; i < houses.size(); i++)
    {
        for (size_t j = i + 1; j < houses.size(); j++)
        {
            int distance = (abs(houses[i].x - houses[j].x) +(abs(houses[i].y - houses[j].y)));
                              
             
            g.addEdge(i, j, distance); // Use the house indices as vertices

            
        }
    }

    g.sortEdges();
    cout << g.findMSTWeight();

    return 0;
}
