/**
* Number:uva12097
* Title:Pie
* Status:AC
* Tag:[二分]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
#define eps 1e-4
typedef long long ll;

double area[10010];
int n, f;
bool ok(double x)
{
    int _f = f + 1;
    for (int i = 0; i < n; i++)
    {
        _f -= int(area[i] / x);
    }
    return _f <= 0;
}
int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &f);
        double lt = 0, rt = 0;
        for (int i = 0; i < n; i++)
        {
            double r;
            scanf("%lf", &r);
            area[i] = PI * r * r;
            rt = max(rt, area[i]);
        }
        while ((rt - lt) > eps)
        {
            double mid = (lt + rt) / 2;
            // printf("%lf %lf %lf\n", lt, mid, rt);
            if (ok(mid))
                lt = mid;
            else
                rt = mid;
        }
        printf("%.4lf\n", lt);
    }
    return 0;
}