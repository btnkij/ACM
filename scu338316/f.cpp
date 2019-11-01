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

char mat1[110][110],mat2[110][110];
bool vis[110][110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        repne(i,0,n)reads(mat1[i]);
        int oldx=0,oldy=0,newx=0,newy=0;
        int s1=0,s2=0;
        clr(vis,false);
        clr(mat2,0);
        repne2(i,0,n,j,0,n)
        {
            mat2[newx][newy]=mat1[oldx][oldy];
            vis[newx][newy]=true;
            switch(s1)
            {
                case 0:
                    if(oldy+1<n)oldy++;
                    else oldx++;
                    s1=1;
                    break;
                case 1:
                    oldx++,oldy--;
                    if(oldx==n-1 || oldy==0)s1=2;
                    break;
                case 2:
                    if(oldx+1<n)oldx++;
                    else oldy++;
                    s1=3;
                    break;
                case 3:
                    oldx--,oldy++;
                    if(oldx==0 || oldy==n-1)s1=0;
                    break;
            }
            switch(s2)
            {
                case 0:
                    newy++;
                    if(newy==n-1 || vis[newx][newy+1])s2=1;
                    break;
                case 1:
                    newx++;
                    if(newx==n-1 || vis[newx+1][newy])s2=2;
                    break;
                case 2:
                    newy--;
                    if(newy==0 || vis[newx][newy-1])s2=3;
                    break;
                case 3:
                    newx--;
                    if(newx==0 || vis[newx-1][newy])s2=0;
                    break;
            }
        }
        repne(i,0,n)printf("%s\n",mat2[i]);
    }
    return 0;
}