#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;
typedef unsigned long long ull;

inline int readi(int& i1) { return scanf("%d", &i1); }
inline int readi(int& i1, int& i2) { return scanf("%d %d", &i1, &i2); }
inline int readi(int& i1, int& i2, int& i3) { return scanf("%d %d %d", &i1, &i2, &i3); }
inline int readi(int& i1, int& i2, int& i3, int& i4) { return scanf("%d %d %d %d", &i1, &i2, &i3, &i4); }
inline int reads(char* s1) { return scanf("%s", s1); }
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int dir[][3]={{-1,0,'U'},{1,0,'D'},{0,-1,'L'},{0,1,'R'}};
pair<int,int> mat[1010][1010];
char ans[1010][1010];
const pair<int,int> nul={-1,-1};
void bfs(int n,pair<int,int> src)
{
    queue<pair<int,int>> Q;
    Q.push(src);
    while(!Q.empty())
    {
        auto nod=Q.front(); Q.pop();
        repne(i,0,4)
        {
            int x=nod.first+dir[i][0],y=nod.second+dir[i][1];
            if(!(1<=x && x<=n && 1<=y && y<=n))continue;
            if(ans[x][y])continue;
            if(ans[src.first][src.second]!='X' && mat[x][y]==nul
             || ans[src.first][src.second]=='X' && mat[x][y]==src)
            {
                ans[x][y]=dir[i^1][2];
                Q.emplace(x,y);
            }
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    rep2(i,1,n,j,1,n)
    {
        auto& p=mat[i][j];
        readi(p.first,p.second);
        if(p.first==i && p.second==j)ans[i][j]='X';
    }
    rep2(i,1,n,j,1,n)if(ans[i][j]=='X')bfs(n,make_pair(i,j));
    rep2(i,1,n,j,1,n)
    {
        if(ans[i][j])continue;
        if(mat[i][j]!=nul)
        {
            puts("INVALID");
            return 0;
        }
        bool flag=false;
        repne(k,0,4)
        {
            int x=i+dir[k][0],y=j+dir[k][1];
            if(!(1<=x && x<=n && 1<=y && y<=n))continue;
            if(ans[x][y])continue;
            if(mat[x][y]==nul)
            {
                flag=true;
                ans[i][j]=dir[k][2];
                bfs(n,make_pair(i,j));
                break;
            }
        }
        if(!flag)
        {
            puts("INVALID");
            return 0;
        }
    }
    puts("VALID");
    rep(i,1,n)puts(ans[i]+1);
    return 0;
}