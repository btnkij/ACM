/**
* Number:ybt1224
* Title:最大子矩阵
* Status:AC
* Tag:[dp]
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

int sum[104];
int mat[104][104];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    readi(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            readi(mat[i][j]);
        }
    }
    int ans = -INF;
    for (int lt = 0; lt < n; lt++)
    {
        mset(sum, 0);
        for (int rt = lt; rt < n; rt++)
        {
            int tmp = 0;
            for (int i = 0; i < n; i++)
            {
                sum[i] += mat[rt][i];
                tmp += sum[i];
                ans = max(ans, tmp);
                tmp = max(tmp, 0);
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}