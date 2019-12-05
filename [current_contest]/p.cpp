/**
* Number:
* Title:
* Status:?
* Tag:[]
**/

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

bool adj[20][20];
bool vis[20*(1<<16)];
int pre[20*(1<<16)],dis[20*(1<<16)];
void bfs(int s,int t)
{
    clr(vis,false);
    queue<int> Q; Q.push(s);
    while(!Q.empty())
    {
        int sta=Q.front(); Q.pop();
        int u=sta>>15,obs=sta&0x7FFF;
        
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
        int n,m,s,t; readi(n,m,s,t);
        s--,t--;
        s<<=15;
        repne(i,0,m)
        {
            int x; readi(x);
            s|=1<<(x-1);
        }
        clr(adj,false);
        repne(i,1,n)
        {
            int u,v; readi(u,v);
            u--,v--;
            adj[u][v]=adj[v][u]=true;
        }
    }
    return 0;
}