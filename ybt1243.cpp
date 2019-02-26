/**
* Number:ybt1243
* Title:月度开销
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

int n,m;
int cost[100004];
bool check(int x)
{
    int sum=0;
    int cnt=1;
    repne(i,0,n)
    {
        sum+=cost[i];
        if(sum>x)
        {
            sum=cost[i];
            cnt++;
        }
    }
    return cnt<=m;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n,m);
    int lt=0,rt=0;
    repne(i,0,n)
    {
        readi(cost[i]);
        lt=max(lt,cost[i]);
        rt+=cost[i];
    }
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(!check(mid))lt=mid+1;
        else rt=mid;
    }
    printf("%d\n",lt);
    return 0;
}