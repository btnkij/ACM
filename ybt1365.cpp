/**
* Number:ybt1365
* Title:FBI树(fbi)
* Status:AC
* Tag:[二叉树]
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

char s[40];
int postorder(int left, int right)
{
    if (left >= right)
        return 0;
    int cnt = 0;
    if ((right - left) & 1 == 1)
    {
        for (int i = left; i < right; i++)
        {
            if (s[i] == '1')
                cnt++;
        }
    }
    else
    {
        int mid = (left + right) >> 1;
        cnt += postorder(left, mid);
        cnt += postorder(mid, right);
    }
    if (cnt == 0)
        putchar('B');
    else if (cnt == right - left)
        putchar('I');
    else
        putchar('F');
    return cnt;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    scanf("%d", &n);
    scanf("%s", s);
    postorder(0, strlen(s));
    return 0;
}