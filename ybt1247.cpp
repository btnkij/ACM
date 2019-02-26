/**
* Number:ybt1247
* Title:河中跳房子
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int L, n, m;
int num[50004];
bool check(int x)
{
    int pre=0;
    int cnt=0;
    rep(i,0,n)
    {
        if(num[i]-pre<x)cnt++;
        else pre=num[i];
    }
    return cnt<=m;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi3(L,n,m);
    repne(i,0,n)readi(num[i]);
    num[n]=L;
    int lt=0, rt=L;
    while(lt<rt)
    {
        int mid=(lt+rt+1)>>1;
        if(check(mid))lt=mid;
        else rt=mid-1;
    }
    printf("%d\n",lt);
    return 0;
}