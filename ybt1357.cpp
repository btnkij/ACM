/**
* Number:ybt1357
* Title:车厢调度(train)
* Status:AC
* Tag:[stack, 栈]
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

int S[1010], top;
int main()
{
    int n;
    scanf("%d", &n);
    top = -1;
    int m = 1;
    for (int i = 0; i < n; i++)
    {
        int t;
        scanf("%d", &t);
        while (m <= n && (top < 0 || S[top] != t))
        {
            S[++top] = m;
            m++;
        }
        if (top >= 0 && S[top] == t)
            top--;
    }
    printf("%s\n", top == -1 ? "YES" : "NO");
    return 0;
}