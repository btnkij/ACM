/**
* Number:
* Title:
* Status:AC
* Tag:[二分]
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
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int n,m;
int a[1000010];
bool check(int mid)
{
    int cnt=0,sum=0;
    repne(i,0,n)
    {
        sum+=a[i];
        if(sum>mid)
        {
            sum=a[i];
            cnt++;
        }
    }
    cnt+=(int)(sum>0);
    return cnt<=m;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi(n,m);
    int lt=-INF, rt=0;
    repne(i,0,n)
    {
        readi(a[i]);
        lt=max(lt,a[i]);
        rt+=a[i];
    }
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(check(mid))rt=mid;
        else lt=mid+1;
    }
    printf("%d",lt);
    return 0;
}