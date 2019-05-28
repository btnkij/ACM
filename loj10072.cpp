/**
* Number:loj10072
* Title:「一本通 3.2 例 1」Sightseeing Trip
* Status:AC
* Tag:[floyd]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int adj[110][110];
int dis[110][110], pre[110][110];
vector<int> path;
void getPath(int from, int to)
{
    if(!pre[from][to])return;
    getPath(from, pre[from][to]);
    path.push_back(pre[from][to]);
    getPath(pre[from][to], to);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    rep2(i,1,n,j,1,n)
    {
        if(i!=j)adj[i][j]=INF;
    }
    while(m--)
    {
        int u,v,w; readi(u,v,w);
        adj[u][v]=adj[v][u]=min(adj[u][v], w);
    }
    memcpy(dis, adj, sizeof(adj));
    ll ans=INF;
    rep(k,1,n)
    {
        repne2(i,1,k,j,i+1,k)
        {
            ll tmp=(ll)dis[i][j]+adj[k][i]+adj[j][k];
            if(tmp<ans)
            {
                ans=tmp;
                path.clear();
                path.push_back(i);
                getPath(i,j);
                path.push_back(j);
                path.push_back(k);
            }
        }
        rep(i,1,n)if(i!=k)
        rep(j,1,n)if(j!=k && i!=j)
        {
            ll tmp=(ll)dis[i][k]+dis[k][j];
            if(tmp<dis[i][j])
            {
                dis[i][j]=tmp;
                pre[i][j]=k;
            }
        }
    }
    if(ans==INF)
    {
        printf("No solution.\n");
    }
    else
    {
        for(int i:path)printf("%d ",i);
    }
    return 0;
}