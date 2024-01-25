#include <bits/stdc++.h>
using namespace std;

const int maximumFlow = 100;
int n,m,source,sink;
char c;
vector<vector<int>> graph;

//printing graph
void printGraph(const vector<vector<int>>& graph) {
    for(const auto& row:graph){
        for(const auto& value:row){
            cout << value << " ";
        }
        cout << "\n";
    }
    cout << "\n";
}

void makeMinCut(const vector<vector<int>>& residualgraph){
    vector<bool> visited(n,false);
    queue<int> q;
    q.push(source);
    visited[source] = true;
    while(!q.empty()){
        int u = q.front();
        q.pop();
        for(int v = 0;v<n;v++){
            if(!visited[v] && residualgraph[u][v]>0){
                q.push(v);
                visited[v] = true;
            }
        }
    }
    cout<<"[ {";
    for(int i =0;i<n;i++){
        if(visited[i]){
            cout<<i+1<<", ";
        }
        
    }
    cout<<"} ";
    cout<<"{";
    for(int i = 0;i<n;i++){
        if(!visited[i]){
            cout<<i+1<<", ";
        } 
        
    }
    cout<<"} ]\n";
}

void nodeWithMaxFlow(const vector<vector<int>>& residualgraph){
    int maxFlow = 0;
    int node = -1;
    for(int i =0 ;i<graph.size();i++){
        if(i == source || i == sink){
            continue;
        }
        int flow=0;
        for(int j = 0;j<graph.size();j++){
            if(graph[i][j]!=0){
                flow += residualgraph[j][i]; 
            }
        }
        if(flow>maxFlow){
            maxFlow = flow;
            node = i;
        }
    }
    cout << node+1 <<" "<<maxFlow<<" "<< "\n";
}

int fordFulkerson(vector<vector<int>>& graph, int source , int sink,char c){
    int numOfVertices = graph.size();
    vector<vector<int>> residualgraph(numOfVertices,vector<int>(numOfVertices,0));
    for(int i=0;i<numOfVertices;i++){
        for(int j=0;j<numOfVertices;j++){
            residualgraph[i][j] = graph[i][j];
        }
    }
    vector<int> parent(numOfVertices,-1);
    int maxFlow = 0;
    while(true){
        vector<bool> visited(numOfVertices,false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v = 0;v<numOfVertices;v++){
                if(!visited[v] && residualgraph[u][v]>0){
                    q.push(v);
                    parent[v] = u;
                    visited[v] = true;
                }
            }
        }
        if(!visited[sink]){
            break;
        }
        //finding the bottleneck capacity
        int pathflow = maximumFlow;
        for(int v = sink;v!=source;v=parent[v]){
            int u = parent[v];
            pathflow = min(pathflow,residualgraph[u][v]);
        }
        for(int v = sink;v!=source;v=parent[v]){
            int u = parent[v];
            residualgraph[u][v] -= pathflow;
            residualgraph[v][u] += pathflow;
        }
        maxFlow += pathflow;
    }
    //printGraph(residualgraph);
    if(c == 'a'){
        nodeWithMaxFlow(residualgraph);
    }
    if(c == 'b'){
        makeMinCut(residualgraph);
        cout << maxFlow << "\n";
    }
    
}
int main(){
    cin >> n>> m;
    graph.resize(n,vector<int>(n,0));
    for(int i=0;i<m;i++){
        int u,v,c;
        cin >> u >> v >> c;
        u--;v--;
        graph[u][v] = c;
    }
    cin >> source >> sink;
    source--;sink--;
    //printGraph(graph);
    cin>>c;
    fordFulkerson(graph,source,sink,c);
    
    return 0;
}