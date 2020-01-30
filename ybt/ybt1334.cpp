/**
* Number:ybt1334
* Title:围圈报数
* Status:AC
* Tag:[链表]
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

struct Node
{
    int num;
    int pre, nxt;
} linked[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n, m;
    scanf("%d %d", &n, &m);
    for (int i = 0; i < n; i++)
    {
        linked[i].num = i + 1;
        linked[i].pre = (i - 1 + n) % n;
        linked[i].nxt = (i + 1) % n;
    }
    int p = 0;
    for (int i = n; i >= 1; i--)
    {
        int k = (m - 1) % i + 1;
        while (k > 1)
        {
            p = linked[p].nxt;
            k--;
        }
        linked[linked[p].pre].nxt = linked[p].nxt;
        linked[linked[p].nxt].pre = linked[p].pre;
        printf("%d ", linked[p].num);
        p = linked[p].nxt;
    }
    printf("\n");
    return 0;
}