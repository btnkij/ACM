/**
* Number:loj2452
* Title:「POI2010」反对称 Antisymmetry 
* Status:AC
* Tag:[manacher]
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
typedef unsigned long long ull;

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

struct manacher
{
    char s[2000100];
    int palin[2000100];
    void loadString(const char* str)
    {
        char* p = s;
        *(p++) = '#';
        const char* q = str;
        while(*q)
        {
            *(p++) = *(q++);
            *(p++) = '#';
        }
    }
    void init()
    {
        int p, far = 0;
        for(int i = 0; s[i]; i++)
        {
            int lt, rt;
            if(i < far)rt = min(i + palin[(p << 1) - i] - 1, far);
            else rt = i;
            lt = (i << 1) - rt;
            // while(lt >= 0 && s[lt] == s[rt])lt--, rt++;
            while(lt >= 0 
            && (
                (s[lt] == '#' && s[rt] == '#') 
                || (s[lt]^s[rt])==1
            ))
                lt--, rt++;
            if(rt - 1 > far)
            {
                far = rt - 1;
                p = i;
            }
            palin[i] = rt - i;
            // printf("%d ",palin[i]);
        }
    }
}solver;
char num[500010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    reads(num);
    solver.loadString(num);
    // printf("%s\n",solver.s);
    solver.init();
    // printf("\n");
    ll ans=0;
    n--;
    for(int i=2;n;i+=2)
    {
        ans+=solver.palin[i]>>1;
        n--;
    }
    printf("%lld",ans);
    return 0;
}