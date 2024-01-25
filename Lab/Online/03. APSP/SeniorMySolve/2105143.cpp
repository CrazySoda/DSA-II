#include <bits/stdc++.h>

using namespace std;
const int N = 105;
const int INF = 1e9;
int n, m, u, v, w, q;
int r[N];
int dp[N][N];

void floyd_warshall()
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            else
            {
                for (int k = j + 1; k < n; k++)
                {
                    if (k == i)
                    {
                        continue;
                    }
                    else if (j > i)
                    {
                        dp[j][k] = min(dp[j][k], (dp[i][j] + dp[i][k]));
                    }
                    else if (k < i)
                    {
                        dp[j][k] = min(dp[j][k],(dp[j][i]+dp[k][i]));
                    }
                    else
                    {
                        dp[j][k] = min(dp[j][k], (dp[j][i] + dp[i][k]));
                    }
                }
            }
        }
    }
}
void req_cities(int q)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                continue;
            }
            else if (j > i)
            {
                if (dp[i][j] <= q)
                {
                    r[i]++;
                }
            }
            else
            {
                if (dp[j][i] <= q)
                {
                    r[i]++;
                }
            }
        }
    }
    int m_in = r[0];
    for (int i = 1; i < n; i++)
    {
        if (r[i] < m_in)
        {
            m_in = r[i];
        }
        else
            continue;
    }
    for (int i = 0; i < n; i++)
    {
        if (r[i] == m_in)
        {
            cout << i + 1 << " ";
        }
    }
    cout << endl;
    // cout<<m_in;
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
    cin >> n;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
            {
                dp[i][j] = 0;
            }
            else
            {
                dp[i][j] = INF;
            }
        }
    }
    cin >> m;
    for (int i = 0; i < m; i++)
    {
        cin >> u >> v >> w;
        u--;
        v--;
        int sum = u + v;
        int minimum = min(u, v);
        dp[minimum][sum - minimum] = w;
    }
    cin >> q;
    floyd_warshall();
    req_cities(q);
    //print_dp();

    return 0;
}