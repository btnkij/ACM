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

const int MAXN=2e5+10;
int a[MAXN];
struct Node
{
    int l,r,d;
    bool operator<(const Node& rhs)const
    {
        return l<rhs.l;
    }
}nodes[MAXN];
bool check(int n,int k,int mid,int t)
{
    int ans=0,pre=0;
    repne(i,0,k)
    {
        Node& nod=nodes[i];
        if(nod.d>mid)
        {
            ans+=max(0,nod.r-max(nod.l,pre)+1);
            pre=max(pre,nod.r+1);
        }
    }
    return n+ans*2+1<=t;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n,k,t; readi(m,n,k,t);
    repne(i,0,m)readi(a[i]);
    repne(i,0,k)readi(nodes[i].l,nodes[i].r,nodes[i].d);
    sort(nodes,nodes+k);
    int lt=0,rt=MAXN;
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(check(n,k,mid,t))rt=mid;
        else lt=mid+1;
    }
    int ans=count_if(a,a+m,[lt](int x){return x>=lt;});
    printf("%d\n",ans);
    return 0;
}