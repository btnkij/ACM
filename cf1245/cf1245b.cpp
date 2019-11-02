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

char bob[110];
char alice[110];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int T; readi(T);
    while(T--)
    {
        int n,a,b,c; readi(n,a,b,c); // R P S
        reads(bob);
        int cntR=0,cntP=0,cntS=0;
        repne(i,0,n)
        {
            if(bob[i]=='R')cntR++;
            else if(bob[i]=='P')cntP++;
            else if(bob[i]=='S')cntS++;
        }
        int win=min(a,cntS)+min(b,cntR)+min(c,cntP);
        if(win>=(n+1)/2)
        {
            puts("YES");
            clr(alice,0);
            repne(i,0,n)
            {
                if(bob[i]=='R' && b)alice[i]='P',b--;
                else if(bob[i]=='P' && c)alice[i]='S',c--;
                else if(bob[i]=='S' && a)alice[i]='R',a--;
            }
            repne(i,0,n)if(!alice[i] && a)alice[i]='R',a--;
            repne(i,0,n)if(!alice[i] && b)alice[i]='P',b--;
            repne(i,0,n)if(!alice[i] && c)alice[i]='S',c--;
            puts(alice);
        }
        else puts("NO");
    }
    return 0;
}