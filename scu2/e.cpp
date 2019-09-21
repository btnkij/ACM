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

int n;
int mat1[32][32],mat2[32][32],tmp[32][32];
void rotate90()
{
    int k=0;
    for(int j=n-1;j>=0;j--)
    {
        for(int i=0;i<n;i++)
        {
            int ii=k/n, jj=k%n;
            k++;
            tmp[i][j]=mat2[ii][jj];
        }
    }
    memcpy(mat2,tmp,sizeof(mat2));
}
int check()
{
    int cnt=0;
    repne2(i,0,n,j,0,n)
    {
        if(mat1[i][j]==mat2[i][j])
        {
            cnt++;
        }
    }
    return cnt;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(readi(n)!=EOF && n)
    {
        repne2(i,0,n,j,0,n)readi(mat1[i][j]);
        repne2(i,0,n,j,0,n)readi(mat2[i][j]);
        int ans=check();
        rotate90();
        ans=max(ans,check());
        rotate90();
        ans=max(ans,check());
        rotate90();
        ans=max(ans,check());
        printf("%d\n",ans);
    }
    return 0;
}