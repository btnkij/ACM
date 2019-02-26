/**
* Number:ybt1313
* Title:位数问题
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

const int MOD = 12345;
ll dp_even[1004];
ll dp_odd[1004];
int main()
{
    int n;
    cin >> n;
    dp_even[1] = 9;
    dp_odd[1] = 1;
    for (int i = 2; i < n; i++)
    {
        dp_even[i] = (9 * dp_even[i - 1] + dp_odd[i - 1]) % MOD;
        dp_odd[i] = (9 * dp_odd[i - 1] + dp_even[i - 1]) % MOD;
    }
    cout << (8 * dp_even[n - 1] + dp_odd[n - 1]) % MOD << endl;
    return 0;
}