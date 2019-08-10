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

struct Node
{
    double a,t;
    bool operator<(const Node& rhs)const
    {
        return a>rhs.a;
    }
}nodes[10010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    double s1=0;
    double v=0;
    repne(i,0,n)
    {
        scanf("%lf %lf",&nodes[i].a,&nodes[i].t);
    }
    repne(i,0,n)
    {
        Node& nod=nodes[i];
        s1+=v*nod.t+0.5*nod.a*pow(nod.t,2);
        v+=nod.a*nod.t;
    }
    sort(nodes,nodes+n);
    double s2=0;
    v=0;
    repne(i,0,n)
    {
        Node& nod=nodes[i];
        s2+=v*nod.t+0.5*nod.a*pow(nod.t,2);
        v+=nod.a*nod.t;
    }
    printf("%.1lf",s2-s1);
    return 0;
}