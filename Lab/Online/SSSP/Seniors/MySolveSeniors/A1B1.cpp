#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
typedef pair<int, int> ii;
const int N = 105;
const int M = 1005;
int n, m, x, y, z, f;
int u[M], v[M], t[M];
vector<ii> adj_list[N];
// going distance and paths
int going[N];
int parents[N];
//coming
int coming_final[N];
vector<int> coming[N];//paths
//coming+going
int final_cost[N];
// helper
void copyArray(int array1[], int array2[], int size)
{
    for (int i = 1; i < size + 1; i++)
    {
        array2[i] = array1[i];
    }
}
void print_path(int i, int s)
{
    if (i == s)
    {
        cout << i;
        return;
    }
    if (parents[i] == -1)
    {
        cout << "No path";
        return;
    }
    print_path(parents[i], s);
    cout << "-> " << i;
}
void store_path(int arr[],int i, int s,int starting)
{
    if (i == s)
    {
        coming[starting].push_back(i);
        return;
    }
    if (arr[i] == -1)
    {
        //cout << "No path";
        return;
    }
    store_path(arr,arr[i], s,starting);
    coming[starting].push_back(i);
}
void print_arr(int arr[], int n)
{
    for (int i = 0; i < n; i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

void print_adj_list(vector<ii> adj[], int n)
{
    cout << "Adjacent list:\n";
    for (int i = 0; i < n; i++)
    {
        cout << i << "->";
        for (auto const &p : adj[i])
        {
            cout << p.first << "->";
        }
        cout << "\n";
    }
}
//here redundant
void bellman_ford(int f)
{
    for (int i = 0; i < n; i++)
    {
        going[i] = INF;
        parents[i] = -1;
    }
    print_arr(parents,n);
    going[f] = 0;
    bool is_neg_cycle = false;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            int city1 = u[j];
            int city2 = v[j];
            int weight = t[j];
            if (i < n - 1 && going[city1] < INF)
            {
                going[city2] = min(going[city2], going[city1] + weight);
                if(min(going[city2], going[city1] + weight)==going[city1] + weight){
                    parents[city2]=city1;
                }
                
            }
            else if (i == (n - 1) && going[city1] < INF && city2 > city1 + weight)
            {
                is_neg_cycle = true;
                cout << "IMPOSSIBLE" << endl;
                break;
            }
        }
    }
    
}
void dijkstra(int strt, int f)
{
    int coming_temp[N];
    int coming_parents[N];
    for(int i=0;i<n;i++){
        coming_temp[i]=INF;
        coming_parents[i]=-1;
    }
    coming_temp[strt]=0;
    priority_queue<ii,vector<ii>,greater<ii>> pq;
    pq.push(ii(0,strt));
    while(!pq.empty()){
        ii front = pq.top();
        pq.pop();
        int city = front.second;
        int dist = front.first;
        if(coming_temp[city]<dist)continue;
        for(auto const &p:adj_list[city]){
            int city2 = p.first;
            int dist2 = p.second;
            if(coming_temp[city]+dist2<coming_temp[city2]){
                coming_temp[city2]=coming_temp[city]+dist2;
                coming_parents[city2]=city;
                pq.push(ii(coming_temp[city2],city2));
            }
        }

    }
    coming_final[strt]=coming_temp[f];
    
    store_path(coming_parents,f,strt,strt);
}
void generate_final(){
    
    for(int i =0;i<n;i++){
        int z = coming_final[i];
        int y = going[i];
        final_cost[i]=z+y;
    }
}
int main()
{
    cin >> n >> m;
    for (int i = 0; i < n; i++)
    {
        adj_list[i].clear();
    }
    for (int i = 0; i < m; i++)
    {
        cin >> x >> y >> z;
        u[i] = x;
        v[i] = y;
        t[i] = z;
        adj_list[x].push_back(ii(y, z));
    }

    cin >> f;
    bellman_ford(f);
    for(int i =0;i<n;i++){
        dijkstra(i,f);
    }
    generate_final();
    int minimum_travel = INF;
    int req_city = -1;
    for(int i =0;i<n;i++){
        if(i==f)continue;
        minimum_travel=min(minimum_travel,final_cost[i]);
        if(minimum_travel==final_cost[i]){
            req_city=i;
        }
    }
    cout<<"Minimum travel cost: "<<minimum_travel<<endl;
    cout<<"Path Going: ";
    print_path(req_city,f);
    cout<<"path Coming: ";
    for(auto const &p:coming[req_city]){
        cout<<p<<"->";
    }
    cout<<endl;
    return 0;
}