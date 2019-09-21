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

const int MAXN=1e2+10;
int n,m;
int arr[MAXN];
int lfac[MAXN],lmul[MAXN],rfac[MAXN],rmul[MAXN];
int lvis[MAXN],rvis[MAXN];
int sz;
struct Node
{
    int l,r,id;
    bool operator<(const Node& rhs)const
    {
        return l/sz==rhs.l/sz ? r<rhs.r : l<rhs.l;
    }
};
vector<Node> Q;
ll ans[MAXN];

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    rep(i,1,n)
    {
        int t; readi(t);
        for(int j=1;j*j<=t;j++)
        {
            if(t%j!=0)continue;
            lfac[i]+=lvis[j];
            if(lvis[j])rmul[j]++;
        }
        lvis[arr[i]=t]=1;
    }
    for(int i=n;i>=1;i--)
    {
        int t=arr[i];
        for(int j=1;j*j<=t;j++)
        {
            if(t%j!=0)continue;
            rfac[i]+=rvis[j];
            if(rvis[j])lmul[j]++;
        }
        rvis[t]=1;
    }
    rep(i,1,m)
    {
        int l,r; readi(l,r);
        Q.push_back((Node){l,r,i});
    }
    sort(Q.begin(),Q.end());
    int wndl=1,wndr=0;
    ll wndans=0;
    repne(i,0,m)
    {
        Node& nod=Q[i];
        while(wndr<nod.r)
        {
            wndr++;
            wndans+=lfac[wndr]+lmul[wndr]
        }
    }
    rep(i,1,m)printf("%lld\n",ans[i]);
    return 0;
}