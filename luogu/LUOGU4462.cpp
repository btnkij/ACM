/**
* Number:p4462
* Title:[CQOI2018]异或序列
* Status:AC
* Tag:[莫队]
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

int sum[100010];
int cnt[1<<17];
int wnd,lptr,rptr,k;
void add(int val)
{
    wnd+=cnt[val^k];
    cnt[val]++;
}
void remove(int val)
{
    cnt[val]--;
    wnd-=cnt[val^k];
}
struct Node
{
    int id,ql,qr;
}query[100010];
int ans[100010];
int block;
bool cmp(const Node& lhs,const Node& rhs)
{
    int b1=lhs.ql/block, b2=rhs.ql/block;
    if(b1==b2)return b1&1 ? lhs.qr>rhs.qr : lhs.qr<rhs.qr;
    else return b1<b2;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m,k);
    block=sqrt(n);
    rep(i,1,n)
    {
        readi(sum[i]);
        sum[i]^=sum[i-1];
    }
    repne(i,0,m)
    {
        query[i].id=i;
        readi(query[i].ql, query[i].qr);
        query[i].ql--;
    }
    sort(query,query+m,cmp);
    lptr=rptr=0;
    cnt[0]=1;
    repne(i,0,m)
    {
        while(rptr<query[i].qr)add(sum[++rptr]);
        while(lptr>query[i].ql)add(sum[--lptr]);
        while(lptr<query[i].ql)remove(sum[lptr++]);
        while(rptr>query[i].qr)remove(sum[rptr--]);
        ans[query[i].id]=wnd;
    }
    repne(i,0,m)printf("%d\n",ans[i]);
    return 0;
}