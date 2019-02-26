/**
* Number:ybt1218
* Title:取石子游戏
* Status:AC
* Tag:[博弈]
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
    int a, b;
    while (scanf("%d %d", &a, &b) != EOF && a && b)
    {
        bool win = true;
        while (true)
        {
            if (a > b)
                swap(a, b);
            if (b / a >= 2)
                break;
            b -= a;
            win = !win;
        }
        printf("%s\n", win ? "win" : "lose");
    }
    return 0;
}