#include <bits/stdc++.h>
using namespace std;
const int N = 105;
const int M = 1005;
const int INF = 1e9;
int n,m,u,v,w;
int tax[N];
int dist[N];
typedef pair<int, int> ii;
vector<ii> adj[N];
int dijkstra(){
    for(int i =0;i<n;i++){
        dist[i] = INF;
    }
    priority_queue<ii, vector<ii>, greater<ii>> pq;
    pq.push(ii(0,0));
    dist[0]=0;
    while(!pq.empty()){
        ii front = pq.top();
        pq.pop();
        int d = front.first;
        int u = front.second;
        if(d>dist[u]) continue;
        for(int j =0;j<adj[u].size();j++){
            ii v = adj[u][j];
            int tax = v.second;
            int city = v.first;
            if(dist[u]+tax<dist[city]){
                dist[city] = dist[u] + tax;
                pq.push(ii(dist[city],city));
            }
        }
    }
    return dist[n-1];
}
int main(){
    cin>>n>>m;
    for(int i =0;i<n;i++){
        cin>>tax[i];
    }
    for(int i =0;i<n;i++){
        adj[i].clear();
    }
    for(int i =0;i<n;i++){
        cout<<tax[i]<<" ";
    }
    for(int i=0;i<m;i++){
        cin>>u>>v;
        u--;v--;
        adj[u].push_back(ii(v,tax[v]));
        adj[v].push_back(ii(u,tax[u]));
    }
    cout<<dijkstra();
    return 0;
}