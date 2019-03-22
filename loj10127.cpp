/**
* Number:ybt1549, loj132
* Title:「一本通 4.3 练习 1」最大数 
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

const int MAXN=2e5+10;
int node[MAXN<<2];
void push_up(int p)
{
    node[p]=max(node[p<<1],node[p<<1|1]);
}
void build(int p,int lt,int rt)
{
    if(lt==rt)
    {
        node[p]=-INF;
        return;
    }
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    build(lc,lt,mid);
    build(rc,mid+1,rt);
    push_up(p);
}
int qlt, qrt, qval;
void set(int p,int lt,int rt)
{
    if(lt==rt && lt==qlt)
    {
        node[p]=qval;
        return;
    }
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    if(qlt<=mid)set(lc,lt,mid);
    else set(rc,mid+1,rt);
    push_up(p);
}
int query(int p,int lt,int rt)
{
    if(qlt<=lt && rt<=qrt)return node[p];
    int lc=p<<1, rc=lc|1;
    int mid=(lt+rt)>>1;
    int ans=-INF;
    if(qlt<=mid)ans=max(ans,query(lc,lt,mid));
    if(mid<qrt)ans=max(ans,query(rc,mid+1,rt));
    return ans;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,mod; readi(n,mod);
    build(1,1,n);
    int tail=0, a=0;
    repne(i,0,n)
    {
        char op[4]; reads(op);
        if(op[0]=='A')
        {
            qlt=++tail;
            readi(qval);
            qval=(qval+a)%mod;
            set(1,1,n);
        }
        else if(op[0]=='Q')
        {
            qrt=tail;
            readi(qlt);
            qlt=tail-qlt+1;
            a=query(1,1,n);
            printf("%d\n",a);
        }
    }
    return 0;
}