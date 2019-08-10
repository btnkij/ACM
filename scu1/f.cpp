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
struct segment_tree
{
    int n;
    ll tree[MAXN<<2];
    inline ll push_up(ll lhs, ll rhs)
    {
        return max(lhs,rhs);
    }
    int qlt, qrt;
    ll qval;
    void update_help(int p, int lt, int rt)
    {
        if(lt==rt)
        {
            tree[p]=max(tree[p],qval);
            return;
        }
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        if(qlt<=mid)update_help(lc,lt,mid);
        else if(mid<qlt)update_help(rc,mid+1,rt);
        tree[p]=push_up(tree[lc], tree[rc]);
    }
    void update(int qpos, ll val)
    {
        this->qlt=qpos, this->qval=val;
        update_help(1,1,n);
    }
    ll query_help(int p, int lt, int rt)
    {
        if(qlt<=lt && rt<=qrt)return tree[p];
        int lc=p<<1, rc=lc|1;
        int mid=(lt+rt)>>1;
        ll ans=0;
        if(qlt<=mid)ans=max(ans,query_help(lc,lt,mid));
        if(mid<qrt)ans=max(ans,query_help(rc,mid+1,rt));
        return ans;
    }
    ll query(int qlt, int qrt)
    {
        if(qlt>qrt)return 0;
        this->qlt=qlt, this->qrt=qrt;
        return query_help(1,1,n);
    }
}T;

struct Node
{
    int x,y,val;
    bool operator<(const Node& rhs)const
    {
        return x<rhs.x || x==rhs.x && y<rhs.y;
    }
}nodes[MAXN];
int ord[MAXN];
ll dp[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    T.n=n;
    repne(i,0,n)
    {
        int x,y,v; readi(x,y,v);
        nodes[i]=(Node){x,y,v};
        ord[i]=y;
    }
    sort(nodes,nodes+n);
    sort(ord,ord+n);
    repne(i,0,n)nodes[i].y=lower_bound(ord,ord+n,nodes[i].y)-ord+1;
    ll ans=0;
    int prei=0,prex=-1;
    repne(i,0,n)
    {
        Node& nod=nodes[i];
        if(nod.x!=prex)
        {
            repne(j,prei+1,i)
            {
                T.update(nodes[j].y, dp[j]);
            }
            prex=nod.x;
            prei=i-1;
        }
        if(i && nod.x==nodes[i-1].x && nod.y==nodes[i-1].y)
            dp[i]=dp[i-1]+nod.val;
        else
            dp[i]=nod.val+T.query(1,nod.y-1);
        ans=max(ans, dp[i]);
    }
    printf("%lld",ans);
    return 0;
}