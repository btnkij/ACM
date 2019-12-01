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

char s[1000010];
int nxt[1000010];
void init_nxt(const char* T, int m)
{
    int a = 0, p = 0;
    nxt[0] = m;

    for (int i = 1; i < m; i++)
    {
        if (i >= p || i + nxt[i - a] >= p)
        {
            if (i >= p)
                p = i;

            while (p < m && T[p] == T[p - i])
                p++;

            nxt[i] = p - i;
            a = i;
        }
        else
            nxt[i] = nxt[i - a];
    }
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
        reads(s);
        int len=strlen(s);
        init_nxt(s,len);
        ll ans=0;
        for(int i=1;i<len;i++)
        {
            ans+=nxt[i]+(int)(nxt[i]!=len-i);
        }
        printf("%lld\n",ans);
    }
    return 0;
}