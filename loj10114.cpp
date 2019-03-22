/**
* Number:loj10114
* Title:「一本通 4.1 例 2」数星星 Stars 
* Status:AC
* Tag:[树状数组]
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

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN = 32005;
int sum[32010];
void add(int x, int delta)
{
    x++;
    while(x<=MAXN)
    {
        sum[x]+=delta;
        x+=x&-x;
    }
}
int query(int x)
{
    x++;
    int ans=0;
    while(x)
    {
        ans+=sum[x];
        x^=x&-x;
    }
    return ans;
}

int cnt[15010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)
    {
        int x,y; readi(x,y);
        cnt[query(x)]++;
        add(x,1);
    }
    repne(i,0,n)printf("%d\n",cnt[i]);
    return 0;
}