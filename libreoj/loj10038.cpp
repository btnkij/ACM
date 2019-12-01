/**
* Number:loj10038
* Title:「一本通 2.1 练习 4」A Horrible Poem 
* Status:AC
* Tag:[字符串哈希, 素数筛]
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

inline int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

int prime[500010], *tailp;
bool is_nonprime[500010];
int nxt[500010];
void init_prime(int n)
{
    tailp = prime;
    is_nonprime[0] = is_nonprime[1] = true;
    nxt[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(!is_nonprime[i])
        {
            *(tailp++) = i;
            nxt[i] = i;
        }
        for(int* iter = prime; iter != tailp; iter++)
        {
            int t = i * (*iter);
            if(t > n)break;
            is_nonprime[t] = true;
            nxt[t] = *iter;
            if(i % *iter == 0)break;
        }
    }
}

struct
{
    ull _hashc[500010], *hashc;
    const ull base = 13131;
    ull powb[500010] = {1};
    void init(char* s)
    {
        hashc = _hashc + 1;
        for(int i = 0; s[i]; i++)
        {
            powb[i + 1] = powb[i] * base;
            hashc[i] = hashc[i - 1] * base + s[i];
        }
    }
    ull range(int lt, int rt)
    {
        return hashc[rt] - hashc[lt - 1] * powb[rt - lt + 1];
    }
}Hash;

char s[500010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n = readu();
    reads(s);
    int q = readu();
    init_prime(n);
    Hash.init(s);
    while(q--)
    {
        int lt = readu() - 1, rt = readu() - 1;
        int len = rt - lt + 1;
        int ans = len;
        for(; len > 1; len /= nxt[len])
        {
            int t = ans / nxt[len];
            if(Hash.range(lt + t, rt) == Hash.range(lt, rt - t))
                ans = t;
            int f = nxt[len];
            while(len % f)len /= f;
        }
        printf("%d\n", ans);
    }
    return 0;
}