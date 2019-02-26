/**
* Number:ybt1242
* Title:网线主管
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

int n,k;
int num[10004];
bool check(int len)
{
    int cnt=0;
    repne(i,0,n)
    {
        cnt+=num[i]/len;
        if(cnt>=k)return true;
    }
    return cnt>=k;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(n,k);
    int lt=1, rt=1;
    repne(i,0,n)
    {
        double t;
        scanf("%lf",&t);
        num[i]=int(t*100);
        rt=max(rt, num[i]);
    }
    while(lt<rt)
    {
        int mid=(lt+rt+1)>>1;
        if(!check(mid))rt=mid-1;
        else lt=mid;
    }
    if(!check(lt))printf("0.00\n");
    else printf("%.2lf\n",lt/100.0);
    return 0;
}