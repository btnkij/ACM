/**
* Number:uva11054
* Title:Wine trading in Gergovia
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
    int n;
    ll ans,pre;
    while(scanf("%d",&n)!=EOF && n)
    {
        ans=pre=0;
        while(n--)
        {
            int t; scanf("%d",&t);
            pre+=t;
            ans+=abs(pre);
        }
        cout<<ans<<endl;
    }
    return 0;
}