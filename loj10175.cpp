/**
* Number:loj10175
* Title:「一本通 5.5 例 1」滑动窗口
* Status:AC
* Tag:[单调队列]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <deque>
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

struct Node
{
    int val,idx;
};
int arr[1000010];
deque<Node> Q;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    repne(i,0,n)readi(arr[i]);
    repne(i,0,n)
    {
        while(!Q.empty() && Q.front().idx<=i-k)Q.pop_front();
        while(!Q.empty() && Q.back().val>=arr[i])Q.pop_back();
        Q.push_back((Node){arr[i],i});
        if(i>=k-1)printf("%d ",Q.front().val);
    }
    printf("\n");
    Q.clear();
    repne(i,0,n)
    {
        while(!Q.empty() && Q.front().idx<=i-k)Q.pop_front();
        while(!Q.empty() && Q.back().val<=arr[i])Q.pop_back();
        Q.push_back((Node){arr[i],i});
        if(i>=k-1)printf("%d ",Q.front().val);
    }
    return 0;
}