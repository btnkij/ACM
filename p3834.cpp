/**
* Number:p3834
* Title:【模板】可持久化线段树 1（主席树）
* Status:AC
* Tag:[可持久化线段树, 主席树]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    int sum, lc, rc;
}tree[200010*20];
int root[200010], tot;
void build(int& id, int lt, int rt)
{
    id=tot++;
    if(lt==rt)return;
    int mid=(lt+rt)>>1;
    build(tree[id].lc, lt, mid);
    build(tree[id].rc, mid+1, rt);
}
int add(int pos, int id, int lt, int rt)
{
    int p=tot++;
    Node& nod=tree[p];
    nod=tree[id];
    nod.sum++;
    if(lt!=rt)
    {
        int mid=(lt+rt)>>1;
        if(pos<=mid)nod.lc=add(pos, nod.lc, lt, mid);
        else nod.rc=add(pos, nod.rc, mid+1, rt);
    }
    return p;
}
int query(int qlt, int qrt, int lt, int rt, int k)
{
    if(lt==rt)return lt;
    int cnt=tree[tree[qrt].lc].sum-tree[tree[qlt].lc].sum;
    int mid=(lt+rt)>>1;
    if(cnt>=k)return query(tree[qlt].lc, tree[qrt].lc, lt, mid, k);
    else return query(tree[qlt].rc, tree[qrt].rc, mid+1, rt, k-cnt);
}

int a[200010], b[200010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,n)
    {
        readi(a[i]);
        b[i]=a[i];
    }
    sort(b,b+n);
    int e=unique(b, b+n)-b;
    build(root[0], 1, e);
    repne(i,0,n)
    {
        int ord=lower_bound(b,b+e,a[i])-b+1;
        root[i+1]=add(ord, root[i], 1, e);
    }
    while(m--)
    {
        int lt,rt,k; readi(lt,rt,k);
        printf("%d\n", b[query(root[lt-1],root[rt],1,e,k)-1]);
    }
    return 0;
}