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
    vector<Edge> getEdgesWithWeight(int weight)
    {
        vector<Edge> result;
        for (const auto &edge : edgelist)
        {
            if (edge.w == weight)
            {
                result.push_back(edge);
            }
        }
        return result;
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
                // cout<<MSTw<<endl;
            }

            if (edgesadded == vertices - 1)
            {
                break;
            }
        }
        return MSTw;
    }

    void printEdges()
    {
        cout << "\nEdges:" << endl;
        cout << setw(5) << "U" << setw(5) << "V" << setw(5) << "Weight" << setw(5) << "Flag" << endl;
        for (const auto &edge : edgelist)
        {
            cout << setw(5) << edge.u << setw(5) << edge.v << setw(7) << edge.w << setw(5) << edge.flag << endl;
        }
    }

    // we know the number of MST edges will be vertices - 1
    // the weight of all the MSTs will be same
    void customKruskal()
    {
        sortEdges();
        int count = 0;
        DSU s(vertices);
        int MSTw = findMSTWeight();
        // cout<<MSTw;
        int MSTCombWeight = 0;
        for (auto &edge : edgelist)
        {
            if (edge.w > findMSTWeight())
            {
                edge.flag = -1;
            }
        }
        // iterating to change loop
        for (size_t i = 0; i < edgelist.size(); ++i)
        {
            // before uniting
            if (edgelist[i].flag == 0 && MSTCombWeight <= MSTw)
            {
                //  check if cycle
                if (s.isCycle(edgelist[i].u, edgelist[i].v))
                {
                    edgelist[i].flag = -1;
                    // cout<<"1"<<endl;
                }
                // not cycle
                else
                {
                    // before uniting
                    //  check if all the next edges of the same weight form cycles and flag them as -1
                    for (size_t j = i + 1; j < edgelist.size(); ++j)
                    {
                        if (edgelist[j].w == edgelist[i].w && s.isCycle(edgelist[j].v, edgelist[j].u))
                        {
                            edgelist[j].flag = -1;
                        }
                    }
                    // after uniting
                    s.unite(edgelist[i].u, edgelist[i].v);
                    if (edgelist[i].w + MSTCombWeight == MSTw || MSTCombWeight == MSTw)
                    {
                        size_t j;
                        for (j = i + 1; j < edgelist.size() && edgelist[j].w == edgelist[i].w; ++j)
                        {
                            if (!s.isCycle(edgelist[j].u, edgelist[j].v))
                                edgelist[j].flag = 1;
                            count++;
                        }
                        MSTCombWeight += edgelist[i].w;
                        // cout<<MSTCombWeight<<endl;
                    }
                    //  check if the same-weight edges that are not flagged -1 form a cycle
                    bool formingCycle = false;
                    for (size_t j = i + 1; j < edgelist.size(); ++j)
                    {
                        if (edgelist[j].w == edgelist[i].w && edgelist[j].flag != -1 && s.isCycle(edgelist[j].v, edgelist[j].u))
                        {
                            formingCycle = true;
                            edgelist[j].flag = 1; // flag the cycling edge as 1
                        }
                        // cout<<formingCycle;
                    }

                    if (formingCycle)
                    {
                        edgelist[i].flag = 1;
                        MSTCombWeight += edgelist[i].w;
                    }
                    else
                    {
                        edgelist[i].flag = 2;
                        MSTCombWeight += edgelist[i].w;
                    }
                    i += count;
                }
            }
            else if (MSTCombWeight > MSTw)
            {
                edgelist[i].flag = -1;
                // cout<<"2"<<endl;
            }
            else
            {
                continue;
            }
            // printEdges();
        }
    }

    void printFlagEdges()
    {
        queue<Edge> flag1_edges;

        for (const auto &edge : edgelist)
        {
            if (edge.flag == 1)
            {
                flag1_edges.push(edge);
            }
        }

        int mst_number = 1; // Initialize MST number
        cout << "MSTs:" << endl;
        while (!flag1_edges.empty())
        {
            cout << mst_number++ << " : [";

            // Print all edges with flag = 2
            bool flag2_printed = false;
            for (const auto &edge : edgelist)
            {
                if (edge.flag == 2)
                {
                    cout << "[" << edge.u << ", " << edge.v << ", " << edge.w << "], ";
                    flag2_printed = true;
                }
            }

            // Check if there are edges with flag = 1 in the queue
            if (!flag1_edges.empty())
            {
                // Dequeue an edge with flag = 1 and print it
                Edge flag1_edge = flag1_edges.front();
                flag1_edges.pop();
                cout << "[" << flag1_edge.u << ", " << flag1_edge.v << ", " << flag1_edge.w << "]";
            }

            if (flag2_printed)
            {
                cout << "]";
            }

            cout << endl;
        }
    }
};

int main()
{
    int n, m; // vertices,edges
    cout << "Give inputs:" << endl;
    cin >> n >> m;
    // cout<<n<<" "<<m;
    Graph g(n);
    for (int i = 0; i < m; i++)
    {
        int u, v, w;
        // cout<<"give values of the edges"<<endl;
        cin >> u >> v >> w;
        g.addEdge(u, v, w);
    }
    // cout << g.findMSTWeight();
    // int MSTW = g.findMSTWeight();

    g.customKruskal();
    g.printEdges();
    //g.printFlagEdges();
    return 0;
}
// edges:
//  all-MST=2
//  anyone=1
//  unprocessed=0
//  None=-1