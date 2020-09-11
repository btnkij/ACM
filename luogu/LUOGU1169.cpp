/**
* Number:LUOGU1169
* Title:[NOI2002]银河英雄传说
* Status:AC
* Tag:[并查集]
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

constexpr int N=30010;
int fa[N],ord[N],rk[N];
int findr(int x)
{
    if(x==fa[x])return x;
    int r=findr(fa[x]);
    ord[x]=ord[x]+ord[fa[x]];
    return fa[x]=r;
}
void merge(int x,int y)
{
    int rx=findr(x),ry=findr(y);
    if(rx==ry)return;
    ord[rx]+=rk[ry];
    rk[ry]+=rk[rx];
    fa[rx]=ry;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    iota(fa,fa+N,0);
    fill(rk,rk+N,1);
    fill(ord,ord+N,0);
    int T; cin>>T;
    while(T--)
    {
        char op[4];
        int x, y;
        cin>>op>>x>>y;
        if(op[0]=='M')merge(x,y);
        else if(op[0]=='C')
        {
            int rx=findr(x), ry=findr(y);
            if(rx!=ry)cout<<"-1\n";
            else cout<<max(0,abs(ord[x]-ord[y])-1)<<"\n";
        }
    }
    return 0;
}