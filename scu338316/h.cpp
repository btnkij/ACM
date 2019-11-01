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

int sum[160<<2],lmax[160<<2],rmax[160<<2],allmax[160<<2];
void add(int p,int lt,int rt,int qpos,int qval)
{
    if(lt==rt)
    {
        sum[p]=lmax[p]=rmax[p]=allmax[p]=sum[p]+qval;
        return;
    }
    int mid=(lt+rt)>>1,lc=p<<1,rc=p<<1|1;
    if(qpos<=mid)add(lc,lt,mid,qpos,qval);
    else add(rc,mid+1,rt,qpos,qval);
    sum[p]=sum[lc]+sum[rc];
    lmax[p]=max(lmax[lc],sum[lc]+lmax[rc]);
    rmax[p]=max(rmax[rc],sum[rc]+rmax[lc]);
    allmax[p]=max(max(lmax[p],rmax[p]),rmax[lc]+lmax[rc]);
}
int mat[160][160];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m,p;
    while(readi(n,m,p)!=EOF)
    {
        rep2(i,1,n,j,1,m)readi(mat[i][j]);
        int ans=INF;
        rep(r,1,n)
        {
            clr(sum,0); clr(lmax,0); clr(rmax,0); clr(allmax,0);
            rep(j,1,m)add(1,1,m,j,mat[r][j]);
            ans=min(ans,allmax[1]);
            rep(i,r+1,n)
            {
                rep(j,1,m)add(1,1,m,j,mat[r][j]);
                ans=min(ans,allmax[1]);
            }
            rep2(i,r,n,j,1,m)
            {
                add(1,1,m,j,p-mat[i][j]);
                ans=min(ans,allmax[1]);
                add(1,1,m,j,mat[i][j]-p);
            }
        }
        printf("%d\n",ans);
    }
    return 0;
}