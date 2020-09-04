/**
* Number:LUOGU2251
* Title:质量检测
* Status:AC
* Tag:[堆]
**/

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

struct Heap
{
    priority_queue<int, vector<int>, greater<int>> open, close;
    void push(int x)
    {
        open.push(x);
    }
    void pop(int x)
    {
        close.push(x);
    }
    int top()
    {
        while(!close.empty() && close.top()==open.top())
        {
            open.pop();
            close.pop();
        }
        return open.top();
    }
};

int arr[1000010];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    scanf("%d %d",&n,&m);
    Heap heap;
    for(int i=0;i<n;i++)scanf("%d",arr+i);
    for(int i=0;i<m;i++)heap.push(arr[i]);
    printf("%d\n",heap.top());
    for(int i=m;i<n;i++)
    {
        heap.pop(arr[i-m]);
        heap.push(arr[i]);
        printf("%d\n",heap.top());
    }
    return 0;
}