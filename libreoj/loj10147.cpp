/**
* Number:loj10147
* Title:「一本通 5.1 例 1」石子合并
* Status:AC
* Tag:[区间dp]
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

#define INF 0x3f3f3f3f3f3f3f3fLL
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

ll dpmax[410][410], dpmin[410][410];
ll sum[410];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(NULL);
    int n; cin>>n;
    rep(i,1,n)cin>>sum[i];
    copy(sum+1, sum+n+1, sum+n+1);
    rep(i,1,n<<1)sum[i]+=sum[i-1];
    for(int len=2;len<=n;len++)
    {
        for(int lt=1,rt=lt+len-1; rt<=n<<1; lt++,rt++)
        {
            dpmax[lt][rt]=-INF;
            dpmin[lt][rt]=INF;
            for(int mid=lt; mid+1<=rt; mid++)
            {
                dpmax[lt][rt]=max(
                    dpmax[lt][rt], 
                    dpmax[lt][mid]+dpmax[mid+1][rt]+sum[rt]-sum[lt-1]);
                dpmin[lt][rt]=min(
                    dpmin[lt][rt], 
                    dpmin[lt][mid]+dpmin[mid+1][rt]+sum[rt]-sum[lt-1]);
            }
        }
    }
    ll ansmax=-INF, ansmin=INF;
    for(int lt=1,rt=n; rt<=n<<1; lt++,rt++)
    {
        ansmax=max(ansmax, dpmax[lt][rt]);
        ansmin=min(ansmin, dpmin[lt][rt]);
    }
    cout<<ansmin<<endl<<ansmax;
    return 0;
}