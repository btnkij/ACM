/**
 * 
 * sg函数
 * 
**/

#include <algorithm>
#include <vector>

int m, trans[20]; // 状态转移
int dp[1010]; // 记忆化，存sg(i)
int mex(std::vector<int>& state)
{
    int ans=0;
    std::sort(state.begin(), state.end());
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
    std::vector<int> state;
    for(int i = 0; i < m && trans[i] <= g; i++)
    {
        state.push_back(sg(g - trans[i]));
    }
    return dp[g] = mex(state);
}