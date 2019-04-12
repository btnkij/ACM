/**
* Number:loj100001048
* Title:「一本通 2.2 练习 4」Censoring 
* Status:AC
* Tag:[字符串哈希]
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
typedef int ll;
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

const ull base=13131;
ull powb=1;
ull hashs[1000010], hasht;
int tail=0;
char s[1000010], t[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(s+1); reads(t+1);
    int lens=strlen(s+1), lent=strlen(t+1);
    rep(i,1,lent)
    {
        hasht=hasht*base+t[i];
        powb*=base;
    }
    rep(i,1,lens)
    {
        tail++;
        s[tail]=s[i];
        hashs[tail]=hashs[tail-1]*base+s[i];
        if(tail>=lent && hashs[tail]-hashs[tail-lent]*powb==hasht)
        {
            tail-=lent;
        }
    }
    s[tail+1]='\0';
    printf("%s",s+1);
    return 0;
}