#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int adj[110][110];
int deg[110];
vector<int> cand,cli;
int ans,vis[110];
void dfs(int dep,int pre)
{
    if(dep==0)
    {
        ans++;
        return;
    }
    for(int i=pre+1;i<cand.size();i++)
    {
        int v=cand[i];
        if(vis[v])continue;
        if(!all_of(cli.begin(),cli.end(),[v](int u){return adj[u][v];}))continue;
        vis[v]=true;
        cli.push_back(v);
        dfs(dep-1,i);
        cli.pop_back();
        vis[v]=false;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,m,s; readi(n,m,s);
        clr(adj,0); clr(deg,0);
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            adj[u][v]=adj[v][u]=1;
            deg[u]++, deg[v]++;
        }
        ans=0; clr(vis,0);
        rep(i,1,n)
        {
            vis[i]=true;
            if(deg[i]<s-1)continue;
            cand.clear(); cli.clear();
            cli.push_back(i);
            rep(j,1,n)if(!vis[j] && adj[i][j])cand.push_back(j);
            if(cand.size()<s-1)continue;
            dfs(s-1,-1);
        }
        printf("%d\n",ans);
    }
    return 0;
}