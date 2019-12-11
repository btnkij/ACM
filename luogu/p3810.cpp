/**
* Number:p3810
* Title:【模板】三维偏序（陌上花开）
* Status:AC
* Tag:[cdq, 分治]
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