/**
* Number:loj10046
* Title:「一本通 2.2 练习 2」OKR-Periods of Words
* Status:AC
* Tag:[kmp]
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

int nxt[1000010];
ll sum;
void getNxt(char* s, int len)
{
    int pre=-1,cur=0;
    nxt[0]=-1;
    while(cur<len)
    {
        if(pre==-1||s[pre]==s[cur])
        {
            pre++, cur++;
            nxt[cur]=pre;
            if(nxt[pre]>0)nxt[cur]=nxt[pre];
            if(pre>0)
                sum+=cur-nxt[cur];
        }
        else
        {
            pre=nxt[pre];
        }
    }
}

char s[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int len; readi(len);
    reads(s);
    getNxt(s,len);
    printf("%lld",sum);
    return 0;
}