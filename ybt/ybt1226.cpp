/**
* Number:ybt1226
* Title:装箱问题
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

int w[8];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(true)
    {
        bool zero=true;
        rep(i,1,6)
        {
            readi(w[i]);
            if(w[i])zero=false;
        }
        if(zero)break;
        int ans = (w[3] + 3) / 4 + w[4] + w[5] + w[6];
        w[3] %= 4;
        w[1] -= w[5] * 11;
        w[2] -= w[4] * 5;
        if(w[3] == 1)
            w[1] -= 7, w[2] -= 5;
        else if(w[3] == 2)
            w[1] -= 6, w[2] -= 3;
        else if(w[3] == 3)
            w[1] -= 5, w[2] -= 1;
        if(w[2] < 0)
        {
            w[1] += w[2] * 4;
            w[2] = 0;
        }
        ans += (w[2] + 8) / 9;
        w[2] = 9 - w[2] % 9;
        w[1] = max(0, w[1] - w[2] * 4);
        ans += (w[1] + 35) / 36;
        printf("%d\n", ans);
    }
    return 0;
}