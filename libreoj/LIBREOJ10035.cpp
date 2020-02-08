/**
* Number:loj10035
* Title:「一本通 2.1 练习 1」Power Strings 
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
typedef int ll;

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

int nxt[1000100];
void init_nxt(char* s, int len)
{
    nxt[0]=-1;
    int pre=0,cur=1;
    while(cur<len)
    {
        if(pre==-1 || s[cur]==s[pre])
        {
            cur++, pre++;
            nxt[cur]=pre;
        }
        else
        {
            pre=nxt[pre];
        }
    }
}

char s[1000100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(reads(s)!=EOF && !(s[0]=='.' && s[1]=='\0'))
    {
        int len=strlen(s);
        init_nxt(s,len);
        if((nxt[len]<<1)>=len && len%(len-nxt[len])==0)
            printf("%d\n",len/(len-nxt[len]));
        else
            printf("1\n");
    }
    return 0;
}