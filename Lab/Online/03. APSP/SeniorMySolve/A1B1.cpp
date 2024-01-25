#include <bits/stdc++.h>
using namespace std;
const int INF = 1e9;
const int N = 105;
const int M = 1005;
int n, m, s, t, f, k;
int u[M], v[M], w[M];
int dp[N][N];
int previ[N][N];

void floyd()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                dp[i][j] = 0;
            else
                dp[i][j] = INF;
            previ[i][j] = -1;
        }
    }
    for (int i = 0; i <= m; i++)
    {
        dp[u[i]][v[i]] = w[i];
        previ[u[i]][v[i]] = u[i];
        dp[v[i]][u[i]] = w[i];
        previ[v[i]][u[i]] = v[i];
    }
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            for (int k = 0; k < n; k++)
            {
                dp[j][k] = min(dp[j][k], dp[j][i] + dp[i][k]);
            }
        }
    }
}
vector<int> get_path(int s, int t)
{
    vector<int> path;
    int cur = t;
    while (cur != -1)
    {
        path.push_back(cur);
        cur = previ[s][cur];
        if (cur == s)
        {
            path.push_back(cur);
            break;
        }
    }
    reverse(path.begin(), path.end());
    return path;
}

void print_dp()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cout << dp[i][j] << " ";
        }
        cout << endl;
    }
}

int main()
{
    cin >> n >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> u[i] >> v[i] >> w[i];
        u[i]--;
        v[i]--;
    }
    cin >> f >> k;
    f--;
    k--;
    floyd();
    // print_dp();
    do
    {
        cin >> s >> t;
        s--;
        t--;
        int minimumdistancewithedge = min(dp[s][f] + dp[f][k] + dp[k][t], dp[s][k] + dp[k][f] + dp[f][t]);
        if (minimumdistancewithedge >= INF)
            cout << "No path from " << s + 1 << " to " << t + 1 << " through the Wall Street." << endl;
        else
        {
            cout << "Shortest path weight :" << minimumdistancewithedge << endl;
            if (dp[s][f] + dp[f][k] + dp[k][t] < dp[s][k] + dp[k][f] + dp[f][t])
            {
                vector<int> path = get_path(s, f);
                for (const auto &i : path)
                {
                    cout << i + 1 << " "
                         << "->";
                }
                path = get_path(k, t);
                for (const auto &i : path)
                {
                    cout << i + 1 << " "
                         << "->";
                }
                cout << endl;
            }
            else if(dp[s][f] + dp[f][k] + dp[k][t] > dp[s][k] + dp[k][f] + dp[f][t])
            {
                vector<int> path = get_path(s, k);
                for (const auto &i : path)
                {
                    cout << i + 1 << " "
                         << "->";
                }
                path = get_path(f, t);
                for (const auto &i : path)
                {
                    cout << path[i] + 1 << " "
                         << "->";
                }
                cout << endl;
            }
        }
    } while (s != -2 && t != -2);
    return 0;
}