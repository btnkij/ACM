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

char s[100010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        reads(s+1);
        int len=strlen(s+1);
        bool ok=true;
        rep(i,1,len)
        {
            if(s[i]=='?')
            {
                if(s[i-1]!='a' && s[i+1]!='a')s[i]='a';
                else if(s[i-1]!='b' && s[i+1]!='b')s[i]='b';
                else if(s[i-1]!='c' && s[i+1]!='c')s[i]='c';
                else 
                {
                    ok=false;
                    break;
                }
            }
            else if(s[i]==s[i-1] || s[i]==s[i+1])
            {
                ok=false;
                break;
            }
        }
        if(ok)puts(s+1);
        else puts("-1");
    }
    return 0;
}