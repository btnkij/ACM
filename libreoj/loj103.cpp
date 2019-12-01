/**
* Number:loj103
* Title:子串查找 
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

int ans;
struct kmp
{
    int nxt[1000010];
    void init_nxt(const char* pat)
    {
        int pre = -1, cur = 0;
        nxt[0] = -1;
        while(pat[cur])
        {
            if(pre == -1 || pat[pre] == pat[cur])
            {
                pre++, cur++;
                nxt[cur] = (pat[pre] == pat[cur] ? nxt[pre] : pre); // next数组优化，表示最终回退位置
                // nxt[cur] = pre; //不优化，表示最大前后缀长度
            }
            else
            {
                pre = nxt[pre];
            }
        }
    }
    void operator()(const char* dst, const char* pat)
    {
        int i = 0, j = 0;
        while(dst[i])
        {
            if(j == -1 || dst[i] == pat[j])
            {
                i++, j++;
                if(pat[j] == '\0')
                {
                    // 匹配dst[i-j:i-1]
                    j=nxt[j];
                    ans++;
                }
            }
            else j = nxt[j];
        }
    }
}solver;

char a[1000010], b[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    reads(a); reads(b);
    solver.init_nxt(b);
    solver(a,b);
    printf("%d",ans);
    return 0;
}