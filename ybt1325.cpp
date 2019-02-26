/**
* Number:ybt1325
* Title:循环比赛日程表
* Status:AC
* Tag:[分治]
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

int tab[1010][1010];
void solve(int x,int y,int d,int w)
{
    if(w==1)
    {
        tab[x][y]=d;
        return;
    }
    int n=w>>1;
    solve(x,y,d,n);
    solve(x+n,y,d+n,n);
    repne2(i,0,n,j,0,n)
        tab[x+n+i][y+n+j]=tab[x+i][y+j];
    repne2(i,0,n,j,0,n)
        tab[x+i][y+n+j]=tab[x+n+i][y+j];
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m; readi(m);
    int w=1<<m;
    solve(0,0,1,w);
    repne(i,0,w)
    {
        repne(j,0,w)
        {
            printf("%d ",tab[i][j]);
        }
        printf("\n");
    }
    return 0;
}