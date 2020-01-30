/**
* Number:ybt1395
* Title:烦人的幻灯片(slides)
* Status:AC
* Tag:[暴力]
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

struct Slide
{
    int xmin,xmax,ymin,ymax;
}slide[40];
struct Point
{
    int x,y;
}point[40];
bool adj[40][40];

int cnt[40],ord[40];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    repne(i,0,n)
    {
        Slide& s=slide[i];
        readi(s.xmin, s.xmax, s.ymin, s.ymax);
    }
    repne(i,0,n)
    {
        Point& p=point[i];
        readi(p.x, p.y);
        repne(j,0,n)
        {
            Slide& s=slide[j];
            if(s.xmin<=p.x && p.x<=s.xmax && s.ymin<=p.y && p.y<=s.ymax)
            {
                adj[j][i]=true;
                cnt[j]++;
            }
        }
    }
    int match=0;
    repne(m,0,n)
    repne(i,0,n)
    {
        if(cnt[i]==1)
        {
            int k;
            for(k=0;k<n;k++)
                if(adj[i][k])break;
            match++;
            ord[i]=k;
            repne(j,0,n)
            {
                if(adj[j][k])
                {
                    cnt[j]--;
                    adj[j][k]=false;
                }
            }
        }
    }
    if(match<n)printf("None");
    else
    {
        repne(i,0,n)
        {
            if(i)printf("\n");
            printf("%c %d",'A'+i,ord[i]+1);
        }
    }
    return 0;
}