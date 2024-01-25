#include <bits/stdc++.h>

using namespace std;

const int INF = 1e9;
const int N = 105;
const int M = 1005;

int n,m,a,b,l,h,s,d,min_dist=999999,opt=-1000,min_dist2;
int u[M],v[M],w[M],dist[N];

void copyArray(int array1[],int array2[],int size){
    for(int i = 1; i<size+1;i++){
        array2[i]=array1[i];
    }
}
int min(int a,int b){
    if(a<b){
        return a;
    }
    else return b;
}
void printArray(const int arr[], int size) {
    for (int i = 0; i < size; ++i) {
        std::cout << arr[i] << " ";
    }
    std::cout << std::endl;
}

void bellman_ford(){
    for(int i= 1;i<=n;i++){
        dist[i]=INF;
    }
    dist[s]=0;
    for(int i=l-1;i<h+1;i++){
        int temp_dist[n];
        copyArray(dist,temp_dist,n);
        bool negative_cycle = false;
        for(int j=0;j<n;j++){
            for(int k=0;k<m;k++){
                int city1=u[k];
                int city2=v[k];
                int weight = w[k];
                if(j<n-1 && temp_dist[city1]<INF){
                    temp_dist[city2]=min(temp_dist[city2],temp_dist[city1]+weight);
                }else if(j==(n-1) && temp_dist[city1]<INF && temp_dist[city2]>temp_dist[city1]+weight){
                    negative_cycle = true;
                    break;
                }
            }
            if(i != l-1){
            temp_dist[b] = min(temp_dist[b],temp_dist[a]+i);
            }
        }
        if(temp_dist[b]>temp_dist[a]+i && i != l-1){
            negative_cycle = true;
        }
        if (negative_cycle == false){
            if (temp_dist[d] < min_dist ){
                if(i >l-1){
                min_dist = temp_dist[d];
                opt = i;
                }else
                min_dist2 = temp_dist[d];
            }
        }
        
    }
    if(opt == -1000 || min_dist2<=min_dist){
        cout<<"IMPOSSIBLE";
    }else{
        cout<<opt<<" "<<min_dist;
    }
    
}

int main(){
    cin>>n>>m;
    for(int i=0;i<m;i++){
        cin >> u[i] >> v[i] >> w[i];
    }
    cin>>a>>b;
    cin>>l>>h;
    cin>>s>>d;
    bellman_ford();
    return 0;
}