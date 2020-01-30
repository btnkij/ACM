/**
* Number:ybt1384
* Title:珍珠(bead)
* Status:AC
* Tag:[floyd]
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

bool adj[200][200];
void floyd(int n)
{
    rep(k,1,n)
    {
        rep2(i,1,n,j,1,n)
        {
            if(i!=j && adj[i][k] && adj[k][j])
                adj[i][j] = true;
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m; readi(n,m);
    repne(i,0,m)
    {
        int x,y; readi(x,y);
        adj[x][y]=1;
    }
    int ans=0,w=n/2;
    floyd(n);
    rep(i,1,n)
    {
        int cnt=0;
        rep(j,1,n) if(adj[i][j]) cnt++;
        if(cnt>w)ans++;
    }
    rep(i,1,n)
    {
        int cnt=0;
        rep(j,1,n) if(adj[j][i]) cnt++;
        if(cnt>w)ans++;
    }
    printf("%d",ans);
    return 0;
}