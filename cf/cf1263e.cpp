#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
using namespace std;

#define INF 0x3f3f3f3f
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

struct Stack
{
    vector<int> seq,summax,summin;
    int sum;
    void push(int x)
    {
        sum+=x;
        seq.push_back(x);
        summax.push_back(max(summax.back(),sum));
        summin.push_back(min(summin.back(),sum));
    }
    void pop()
    {
        sum-=seq.back();
        seq.pop_back();
        summax.pop_back();
        summin.pop_back();
    }
}lseq,rseq;
char op[1000010],s[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; scanf("%d %s",&n,op);
    int p=0;
    repne(i,0,n)
    {
        switch(op[i])
        {
        case 'L':
            if(p)
            {
                p--;
                if(s[p]=='(' || s[p]==')')
                {
                    rseq.push(s[p]=='('?1:-1);
                    lseq.pop();
                }
            }
            break;
        case 'R':
            if(s[p]=='(' || s[p]==')')
            {
                lseq.push(s[p]=='('?-1:1);
                if(!rseq.seq.empty())rseq.pop();
            }
            break;
        case '(':
            if(!rseq.seq.empty())rseq.pop();
            rseq.push(1);
            break;
        case ')':
            if(!rseq.seq.empty())rseq.pop();
            rseq.push(-1);
            break;
        default:
            break;
        }
        
    }
    return 0;
}