/**
* Number:
* Title:
* Status:?
* Tag:[]
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
typedef int ll;
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

int p,a,b,tot;
int nb;
bool vis[30];
int damage[30];
int up,down;
void dfs(int n, int d)
{
    // printf("%d %d\n",n,d);
    if(n==0 || nb==0)
    {
        down++;
        if(d>=p)up++;
        return;
    }
    for(int i=0;i<tot;i++)
    {
        if(vis[i])continue;
        vis[i]=true;
        if(i<b)
        {
            nb--;
            dfs(n-1,d+damage[i]);
            nb++;
        }
        else dfs(n+2,d);
        vis[i]=false;
    }
}
int gcd(int a,int b)
{
    return b==0? a:gcd(b,a%b);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        up=down=0;
        readi(p,a,b);
        tot=a+b;
        nb=b;
        repne(i,0,b)readi(damage[i]);
        dfs(1,0);
        if(up==0)printf("0/1\n");
        else 
        {
            int d=gcd(up,down);
            printf("%d/%d\n",up/d,down/d);
        }
    }
    return 0;
}