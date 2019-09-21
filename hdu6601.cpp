/**
* Number:hdu6601
* Title:Keen On Everything But Triangle
* Status:AC
* Tag:[主席树, 区间第k大]
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

const int MAXN=1e5+10;
int a[MAXN],ord[MAXN];

struct Node
{
    int lson,rson,val;
}tree[MAXN*20];
int node_id;
int clone(int ori)
{
    tree[++node_id]=tree[ori];
    return node_id;
}
int update(int p,int lt,int rt,int qpos)
{
    int id=clone(p);
    tree[id].val++;
    if(lt==rt)return id;
    int mid=(lt+rt)>>1;
    if(qpos<=mid)tree[id].lson=update(tree[p].lson,lt,mid,qpos);
    else tree[id].rson=update(tree[p].rson,mid+1,rt,qpos);
    return id;
}
int query(int pl,int pr,int lt,int rt,int nth)
{
    if(lt==rt)return ord[lt];
    int mid=(lt+rt)>>1;
    int cnt=tree[tree[pr].rson].val-tree[tree[pl].rson].val;
    if(cnt>=nth)return query(tree[pl].rson,tree[pr].rson,mid+1,rt,nth);
    else return query(tree[pl].lson,tree[pr].lson,lt,mid,nth-cnt);
}

int len[50];
int root[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,q;
    while(readi(n,q)!=EOF)
    {
        node_id=0;
        rep(i,1,n)
        {
            readi(a[i]);
            ord[i]=a[i];
        }
        sort(ord+1,ord+n+1);
        int tot=unique(ord+1,ord+n+1)-ord;
        rep(i,1,n)
        {
            int id=lower_bound(ord+1,ord+tot,a[i])-ord;
            root[i]=update(root[i-1],1,tot,id);
        }
        while(q--)
        {
            int li,ri; readi(li,ri);
            int lim=min(48,ri-li+1);
            ll ans=-1;
            for(int k=1;k<=lim;k++)
            {
                len[k]=query(root[li-1],root[ri],1,tot,k);
                if(k>=3 && len[k]+len[k-1]>len[k-2])
                {
                    ans=(ll)len[k]+len[k-1]+len[k-2];
                    break;
                }
            }
            printf("%lld\n",ans);
        }
    }
    return 0;
}