/**
* Number:ybt1209
* Title:分数求和
* Status:AC
* Tag:[分数运算]
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

int gcd(int a, int b)
{
    return b == 0 ? a : gcd(b, a % b);
}
void add(int &a1, int &b1, int a2, int b2)
{
    a1 = a1 * b2 + a2 * b1;
    b1 = b1 * b2;
    int d = gcd(a1, b1);
    a1 /= d;
    b1 /= d;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    int ans_a = 0, ans_b = 1;
    while (n--)
    {
        int a, b;
        scanf("%d/%d", &a, &b);
        add(ans_a, ans_b, a, b);
    }
    if (ans_b == 1)
        printf("%d\n", ans_a);
    else
        printf("%d/%d\n", ans_a, ans_b);
    return 0;
}