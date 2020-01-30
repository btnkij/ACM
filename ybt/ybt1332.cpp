/**
* Number:ybt1332
* Title:周末舞会
* Status:AC
* Tag:[]
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
    int a, b, n;
    scanf("%d %d %d", &a, &b, &n);
    int i = 1, j = 1;
    while (n--)
    {
        printf("%d %d\n", i, j);
        i = i % a + 1;
        j = j % b + 1;
    }
    return 0;
}