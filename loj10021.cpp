/**
* Number:loj10021
* Title:「一本通 1.3 例 4」Addition Chains
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

int n, arr[20]={1,2}, len=2;
int ans, ans1[20];
void dfs()
{
    if(arr[len-1]==n)
    {
        if(len<ans)
        {
            copy(arr,arr+len,ans1);
            ans=len;
        }
        return;
    }
    for(int i=len-1; i>=0; i--)
    {
        int lb=arr[len-1]-arr[i];
        for(int j=i; j>=0 && arr[j]>=lb; j--)
        {
            int nxtl=arr[i]+arr[j];
            if(nxtl>n)continue;
            int k=0;
            while((nxtl<<k)<n)k++;
            if(len+k+1>=ans)break;
            arr[len++]=nxtl;
            dfs();
            len--;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n)!=EOF && n)
    {
        if(n==1)printf("1\n");
        else if(n==2)printf("1 2\n");
        else
        {
            ans=INF;
            dfs();
            repne(i,0,ans)
            {
                printf("%d ",ans1[i]);
            }
            printf("\n");
        }
    }
    return 0;
}