/**
* Number:ybt1542, loj10120
* Title:【例 2】最敏捷的机器人
* Status:AC
* Tag:[单调队列]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <deque>
#include <stack>
using namespace std;

#define INF 0x3f3f3f3f
#define PI acos(-1)
typedef long long ll;

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

struct Node
{
    int val, idx;
};
deque<Node> Qmax,Qmin;
void enqueue(Node& node)
{
    while(!Qmax.empty() && Qmax.back().val<=node.val)
        Qmax.pop_back();
    Qmax.push_back(node);
    while(!Qmin.empty() && Qmin.back().val>=node.val)
        Qmin.pop_back();
    Qmin.push_back(node);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,k; readi(n,k);
    int cur=1;
    repne(i,1,k)
    {
        Node node;
        readi(node.val);
        node.idx=i;
        enqueue(node);
    }
    rep(i,k,n)
    {
        Node node;
        readi(node.val);
        node.idx=i;
        enqueue(node);
        while(Qmax.front().idx<cur)Qmax.pop_front();
        while(Qmin.front().idx<cur)Qmin.pop_front();
        printf("%d %d\n",Qmax.front().val, Qmin.front().val);
        cur++;
    }
    return 0;
}