/**
* Number:loj10178
* Title:「一本通 5.5 例 4」旅行问题
* Status:AC
* Tag:[dp, 单调队列]
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e6+10;
ll p[MAXN*2],d[MAXN*2];
ll sum[MAXN*2];
struct Node
{
    ll val;
    int idx;
}Q[MAXN];
int head,tail;
bool ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)scanf("%lld %lld",p+i,d+i);
    copy(p+1,p+n+1,p+n+1);
    copy(d+1,d+n+1,d+n+1);
    rep(i,1,n<<1)sum[i]=sum[i-1]+p[i]-d[i];
    rep(i,1,n<<1)
    {
        while(head!=tail && Q[head].idx<=i-n)head++;
        while(head!=tail && Q[tail-1].val>=sum[i])tail--;
        Q[tail++]=(Node){sum[i],i};
        if(i>=n && Q[head].val-sum[i-n]>=0)ans[i-n+1]=true;
    }
    sum[n*2+1]=0;
    d[0]=d[n];
    for(int i=2*n;i>=1;i--)sum[i]=sum[i+1]+p[i]-d[i-1];
    head=tail=0;
    for(int i=n*2;i>=1;i--)
    {
        while(head!=tail && Q[head].idx>=i+n)head++;
        while(head!=tail && Q[tail-1].val>=sum[i])tail--;
        Q[tail++]=(Node){sum[i],i};
        if(i<=n+1 && Q[head].val-sum[i+n]>=0)ans[i-1]=true;
    }
    rep(i,1,n)printf("%s\n",ans[i]?"TAK":"NIE");
    return 0;
}