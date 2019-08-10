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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const ll MOD=1e9+7;
ll qpow[400010];
// struct Edge
// {
//     int val,nxt;
// }edges[400010];
// int head[100010],edge_id;
// int cur[100010];
// void addedge(int pre,int val)
// {
//     edges[edge_id]=(Edge{val,head[pre]});
//     head[pre]=edge_id++;
// }
struct Node
{
    int val,st,i;
    bool operator<(const Node& rhs)const
    {
        if(st==rhs.st)return i>rhs.i;
        else return val<rhs.val;
    }
}nodes[400010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    int tot=0;
    repne(i,0,n)
    {
        int k; readi(k);
        repne(j,0,k)
        {
            int v; readi(v);
            nodes[tot++]=(Node){v,i,k};
        }
    }
    sort(nodes,nodes+tot);
    qpow[0]=1;
    rep(i,1,tot)qpow[i]=qpow[i-1]*365%MOD;
    ll ans=0;
    repne(i,0,tot)
    {
        ans=(ans+nodes[i].val*qpow[tot-i])%MOD;
    }
    printf("%lld",ans);
    return 0;
}