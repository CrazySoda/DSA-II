#include <bits/stdc++.h>
using namespace std;
int n,m,size;
int height,age,isDvorced;

vector<vector<int>> graph;
vector<tuple<int,int,int>> person;
//helper function
void printPerson(const vector<tuple<int,int,int>>& person){
    for(const auto& row:person){
        cout << get<0>(row) << " " << get<1>(row) << " " << get<2>(row) << "\n";
    }
    cout << "\n";
}
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
int fordFulkerson(const vector<vector<int>>& graph,int source,int sink){
    int numOfvertices = graph.size();
    vector<vector<int>> residualgraph(numOfvertices,vector<int>(numOfvertices,0));
    for(int i = 0;i<numOfvertices;i++){
        for(int j = 0;j<numOfvertices;j++){
            residualgraph[i][j] = graph[i][j];
        }
    }
    vector<int> parent(numOfvertices,-1);
    int maxflow = 0;
    while(true){
        vector<bool> visited(numOfvertices,false);
        queue<int> q;
        q.push(source);
        visited[source] = true;
        parent[source] = -1;
        while(!q.empty()){
            int u = q.front();
            q.pop();
            for(int v = 0;v<numOfvertices;v++){
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
        int pathflow = INT_MAX;
        for(int v = sink;v!=source;v=parent[v]){
            int u = parent[v];
            pathflow = min(pathflow,residualgraph[u][v]);
        }
        for(int v = sink;v!=source;v=parent[v]){
            int u = parent[v];
            residualgraph[u][v] -= pathflow;
            residualgraph[v][u] += pathflow;
        }
        maxflow += pathflow;
    }
    printGraph(residualgraph);
    return maxflow;
}
int main(){
    cin >> n >> m;
    int size = n+m+2;
    graph.resize(size,vector<int>(size,0));
    for(int i =0; i<size-2;i++){
        cin>>height>>age>>isDvorced;
        person.push_back(make_tuple(height,age,isDvorced));
    }
    //printPerson(person);
    //populate the graph
    for(int i =0;i<size;i++){
        for(int j =0;j<size;j++){
            if(i == 0){
                if(j>=1 && j<=n){
                    graph[i][j] = 1;
                }
            }
            if(i == size-1){
            }
            if(i>0 && i<=n){
                int heightOfMale = get<0>(person[i-1]);
                int ageOfMale = get<1>(person[i-1]);
                int isDvorcedOfMale = get<2>(person[i-1]);
                if(j>n && j<size-1){
                    int heightOfFemale = get<0>(person[j-1]);
                    int ageOfFemale = get<1>(person[j-1]);
                    int isDvorcedOfFemale = get<2>(person[j-1]);
                    if(abs(heightOfFemale-heightOfMale)<=10 && abs(heightOfMale-heightOfFemale)<=10 && abs(ageOfFemale-ageOfMale)<=5 && abs(ageOfMale-ageOfFemale)<=5 && isDvorcedOfFemale == isDvorcedOfMale)
                    graph[i][j] = 1;
                }
            }
            if(i>n && i<size-1){
                if(j == size-1){
                    graph[i][j] = 1;
                }
            }
        }
    }
    //printGraph(graph);
    cout<<fordFulkerson(graph,0,size-1)<<"\n";
    return 0;
}