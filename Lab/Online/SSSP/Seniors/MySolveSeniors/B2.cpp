#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 105;
const int M = 1005;

typedef pair<int, int> ii;
int n, m, dest;

string a, begn, destn;
string state[N];
int u[M], v[M], w[M];
int layover[N];

// cost
int dist[N];
int parent[N];

// adjacency list
vector<ii> adj[N];

unordered_map<string, int> state_map;

// dijkstra
void dijkstra(int beg)
{
    for (int i = 0; i < n; i++)
    {
        dist[i] = INF;
        parent[i] = -1;
    }
    dist[beg] = 0;
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0, beg));
    while (!pq.empty())
    {
        ii front = pq.top();
        int cost = front.first;
        int city = front.second;
        pq.pop();
        if (cost > dist[city])
            continue;
        for (const auto &v : adj[city])
        {
            int city1 = v.first;
            int cost1 = v.second;
            if (dist[city] + cost1 < dist[city1])
            {
                dist[city1] = dist[city] + cost1;
                parent[city1] = city;
                pq.push(ii(dist[v.first], v.first));
            }
        }
    }
    cout << dist[dest] << endl;
    if (dist[dest] == INF)
    {
        cout << "No route" << endl;
        return;
    }
    vector<int> path;
    int cur = dest;
    while (cur != -1)
    {
        path.push_back(cur);
        cur = parent[cur];
    }
    reverse(path.begin(), path.end());
    for (int i = 0; i < path.size(); i++)
    {
        if (i == path.size() - 1)
        {
            cout << state[path[i]] << endl;
            break;
        }
        cout << state[path[i]] << "->";
    }
    cout << endl;
    return;
}


int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        cin >> a;
        state[i] = a;
        cin >> layover[i];
        state_map[a] = i;
    }

    for (int i = 0; i < m; i++)
    {
        cin >> a;
        u[i] = {state_map[a]};
        cin >> a;
        v[i] = {state_map[a]};
        cin >> w[i];
        adj[u[i]].push_back(ii(v[i], w[i] + layover[u[i]]));
        adj[v[i]].push_back(ii(u[i], w[i] + layover[v[i]]));
    }
    cin >> begn >> destn;
    int beg = state_map[begn];
    dest = state_map[destn];
    dijkstra(beg);
    return 0;
}