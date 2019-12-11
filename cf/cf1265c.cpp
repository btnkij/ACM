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

int a[400010];
int cnt[400010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n; readi(n);
        rep(i,1,n)readi(a[i]);
        int ans[3]={0,0,0},tot=0;
        int maxn=n/2;
        int i=1,cnt=1;
        while(i+cnt<=n && a[i+cnt]==a[i])cnt++;
        ans[0]=cnt;
        tot+=cnt;
        i+=cnt;
        while(i<=n && tot<=maxn && ans[1]<=ans[0])
        {
            cnt=1;
            while(i+cnt<=n && a[i+cnt]==a[i])cnt++;
            ans[1]+=cnt;
            tot+=cnt;
            i+=cnt;
        }
        while(i<=n && tot<=maxn)
        {
            cnt=1;
            while(i+cnt<=n && a[i+cnt]==a[i])cnt++;
            if(tot+cnt>maxn)break;
            tot+=cnt;
            ans[2]+=cnt;
            i+=cnt;
        }
        if(tot<=maxn && ans[0]<ans[1] && ans[0]<ans[2])
        {
            printf("%d %d %d\n", ans[0], ans[1], ans[2]);
        }
        else
        {
            printf("0 0 0\n");
        }
    }
    return 0;
}