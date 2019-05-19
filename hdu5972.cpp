/**
* Number:hdu5972
* Title:Regular Number
* Status:AC
* Tag:[shiftand, bitset]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <bitset>

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

inline int readu()
{
    register int num = 0;
    register char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

std::bitset<1010> mask[10];
std::bitset<1010> ans;
char s[5000100];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF)
    {
        repne(i,0,10)mask[i].reset();
        ans.reset();
        repne(i,0,n)
        {
            int a=readu();
            repne(j,0,a)
            {
                int b=readu();
                mask[b].set(i);
            }
        }
        gets(s);
        int len=strlen(s);
        repne(i,0,len)
        {
            ans<<=1;
            ans.set(0);
            ans&=mask[s[i]&0xF];
            if(ans.test(n-1))
            {
                int j=i+1;
                char tmp=s[j];
                s[j]='\0';
                puts(s+j-n);
                s[j]=tmp;
            }
        }
    }
    return 0;
}