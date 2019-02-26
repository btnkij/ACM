/**
* Number:ybt1230
* Title:寻找平面上的极大点
* Status:AC
* Tag:[贪心]
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

const int MAXX=104;
int px[MAXX];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(px,-1);
    int n; readi(n);
    while(n--)
    {
        int x,y;
        readi2(x,y);
        px[x]=max(px[x], y);
    }
    int maxy=-INF;
    for(int i=MAXX-1;i>=0;i--)
    {
        if(px[i]<=maxy)px[i]=-1;
        else maxy=px[i];
    }
    bool first=true;
    repne(i,0,MAXX)
    {
        if(px[i]<0)continue;
        if(!first)putchar(',');
        first=false;
        printf("(%d,%d)",i,px[i]);
    }
    return 0;
}