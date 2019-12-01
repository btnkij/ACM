/**
* Number:loj10005
* Title:「一本通 1.1 练习 1」数列极差 
* Status:AC
* Tag:[贪心, priority_queue, 贪心队列]
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n)!=EOF && n)
    {
        priority_queue<int, vector<int>, less<int> > MaxQ;
        priority_queue<int, vector<int>, greater<int> > MinQ;
        repne(i,0,n)
        {
            int t; readi(t);
            MaxQ.push(t);
            MinQ.push(t);
        }
        while(MaxQ.size()>1)
        {
            int a=MaxQ.top(); MaxQ.pop();
            int b=MaxQ.top(); MaxQ.pop();
            MaxQ.push(a*b+1);
        }
        while(MinQ.size()>1)
        {
            int a=MinQ.top(); MinQ.pop();
            int b=MinQ.top(); MinQ.pop();
            MinQ.push(a*b+1);
        }
        printf("%d\n",MinQ.top()-MaxQ.top());
    }
    return 0;
}