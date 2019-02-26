/**
* Number:ybt1205
* Title:汉诺塔问题
* Status:AC
* Tag:[递归]
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

void solve(int n, char src, char via, char dst)
{
    if (n == 0)
        return;
    solve(n - 1, src, dst, via);
    printf("%c->%d->%c\n", src, n, dst);
    solve(n - 1, via, src, dst);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    char a[2], b[2], c[2];
    scanf("%d", &n);
    scanf("%s %s %s", a, b, c);
    solve(n, *a, *c, *b);
    return 0;
}