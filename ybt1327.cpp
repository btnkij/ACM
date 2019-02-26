/**
* Number:ybt1327
* Title:黑白棋子的移动
* Status:AC
* Tag:[构造]
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

char s[1000010];
int step=1;
void move(int from, int to)
{
    s[to]=s[from], s[to+1]=s[from+1];
    s[from]=s[from+1]='-';
    printf("step%2d:%s\n",step++,s);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)s[i]='o';
    repne(i,n,n<<1)s[i]='*';
    s[n<<1]=s[(n<<1)+1]='-';
    printf("step 0:%s\n",s);
    while(n>=4)
    {
        move(n-1, n<<1);
        if(n>4)move((n<<1)-2, n-1);
        n--;
    }
    move(7,3);
    move(1,7);
    move(6,1);
    move(0,6);
    return 0;
}