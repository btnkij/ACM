/**
* Number:LUOGO2048
* Title:[NOI2010]超级钢琴
* Status:AC
* Tag:[ST表, 前缀和, 优先队列]
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

constexpr int N=5e5+10;
pair<int,int> dp[N][20];
void init(int n)
{
    for(int k=1;k<20;k++)
    {
        int len=1<<k;
        for(int i=1;i+len-1<=n;i++)
        {
            dp[i][k]=max(dp[i][k-1],dp[i+(len>>1)][k-1]);
        }
    }
}
struct Node
{
    int val,x,lt,rt,mid;
    bool operator<(const Node& rhs)const
    {
        return val<rhs.val;
    }
};
Node query(int x,int lt,int rt)
{
    int len=rt-lt+1;
    int k=0;
    while((1<<k)<=len)k++;
    k--;
    auto maxv=max(dp[lt][k],dp[rt-(1<<k)+1][k]);
    Node nod;
    nod.val=maxv.first-dp[x-1][0].first;
    nod.x=x, nod.lt=lt, nod.rt=rt;
    nod.mid=maxv.second;
    return nod;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k,L,R; scanf("%d %d %d %d",&n,&k,&L,&R);
    for(int i=1;i<=n;i++)
    {
        scanf("%d",&dp[i][0].first);
        dp[i][0].first+=dp[i-1][0].first;
        dp[i][0].second=i;
    }
    init(n);
    priority_queue<Node> Q;
    for(int i=1;i+L-1<=n;i++)
        Q.push(query(i,i+L-1,min(n,i+R-1)));
    ll ans=0;
    while(k--)
    {
        Node nod=Q.top(); Q.pop();
        ans+=nod.val;
        if(nod.mid-1>=nod.lt)
            Q.push(query(nod.x,nod.lt,nod.mid-1));
        if(nod.mid+1<=nod.rt)
            Q.push(query(nod.x,nod.mid+1,nod.rt));
    }
    printf("%lld\n",ans);
    return 0;
}