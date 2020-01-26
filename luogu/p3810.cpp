/**
* Number:p3810
* Title:【模板】三维偏序（陌上花开）
* Status:AC
* Tag:[cdq, 分治, 归并排序]
* desc:定义三维偏序A(x1,y1,z1)<=B(x2,y2,z2)当且仅当x1<=x2 and y1<=y2 and z1<=z2。求排序为0..n-1的三元组个数。
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

inline int readi(int &i1) { return scanf("%d", &i1); }
inline int readi(int &i1, int &i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int &i1, int &i2, int &i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int &i1, int &i2, int &i3, int &i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char *s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 2e5 + 10;
const int MAX_DIM = 2;
struct Node
{
    int v[3], sz, ans;
} nodes[MAXN];
pair<Node *, int> buf[4][MAXN];
void cdq(int beg, int end, int dim)
{
    if (end - beg <= 1)
        return;
    int mid = (beg + end) >> 1;
    cdq(beg, mid, dim);
    cdq(mid, end, dim);
    pair<Node *, int> *cur = buf[dim], *nxt = buf[dim + 1];
    int i = beg, j = mid, k = beg, cnt = 0;
    while (i < mid || j < end)
    {
        if (j == end || i < mid && cur[i].first->v[dim] <= cur[j].first->v[dim])
        {
            nxt[k] = cur[i];
            if (dim == 1 || dim < MAX_DIM && cur[i].second == 1)
                nxt[k].second = 1;
            if (dim == MAX_DIM && nxt[k].second == 1)
                cnt += nxt[k].first->sz;
            i++, k++;
        }
        else
        {
            nxt[k] = cur[j];
            if (dim == 1 || dim < MAX_DIM && cur[j].second == 2)
                nxt[k].second = 2;
            if (dim == MAX_DIM && nxt[k].second == 2)
                nxt[k].first->ans += cnt;
            j++, k++;
        }
    }
    copy(nxt + beg, nxt + end, cur + beg);
    if (dim < MAX_DIM)
        cdq(beg, end, dim + 1);
}
int ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, k;
    readi(n, k);
    repne(i, 0, n)
    {
        readi(nodes[i].v[0], nodes[i].v[1], nodes[i].v[2]);
        buf[1][i] = make_pair(nodes + i, 0);
    }
    pair<Node *, int> *cur = buf[1];
    sort(cur, cur + n, [](const pair<Node *, int> &lhs, const pair<Node *, int> &rhs) {
        int *v1 = lhs.first->v, *v2 = rhs.first->v;
        if (v1[0] != v2[0])
            return v1[0] < v2[0];
        if (v1[1] != v2[1])
            return v1[1] < v2[1];
        return v1[2] < v2[2];
    });
    int tot = 0;
    for (int i = 0; i < n;)
    {
        int cnt = 1;
        while (i + 1 < n && cur[i].first->v[0] == cur[i + 1].first->v[0] && cur[i].first->v[1] == cur[i + 1].first->v[1] && cur[i].first->v[2] == cur[i + 1].first->v[2])
        {
            cnt++, i++;
        }
        cur[tot] = cur[i];
        cur[tot].first->sz = cnt;
        tot++, i++;
    }
    cdq(0, tot, 1);
    repne(i, 0, tot) ans[cur[i].first->ans + cur[i].first->sz - 1] += cur[i].first->sz;
    repne(i, 0, n) printf("%d\n", ans[i]);
    return 0;
}

/**
* Number:p3810
* Title:【模板】三维偏序（陌上花开）
* Status:AC
* Tag:[cdq, 分治, 树状数组]
**/

/*
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

struct Node
{
    int a,b,c,k,low;
    bool operator==(const Node& rhs)const
    {
        return a==rhs.a && b==rhs.b && c==rhs.c;
    }
}nodes[MAXN];
bool cmpa(const Node& lhs,const Node& rhs)
{
    if(lhs.a!=rhs.a)return lhs.a<rhs.a;
    if(lhs.b!=rhs.b)return lhs.b<rhs.b;
    return lhs.c<rhs.c;
}
bool cmpb(const Node& lhs,const Node& rhs)
{
    if(lhs.b!=rhs.b)return lhs.b<rhs.b;
    return lhs.c<rhs.c;
}

int tree[MAXN],N;
void add(int x,int v)
{
    for(;x<=N;x+=x&-x)tree[x]+=v;
}
int query(int x)
{
    int ans=0;
    for(;x;x^=x&-x)ans+=tree[x];
    return ans;
}

void cdq(int lt,int rt)
{
    if(rt-lt<=1)return;
    int mid=(lt+rt)>>1;
    cdq(lt,mid); sort(nodes+lt,nodes+mid,cmpb);
    cdq(mid,rt); sort(nodes+mid,nodes+rt,cmpb);
    int i=lt,j=mid;
    for(;j<rt;j++)
    {
        while(i<mid && nodes[i].b<=nodes[j].b)
        {
            add(nodes[i].c,nodes[i].k);
            i++;
        }
        nodes[j].low+=query(nodes[j].c);
    }
    for(i--;i>=lt;i--)add(nodes[i].c,-nodes[i].k);
}

int ans[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    N=k;
    repne(i,0,n)readi(nodes[i].a,nodes[i].b,nodes[i].c);
    sort(nodes,nodes+n,cmpa);
    int tot=0;
    for(int i=0;i<n;)
    {
        int j=i+1;
        while(nodes[i]==nodes[j])j++;
        nodes[tot]=nodes[i];
        nodes[tot].k=j-i;
        tot++, i=j;
    }
    cdq(0,tot);
    repne(i,0,n)ans[nodes[i].low+nodes[i].k-1]+=nodes[i].k;
    repne(i,0,n)printf("%d\n",ans[i]);
    return 0;
}
*/