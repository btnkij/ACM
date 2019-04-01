/**
* Number:loj10036
* Title:「一本通 2.1 练习 2」Seek the Name, Seek the Fame 
* Status:ACs
* Tag:[扩展kmp]
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

struct extend_kmp
{
    int nxt[400010] /* 最长前缀 */, ext[400010];
    void init_nxt(const char* pat)
    {
        int p = 0, mx = 0, i;
        for(i = 1; pat[i]; i++)
        {      
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)nxt[i] = nxt[i - p];
            else
            {
                k = mx + 1;
                int j = i > mx ? 0 : k - p;
                while(pat[k] && pat[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                nxt[i] = k - i;
            }
        }
        nxt[0] = i;
    }
    void operator()(const char* dst, const char* pat)
    {
        int p, mx = -1, i;
        for(i = 0; dst[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)ext[i] = nxt[i - p];
            else
            {
                int k = mx + 1;
                int j = k - i;
                while(dst[k] && dst[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                ext[i] = k - i;
            }
        }
    }
}solver;

char s[400010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    while(reads(s)!=EOF)
    {
        int len=strlen(s);
        solver.init_nxt(s);
        for(int i=len-1;i>=0;i--)
        {
            if(solver.nxt[i]==len-i)printf("%d ",len-i);
        }
        printf("\n");
    }
    return 0;
}