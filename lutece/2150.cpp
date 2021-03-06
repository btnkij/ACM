/**
* Number:2150
* Title:拍照
* Status:AC
* Tag:[单调队列]
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

#define INF 0x3f3f3f3f3f3f3f3f
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

struct Node
{
    ll val;
    int tin;
}Q[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    int head=0,tail=0;
    ll ans=-INF, sum=0;
    scanf("%lld",&sum);
    ans=sum;
    Q[tail++]=(Node){sum,0};
    repne(i,1,n)
    {
        int t; readi(t);
        sum+=t;
        ans=max(ans,(ll)t);
        if(i<m)ans=max(ans,sum);
        while(head<tail && Q[head].tin<i-m)head++;
        if(head<tail)ans=max(ans,sum-Q[head].val);
        while(head<tail && sum<=Q[tail-1].val)tail--;
        Q[tail++]=(Node){sum,i};
    }
    printf("%lld\n",ans);
    return 0;
}