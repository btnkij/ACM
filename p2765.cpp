/**
* Number:p2765
* Title:魔术球问题
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

const int MAXN=4000;
int num[60][MAXN],tot,tail[60];
bool squ[MAXN];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    for(int i=1;i*i<MAXN;i++)squ[i*i]=true;
    int n; readi(n);
    int m=1;
    while(true)
    {
        int i=0;
        for(;i<tot;i++)
            if(squ[ num[i][tail[i]] + m ])break;
        if(i==tot)
        {
            if(tot==n)break;
            tot++;
            num[i][0]=m;
        }
        else
        {
            num[i][++tail[i]]=m;
        }
        m++;
    }
    printf("%d\n",m-1);
    repne(i,0,n)
    {
        if(i)putchar('\n');
        rep(j,0,tail[i])printf("%d ",num[i][j]);
    }
    return 0;
}