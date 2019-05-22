/**
* Number:loj10244
* Title:「一本通 6.7 练习 1」取石子游戏
* Status:AC
* Tag:[sg函数, Sprague-Grundy]
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
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

int n,m,game[20],trans[20];
int dp[1010];
int mex(vector<int>& state)
{
    int ans=0;
    sort(state.begin(), state.end());
    for(int s:state)
    {
        if(ans == s)ans++;
        else if(ans < s)break;
    }
    return ans;
}
int sg(int g)
{
    if(~dp[g])return dp[g];
    vector<int> state;
    for(int i = 0; i < m && trans[i] <= g; i++)
    {
        state.push_back(sg(g - trans[i]));
    }
    return dp[g] = mex(state);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    mset(dp,-1);
    readi(n);
    repne(i,0,n)readi(game[i]);
    readi(m);
    repne(i,0,m)readi(trans[i]);
    int sum=0;
    // repne(i,0,11)printf("sg(%d)=%d\n",i,sg(i));
    repne(i,0,n)sum^=sg(game[i]);
    if(sum==0)printf("NO\n");
    else
    {
        printf("YES\n");
        repne(i,0,n)
        {
            sum^=sg(game[i]);
            for(int j=0; j<m && trans[j]<=game[i]; j++)
            {
                if((sum^sg(game[i]-trans[j]))==0)
                {
                    printf("%d %d\n",i+1,trans[j]);
                    return 0;
                }
            }
            sum^=sg(game[i]);
        }
    }
    return 0;
}