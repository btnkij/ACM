/**
* Number:loj10020
* Title:「一本通 1.3 例 3」小木棍
* Status:AC
* Tag:[dfs]
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

int arr[80];
int len[80], cnt[80], tot;
int m, L;
bool dfs(int n, int l, int pre)
{
    if(n==0)return true;
    for(int i=pre;i<=tot;i++)
    {
        if(cnt[i]==0 || len[i]>l)continue;
        cnt[i]--;
        if(l==len[i] && dfs(n-1, L, 1))return true;
        else if(dfs(n, l-len[i], i))return true;
        cnt[i]++;
        if(pre==1 && l==L)return false;
        if(l==len[i])return false;
    }
    return false;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    int lt=-INF, rt=0;
    repne(i,0,n)
    {
        int t; readi(t);
        arr[i]=t;
        lt=max(lt, t);
        rt+=t;
    }
    int pre=-1;
    sort(arr, arr+n, greater<int>());
    repne(i,0,n)
    {
        if(arr[i]!=pre)
        {
            pre=arr[i];
            len[++tot]=arr[i];
            cnt[tot]=1;
        }
        else
        {
            cnt[tot]++;
        }
    }
    int ub=rt>>1;
    int ans=rt;
    rep(i,lt,ub)
    {
        if(rt%i==0)
        {
            m=rt/i, L=i;
            if(dfs(m, L, 1))
            {
                ans=i;
                break;
            }
        }
    }
    printf("%d",ans);
    return 0;
}