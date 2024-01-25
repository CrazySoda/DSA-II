#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N=105;
const int M = 1005;
typedef pair<string,int> si;
int s1,r1,s2,r2,p1,p2;
string start_c,end_c;
unordered_map<string,vector<si>> state_map_1;
unordered_map<string,vector<si>> state_map_2;
unordered_map<string,int> distance1;
unordered_map<string,int> distance2;
unordered_map<string,string> parent1;
unordered_map<string,string> parent2;
unordered_map<string,int> port1;
unordered_map<string,int> port2;

void dijkstra(string start_c, unordered_map<string,vector<si>>& state_map, unordered_map<string,int>& distance, unordered_map<string,string>& parent){
    // Initialize the distance array with INF values, except for the start state
    for(auto& p : state_map){
        distance[p.first] = INF;
        parent[p.first] = "";
    }
    distance[start_c] = 0;

    // Use a set to store the states with their distances, and extract the minimum distance state in each iteration
    set<si> s;
    s.insert(si(start_c, 0));

    while(!s.empty()){
        // Get the state with the minimum distance
        string u = s.begin()->first;
        s.erase(s.begin());

        // Loop through the adjacent states and update their distances if smaller
        for(auto& p : state_map[u]){
            string v = p.first;
            int w = p.second;
            if(distance[v] > distance[u] + w){
                // Remove the old distance if present
                if(distance[v] != INF){
                    s.erase(s.find(si(v, distance[v])));
                }
                // Update the new distance and parent
                distance[v] = distance[u] + w;
                parent[v] = u;
                // Insert the new distance
                s.insert(si(v, distance[v]));
            }
        }
    }
}

int main(){
    cin>>s1>>r1>>s2>>r2;
    for(int i=0;i<r1;i++){
        string a,b;
        int c;
        cin>>a>>b>>c;
        state_map_1[a].push_back(si(b,c));
        state_map_1[b].push_back(si(a,c));
    }
    for(int i=0;i<r2;i++){
        string a,b;
        int c;
        cin>>a>>b>>c;
        state_map_2[a].push_back(si(b,c));
        state_map_2[b].push_back(si(a,c));
    }
    cin>>p1;
    for(int i=0;i<p1;i++){
        string a;
        int b;
        cin>>a>>b;
        port1[a]=b;
    }
    cin>>p2;
    for(int i=0;i<p2;i++){
        string a;
        int b;
        cin>>a>>b;
        port2[a]=b;
    }
    cin>>start_c>>end_c;

    // Run the dijkstra function for both maps
    dijkstra(start_c, state_map_1, distance1, parent1);
    dijkstra(end_c, state_map_2, distance2, parent2);

    // Find the minimum cost and the cheapest route
    int min_cost = INF;
    string min_port = "";
    string route = "";

    // Loop through the port states and compare the distances
    for(auto& p : port1){
        string u = p.first;
        int t1 = p.second;
        if(port2.count(u) > 0){
            int t2 = port2[u];
            int cost = distance1[u] + t1 + t2 + distance2[u];
            if(cost < min_cost){
                min_cost = cost;
                min_port = u;
            }
        }
    }

    // Check if there is a valid route
    if(min_cost == INF){
        cout << "There is no path from " << start_c << " to " << end_c << endl;
    }
    else{
        // Print the minimum cost
        cout << "The minimum cost required to visit Farhan is " << min_cost << endl;

        // Reconstruct the route by following the parent states
        route = min_port;
        string u = min_port;
        while(parent1[u] != ""){
            u = parent1[u];
            route = u + " -> " + route;
        }
        u = min_port;
        while(parent2[u] != ""){
            u = parent2[u];
            route = route + " -> " + u;
        }

        // Print the cheapest route
        cout << "The cheapest route is " << route << endl;
    }

    return 0;
}
