/**
* Number:ybt1236
* Title:区间合并
* Status:AC
* Tag:[排序]
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

struct Seg
{
    int begin,end;
    bool operator<(const Seg& rhs)const
    {
        return begin < rhs.begin;
    }
}segs[50010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)readi2(segs[i].begin, segs[i].end);
    sort(segs, segs+n);
    int end=segs[0].end;
    bool ans=true;
    repne(i,1,n)
    {
        if(segs[i].begin>end)
        {
            ans=false;
            break;
        }
        end=max(end, segs[i].end);
    }
    if(ans)printf("%d %d\n",segs[0].begin, end);
    else printf("no\n");
    return 0;
}