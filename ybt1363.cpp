/**
* Number:ybt1363
* Title:小球(drop)
* Status:AC
* Tag:[二叉树, 二进制]
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int D, I;
    scanf("%d %d", &D, &I);
    int ans = 1;
    I--;
    for (int i = 1; i < D; i++)
    {
        if ((I & 1) == 0)
            ans = ans << 1;
        else
            ans = (ans << 1) | 1;
        I >>= 1;
    }
    printf("%d\n", ans);
    return 0;
}