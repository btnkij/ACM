/**
* Number:HDU2161
* Title:Primes
* Status:AC
* Tag:[数论, 质数判断]
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
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int MAXN=16100;
int prime[MAXN], *tailp;
bool is_nonprime[MAXN];
int nxt[MAXN]; // nxt[i]: i的最小质因子
void init_prime(int n)
{
    tailp = prime;
    is_nonprime[0] = is_nonprime[1] = true;
    nxt[1] = 1;
    for(int i = 2; i <= n; i++)
    {
        if(!is_nonprime[i])
            *(tailp++) = nxt[i] = i;
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    init_prime(MAXN-10);
    is_nonprime[1]=is_nonprime[2]=true;
    int n;
    int kase=1;
    while(readi(n)!=EOF && n>0)
    {
        if(is_nonprime[n])printf("%d: no\n",kase++);
        else printf("%d: yes\n",kase++);
    }
    return 0;
}