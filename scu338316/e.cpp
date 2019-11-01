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

int c[110],t[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int m,n,x;
    while(readi(m,n,x)!=EOF)
    {
        repne(i,0,n)readi(c[i]);
        sort(c,c+n);
        clr(t,0);
        while(x>0)
        {
            int elapse=x;
            repne(i,0,n)
            {
                if(m && !t[i])
                {
                    t[i]=c[i];
                    m--;
                }
                if(t[i])elapse=min(elapse,t[i]);
            }
            x-=elapse;
            repne(i,0,n)if(t[i])t[i]-=elapse;
        }
        int tot=0;
        repne(i,0,n)
        {
            if(0<t[i] && t[i]<c[i])tot++;
            else if(t[i]==c[i])m++;
        }
        printf("%d %d\n",m,tot);
    }
    return 0;
}