/**
* Number:uva1324
* Title:Bring Them There
* Status:AC
* Tag:[网络流, 最大流]
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

const int MAXN=100*200;
const int MAXM=1000*200;

struct Edge
{
    int from,to,flow,nxt;
}edges[MAXM];
int head[MAXN],edgeid;
void addedge(int from,int to,int flow)
{
    edges[edgeid]=(Edge){from,to,flow,head[from]};
    head[from]=edgeid++;
}

int src,dst;
int dep[MAXN],cur[MAXN];
void addflow(int from,int to,int flow)
{
    addedge(from,to,flow);
    addedge(to,from,0);
}
bool getdep()
{
    clr(dep,0); dep[src]=1;
    queue<int> Q; Q.push(src);
    while(!Q.empty())
    {
        int u=Q.front(); Q.pop();
        for(int i=head[u];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(e.flow==0 || dep[e.to])continue;
            dep[e.to]=dep[u]+1;
            Q.push(e.to);
        }
    }
    return dep[dst]>0;
}
int augment(int u,int flow)
{
    if(u==dst)return flow;
    for(int& i=cur[u];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        if(e.flow==0 || dep[u]+1!=dep[e.to])continue;
        int f=augment(e.to,min(flow,e.flow));
        if(f)
        {
            e.flow-=f, edges[i^1].flow+=f;
            return f;
        }
    }
    return 0;
}
int dinic()
{
    int maxflow=0,f;
    while(getdep())
    {
        memcpy(cur,head,sizeof(head));
        while(f=augment(src,INF))maxflow+=f;
    }
    return maxflow;
}

int link[MAXN][2],id[MAXM];
bool vis[55];
int pos[55];
vector<pair<int,int> > flight;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,k,s,t;
    while(scanf("%d %d %d %d %d",&n,&m,&k,&s,&t)!=EOF)
    {
        s--, t--;
        repne(i,0,m)
        {
            readi(link[i][0],link[i][1]);
            link[i][0]--, link[i][1]--;
        }
        int day=0,maxflow=0;
        src=MAXN-1;
        clr(head,-1); edgeid=0;
        addflow(src,s,k);
        while(maxflow<k)
        {
            day++;
            int pre=(day-1)*n, now=day*n;
            repne(i,0,n)addflow(pre+i,now+i,INF);
            repne(i,0,m)
            {
                id[day*m+i]=edgeid;
                addflow(pre+link[i][0],now+link[i][1],1);
                addflow(pre+link[i][1],now+link[i][0],1);
            }
            dst=now+t;
            maxflow+=dinic();
        }
        printf("%d\n",day);
        fill_n(pos,k+1,s);
        rep(d,1,day)
        {
            flight.clear();
            repne(i,0,m)
            {
                int e=id[d*m+i];
                int f1=edges[e].flow, f2=edges[e+2].flow;
                // printf("# %d %d %d %d\n",d,i,f1,f2);
                if(!f1 && f2)flight.emplace_back(link[i][0],link[i][1]);
                else if(f1 && !f2)flight.emplace_back(link[i][1],link[i][0]);
            }
            printf("%d",flight.size());
            clr(vis,false);
            for(auto it:flight)
            {
                rep(i,1,k)
                {
                    if(!vis[i] && pos[i]==it.first)
                    {
                        it.first=i;
                        vis[i]=true, pos[i]=it.second;
                        break;
                    }
                }
                printf(" %d %d",it.first,it.second+1);
            }
            printf("\n");
        }
    }
    return 0;
}