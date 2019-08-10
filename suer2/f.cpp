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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

// struct Node
// {
//     ll val;
//     int idx;
// };
// struct cmp1
// {
//     bool operator()(const Node& lhs, const Node& rhs)
//     {
//         return lhs.val < rhs.val;
//     }
// };
// struct cmp2
// {
//     bool operator()(const Node& lhs, const Node& rhs)
//     {
//         return lhs.val > rhs.val;
//     }
// };
int w[100010];
char a[100010],b[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)w[i];
    reads(a);
    reads(b);
    priority_queue<ll> Max;
    priority_queue<ll,vector<ll>,greater<ll> > Min;
    ll ans=0,sum=0;
    repne(i,0,n)
    {
        if(a[i]=='1' && b[i]=='0')
        {
            Max.push(w[i]);
            sum+=w[i];
        }
    }
    while(!Max.empty())
    {
        ans+=Max.top()
    }
    return 0;
}