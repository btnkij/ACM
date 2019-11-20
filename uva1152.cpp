/**
* Number:uva1152
* Title:4 Values whose Sum is 0
* Status:AC
* Tag:[meet-in-the-mid]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <unordered_map>
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

const int MAXN=4010;
int a[MAXN],b[MAXN],c[MAXN],d[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    unordered_map<int,int> cnt;
    int T; readi(T);
    while(T--)
    {
        cnt.clear();
        int n; readi(n);
        repne(i,0,n)scanf("%d %d %d %d",a+i,b+i,c+i,d+i);
        repne2(i,0,n,j,0,n)cnt[a[i]+b[j]]++;
        int ans=0;
        repne2(i,0,n,j,0,n)
        {
            int sum=-(c[i]+d[j]);
            if(cnt.count(sum))ans+=cnt[sum];
        }
        printf("%d\n",ans);
        if(T)printf("\n");
    }
    return 0;
}