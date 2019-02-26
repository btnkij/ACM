/**
* Number:ybt1233
* Title:接水问题
* Status:AC
* Tag:[模拟]
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    readi2(n,m);
    priority_queue<int, vector<int>, greater<int> > Q;
    int cur=0;
    int t;
    repne(i,0,m)
    {
        readi(t);
        Q.push(t);
    }
    repne(i,m,n)
    {
        cur=Q.top();
        Q.pop();
        readi(t);
        Q.push(cur+t);
    }
    repne(i,0,m)
    {
        cur=Q.top();
        Q.pop();
    }
    printf("%d\n",cur);
    return 0;
}