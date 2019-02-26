/**
* Number:ybt1207
* Title:求最大公约数问题
* Status:AC
* Tag:[gcd, 数论]
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

ll gcd(ll a, ll b)
{
    while (b)
    {
        ll tmp = a % b;
        a = b;
        b = tmp;
    }
    return a;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ll a, b;
    cin >> a >> b;
    cout << gcd(a, b) << endl;
    return 0;
}