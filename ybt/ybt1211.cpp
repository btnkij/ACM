/**
* Number:ybt1211
* Title:判断元素是否存在
* Status:AC
* Tag:[dfs]
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

int k;
bool ans;
void dfs(int n)
{
    if (ans)
        return;
    if (n == k)
    {
        ans = true;
        return;
    }
    n--;
    if (n < k)
        return;
    if (n % 2 == 0 && !ans)
        dfs(n / 2);
    if (n % 3 == 0 && !ans)
        dfs(n / 3);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int x;
    scanf("%d,%d", &k, &x);
    dfs(x);
    printf("%s\n", ans ? "YES" : "NO");
    return 0;
}