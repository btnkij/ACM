/**
* Number:2228
* Title:洁姐姐带学画画
* Status:AC
* Tag:[最小生成树, 递推]
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
    int from,to;
    double h,d;
    int nxt;
}edges[2000010];
int head[1010],edge_id;
void addedge(int from,int to,double h,double d)
{
    edges[edge_id]=(Edge){from,to,h,d,head[from]};
    head[from]=edge_id++;
}

struct Node
{
    Edge* e;
    double k;
    bool operator<(const Node& rhs)const
    {
        return k>rhs.k;
    }
};
int n,x[1010],y[1010],z[1010];
bool vis[1010];
double prim(double mid)
{
    mset(vis,false);
    vis[0]=true;
    priority_queue<Node> Q;
    for(int i=head[0];~i;i=edges[i].nxt)
    {
        Edge& e=edges[i];
        Q.push((Node){&e, e.h-mid*e.d});
    }
    int cnt=n-1;
    double sumh=0,sumd=0;
    while(!Q.empty() && cnt)
    {
        Node cur=Q.top(); Q.pop();
        if(vis[cur.e->to])continue;
        vis[cur.e->to]=true;
        cnt--;
        sumh+=cur.e->h;
        sumd+=cur.e->d;
        for(int i=head[cur.e->to];~i;i=edges[i].nxt)
        {
            Edge& e=edges[i];
            if(!vis[e.to])Q.push((Node){&e, e.h-mid*e.d});
        }
    }
    return sumh/sumd;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n);
    repne(i,0,n)readi(x[i],y[i],z[i]);
    mset(head,-1);
    repne2(i,0,n,j,0,i)
    {
        double h=fabs(z[i]-z[j]);
        double d=sqrt(pow(x[i]-x[j],2)+pow(y[i]-y[j],2));
        addedge(i,j,h,d); addedge(j,i,h,d);
    }
    double pre=0,cur=1;
    while(fabs(pre-cur)>1e-4)
    {
        pre=cur;
        cur=prim(pre);
    }
    printf("%.3lf",cur);
    return 0;
}