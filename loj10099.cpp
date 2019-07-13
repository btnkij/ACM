/**
* Number:loj10099
* Title:「一本通 3.6 例 2」矿场搭建
* Status:?
* Tag:[]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Edge
{
    int from,to,nxt;
}edges[1010];
int head[510],edge_id;
void addedge(int from,int to)
{
    edges[edge_id]=(Edge){from,to,head[from]};
    head[from]=edge_id++;
}
bool vis[510];
int cnt;
void dfs(int u)
{
    if(vis[u])return;
    vis[u]=true;
    cnt++;
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(!vis[v])dfs(v);
    }
}

int node[2010];
int b[2010],e[2010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,kase=1;
    while(readi(m)!=EOF && m)
    {
        edge_id=0;
        int n=0;
        repne(i,0,m)
        {
            int u,v; readi(u,v);
            b[i]=u, e[i]=v;
            node[n++]=u, node[n++]=v;
        }
        sort(node,node+n);
        n=unique(node,node+n)-node;
        fill_n(head+1,n,-1);
        edge_id=0;
        repne(i,0,m)
        {
            int u=lower_bound(node,node+n,b[i])-node+1;
            int v=lower_bound(node,node+n,e[i])-node+1;
            addedge(u,v); addedge(v,u);
        }
        ull ans=0;
        int maxpart=0;
        rep(i,1,n)
        {
            fill_n(vis+1,n,false);
            vis[i]=true;
            int part=0;
            ull tmp=1;
            rep(j,1,n)
            {
                if(vis[j])continue;
                cnt=0;
                dfs(j);
                part++;
                tmp*=cnt;
            }
            if(part==maxpart)ans+=tmp;
            else if(part>maxpart)
            {
                maxpart=part;
                ans=tmp;
            }
        }
        printf("Case %d: %d %llu\n",kase++,maxpart,ans);
    }
    return 0;
}