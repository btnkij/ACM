/**
* Number:loj10128
* Title:「一本通 4.3 练习 2」花神游历各国
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

const int MAXN=1e5+10;
int mx[MAXN<<2];
ll sum[MAXN<<2];
void push_up(int p)
{
    mx[p]=max(mx[p<<1],mx[p<<1|1]);
    sum[p]=sum[p<<1]+sum[p<<1|1];
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        scanf("%d",&mx[p]);
        sum[p]=mx[p];
        return;
    }
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    build(lc,lt,mid);
    build(rc,mid+1,rt);
    push_up(p);
}
int qlt, qrt;
void set(int p,int lt,int rt)
{
    if(lt==rt)
    {
        sum[p]=mx[p]=(int)sqrt(sum[p]);
        return;
    }
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(qlt<=mid && mx[lc]>1)set(lc,lt,mid);
    if(mid<qrt && mx[rc]>1)set(rc,mid+1,rt);
    push_up(p);
}
ll query(int p,int lt,int rt)
{
    if(qlt<=lt && rt<=qrt)return sum[p];
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    ll ans=0;
    if(qlt<=mid)ans+=query(lc,lt,mid);
    if(mid<qrt)ans+=query(rc,mid+1,rt);
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    build(1,1,n);
    int m; readi(m);
    while(m--)
    {
        int op; readi(op, qlt, qrt);
        if(op==1)printf("%lld\n",query(1,1,n));
        else if(op==2)set(1,1,n);
    }
    return 0;
}