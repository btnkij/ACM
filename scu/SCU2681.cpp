/**
* Number:scu2681
* Title:平方数 2
* Status:AC
* Tag:[贪心]
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

int pole[1010],tot;
bool squ[2010];
int dp[1010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for(int i=1;i*i<=2000;i++)
    {
        squ[i*i]=true;
    }
    for(int i=1;i<=1000;i++)
    {
        int tmp=INF, idx=-1;
        for(int j=0;j<tot;j++)
        {
            if(squ[i+pole[j]] && pole[j]<tmp)
            {
                tmp=pole[j];
                idx=j;
            }
        }
        if(idx==-1)
        {
            pole[tot++]=i;
        }
        else
        {
            pole[idx]=i;
        }
        dp[i]=tot;
    }
    int n;
    while(readi(n)!=EOF && n)
    {
        printf("%d\n",dp[n]);
    }
    return 0;
}