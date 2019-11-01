/**
* Number:uva1201
* Title:Taxi Cab Scheme
* Status:AC
* Tag:[二分图, hungary, 最小路径覆盖]
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

struct Edge
{
    int from,to,nxt;
}edges[510*510];
int head[510],edgeid;
void addedge(int from,int to)
{
    edges[edgeid]=(Edge){from,to,head[from]};
    head[from]=edgeid++;
}

int match[510*2];
bool vis[510*2];
int dfs(int u)
{
    for(int i=head[u];~i;i=edges[i].nxt)
    {
        int v=edges[i].to;
        if(vis[v])continue;
        vis[v]=true;
        if(!match[v] || dfs(match[v]))
        {
            match[v]=u;
            return 1;
        }
    }
    return 0;
}

struct Node
{
    int t,x1,y1,x2,y2;
}nodes[510];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        rep(i,1,n)
        {
            char t[8];
            Node& nod=nodes[i];
            scanf("%s %d %d %d %d",t,&nod.x1,&nod.y1,&nod.x2,&nod.y2);
            nod.t=((t[0]&0xF)*10+(t[1]&0xF))*60+(t[3]&0xF)*10+(t[4]&0xF);
        }
        clr(head,-1); edgeid=0;
        rep2(i,1,n,j,i+1,n)
        {
            Node &u=nodes[i],&v=nodes[j];
            if(u.t+abs(u.x2-u.x1)+abs(u.y2-u.y1)+abs(v.x1-u.x2)+abs(v.y1-u.y2)<v.t)
            {
                addedge(i,n+j);
            }
        }
        int maxmatch=0;
        clr(match,0);
        rep(i,1,n)
        {
            clr(vis,false);
            maxmatch+=dfs(i);
        }
        printf("%d\n",n-maxmatch);
    }
    return 0;
}