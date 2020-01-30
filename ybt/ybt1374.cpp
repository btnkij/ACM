/**
* Number:ybt1374
* Title:铲雪车(snow)
* Status:AC
* Tag:[欧拉回路]
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int srcx, srcy;
    readi2(srcx, srcy);
    double sum=0;
    int x1,y1,x2,y2;
    while(readi4(x1,y1,x2,y2)!=EOF)
    {
        sum+=sqrt(pow(x1-x2,2)+pow(y1-y2,2));
    }
    sum=sum/1000*2/20;
    int h=(int)sum;
    int m=(int)round((sum-h)*60.0);
    printf("%d:%02d",h,m);
    return 0;
}