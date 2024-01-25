#include <bits/stdc++.h>

using namespace std;

#define INF 1e9;
const int N=105;
const int M = 1005;
const int C=105;
typedef pair<int,int> ii;
int n,m,capacity,a,b,w,strt,finish;

//adjacent list
vector<ii> adj[N];
//cost Array(Dp)
int cost[N][C];
//gasprice
int gasprice[N];


//helpers
void print_adj_list(vector<ii> adj[], int n) {
    cout << "Adjacent list:\n";
    for (int i = 0; i <= n; i++) {
        cout << i << "->";
        for (auto const &p : adj[i]) {
            cout << p.first << "->";
        }
        cout << "\n";
    }
}
void printcostArray(int n, int capacity) {
    cout << "costance Array:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j <= capacity; j++) {
            cout << cost[i][j] << " ";
        }
        cout << "\n";
    }
}

//city
class City{
    public:
    int city_no,gasIntank,total_min_cost;//c->gas_in_tank_left;d->total_costs
    City() {};
    City(int u,int c, int d){
        this->city_no=u;
        this->gasIntank=c;
        this->total_min_cost=d;
    }
    //ol compare operator
    bool operator>(const City &s) const { return total_min_cost > s.total_min_cost; }
};
int state_Djikstra(int strt, int finish)
{
    //populating the Dp with INF
    for(int i =0;i<n;i++){
        for(int j = 0;j<=capacity;j++){
            cost[i][j]=INF;
        }
    }
    //priority queue
    priority_queue<City,vector<City>,greater<City>> pq;
    pq.push(City(strt,0,0));
    while(!pq.empty()){
        City city = pq.top();
        pq.pop();
        if(cost[city.city_no][city.gasIntank]<city.total_min_cost) continue;
        cost[city.city_no][city.gasIntank]=city.total_min_cost;

        for(auto const &p: adj[city.city_no]){
            int u = p.first;
            int w = p.second;
            for(int fillable_gas = capacity-city.gasIntank;fillable_gas>=0 && city.gasIntank+fillable_gas-w>=0;fillable_gas--){
                if(cost[u][city.gasIntank+fillable_gas-w]>city.total_min_cost + fillable_gas*gasprice[city.city_no]){
                    cost[u][city.gasIntank+fillable_gas-w] = city.total_min_cost + fillable_gas*gasprice[city.city_no];
                    pq.push(City(u,city.gasIntank+fillable_gas-w,city.total_min_cost+fillable_gas*gasprice[city.city_no]));
                }
            }
        }
        //printcostArray(n,capacity);
    }
    int minimum_cost = INF;
    for(int i =0;i<=capacity;i++){
        minimum_cost=min(minimum_cost,cost[finish][i]);
    }
    return minimum_cost;
}


int main(){
    cin>>n>>m>>capacity;
    for (int i = 0; i < N; i++) adj[i].clear();
    for(int i =0;i<n;i++){
        cin>>gasprice[i];
    }

    /*for(int i =0;i<n;i++){
        cout<<cost[i];
    }*/
    //cout<<endl;

    for(int i =0;i<n;i++){
        adj[i].clear();
    }
    for(int i=0;i<m;i++){
        cin>>a>>b>>w;a--;b--;
        adj[a].push_back(ii(b,w));
        adj[b].push_back(ii(a,w));
    }
    //print_adj_list(adj,n);
    cin>>strt>>finish;
    cout<<endl;
    int minimum_trvl = state_Djikstra(strt-1,finish-1);
    if(minimum_trvl == 1e9 ){
        cout<<"IMPOSSIBLE";
    }else
    cout<<minimum_trvl;
    return 0;
}
