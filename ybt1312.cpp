/**
* Number:ybt1312
* Title:昆虫繁殖
* Status:AC
* Tag:[递推]
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

long long a[55], b[55];
int main()
{
    int x, y, z;
    scanf("%d %d %d", &x, &y, &z);
    for (int i = 1; i <= x; i++)
        a[i] = 1, b[i] = 0;
    for (int i = x + 1; i <= z + 1; i++)
    {
        b[i] = y * a[i - x];
        a[i] = a[i - 1] + b[i - 2];
    }
    printf("%lld\n", a[z + 1]);
    return 0;
}