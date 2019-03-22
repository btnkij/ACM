/**
* Number:ybt1548 loj132
* Title:树状数组 3 ：区间修改，区间查询
* Status:AC
* Tag:[线段树]
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=1e6+10;
ll sum[MAXN<<2], lazy[MAXN<<2];
void push_up(int p)
{
    sum[p]=sum[p<<1]+sum[p<<1|1];
}
void push_down(int p,int lt,int rt)
{
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    sum[lc]+=lazy[p]*(mid-lt+1);
    lazy[lc]+=lazy[p];
    sum[rc]+=lazy[p]*(rt-mid);
    lazy[rc]+=lazy[p];
    lazy[p]=0;
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        scanf("%lld",&sum[p]);
        return;
    }
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(lt<=mid)build(lc,lt,mid);
    if(mid<rt)build(rc,mid+1,rt);
    push_up(p);
}
int qlt,qrt;
ll qval;
void add(int p,int lt,int rt)
{
    if(qlt<=lt && rt<=qrt)
    {
        sum[p]+=qval*(rt-lt+1);
        lazy[p]+=qval;
        return;
    }
    push_down(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(mid>=qlt)add(lc,lt,mid);
    if(mid<qrt)add(rc,mid+1,rt);
    push_up(p);
}
ll query(int p,int lt,int rt)
{
    
    if(qlt<=lt && rt<=qrt)return sum[p];
    push_down(p,lt,rt);
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    ll ans=0;
    if(mid>=qlt)ans+=query(lc,lt,mid);
    if(mid<qrt)ans+=query(rc,mid+1,rt);
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    build(1,1,n);
    while(m--)
    {
        int k; readi(k);
        if(k==1)
        {
            scanf("%d %d %lld",&qlt,&qrt,&qval);
            add(1,1,n);
        }
        else if(k==2)
        {
            scanf("%d %d",&qlt,&qrt);
            printf("%lld\n",query(1,1,n));
        }
    }
    return 0;
}