/**
* Number:2176
* Title:序列
* Status:AC
* Tag:[最长上升子序列, LIS]
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

int arr[1000010];
int frodp[1000010],bacdp[1000010];
int Q[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep(i,1,n)readi(arr[i]);
    int len=0;
    for(int i=1;i<=n;i++)
    {
        int p=lower_bound(Q,Q+len,arr[i])-Q;
        Q[p]=arr[i];
        frodp[i]=p+1;
        len=max(len,p+1);
    }
    len=0;
    for(int i=n;i>=1;i--)
    {
        int p=lower_bound(Q,Q+len,arr[i])-Q;
        Q[p]=arr[i];
        bacdp[i]=p+1;
        len=max(len,p+1);
    }
    int ans=0;
    for(int i=1;i<=n;i++)
    {
        ans=max(ans,min(frodp[i],bacdp[i])*2-1);
    }
    printf("%d",ans);
    return 0;
}