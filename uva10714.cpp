/**
* Number:uva10714
* Title:Ants 
* Status:AC
* Tag:[greedy]
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
typedef long long ll;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        int l, n;
        scanf("%d %d", &l, &n);
        int p;
        int ansmax = 0, ansmin = 0;
        for (int i = 0; i < n; i++)
        {
            scanf("%d", &p);
            ansmax = max(ansmax, max(p, l - p));
            ansmin = max(ansmin, min(p, l - p));
        }
        printf("%d %d\n", ansmin, ansmax);
    }
    return 0;
}