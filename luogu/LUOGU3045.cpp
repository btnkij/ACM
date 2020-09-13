/**
* Number:LUOGU3045
* Title: [USACO12FEB]Cow Coupons G
* Status:AC
* Tag:[贪心, 堆]
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

constexpr int N=50010;
struct Node
{
    int p, c, id;
};
struct cmpc
{
    bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.c > rhs.c;
    }
};
struct cmpp
{
    bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.p > rhs.p;
    }
};
struct cmppc
{
    bool operator()(const Node& lhs, const Node& rhs)
    {
        return lhs.p-lhs.c > rhs.p-rhs.c;
    }
};
bool vis[N];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    int n,k; ll m; cin>>n>>k>>m;
    priority_queue<Node,vector<Node>,cmpc> qc;
    priority_queue<Node,vector<Node>,cmpp> qp;
    priority_queue<Node,vector<Node>,cmppc> qpc;
    for(int i=0;i<n;i++)
    {
        int p, c; cin>>p>>c;
        Node node=(Node){p,c,i};
        qc.push(node);
        qp.push(node);
    }
    for(int i=0;i<k;i++)qpc.push({0,0,-1});
    int ans=0;
    while(true)
    {
        while(!qc.empty() && vis[qc.top().id])qc.pop();
        while(!qp.empty() && vis[qp.top().id])qp.pop();
        if(qc.empty() || qp.empty())break;
        int costc=qpc.top().p-qpc.top().c+qc.top().c;
        int costp=qp.top().p;
        if(m<costc && m<costp)break;
        if(costc<costp)
        {
            qpc.pop();
            vis[qc.top().id]=true;
            qpc.push(qc.top());
            qc.pop();
            m-=costc;
        }
        else
        {
            m-=costp;
            vis[qp.top().id]=true;
            qp.pop();
        }
        ans++;
    }
    cout<<ans<<"\n";
    return 0;
}