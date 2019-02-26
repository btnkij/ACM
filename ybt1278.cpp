/**
* Number:ybt1278
* Title:复制书稿(book)
* Status:AC
* Tag:[二分, 贪心]
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

int m,k;
int num[504];
bool check(int n)
{
    int cnt=0, sum=0;
    int i=m-1;
    while(cnt<=k && i>=0)
    {
        if(sum+num[i]>n)
            sum=0,cnt++;
        else
            sum+=num[i],i--;
    }
    if(sum)cnt++;
    return i<0 && cnt<=k;
}
void showpath(int n, int k, int pre)
{
    if(pre==0)
    {
        if(k)
        {
            showpath(n,k-1,pre);
            printf("0 0\n");
        }
        return;
    }
    int sum=0;
    int i=pre-1;
    while(i>=0 && sum<=n)
    {
        sum+=num[i];
        i--;
    }
    i++;
    if(sum>n)i++;
    showpath(n,k-1,i);
    printf("%d %d\n",i+1,pre);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    readi2(m,k);
    int lt=0,rt=0;
    for(int i=0;i<m;i++)
    {
        readi(num[i]);
        lt=max(lt,num[i]);
        rt+=num[i];
    }
    while(lt<rt)
    {
        int mid=(lt+rt)>>1;
        if(!check(mid))lt=mid+1;
        else rt=mid;
    }
    showpath(lt, k, m);
    return 0;
}