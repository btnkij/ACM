/**
* Number:D
* Title:看病要排队 
* Status:AC
* Tag:[优先队列]
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
    int id, prior; // ID, 优先级
    bool operator<(const Node& rhs)const
    {
        // 优先级大的排前面, 如果优先级相等, ID小的排前面
        return prior < rhs.prior || (prior == rhs.prior && id > rhs.id);
    }
};
priority_queue<Node> Q[4];
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n;
    while(readi(n) != EOF)
    {
        rep(i, 1, 3)
        {
            Q[i] = priority_queue<Node>(); // 清空优先队列
        }
        int id = 1;
        while(n--)
        {
            char op[8];
            int A, B;
            reads(op);
            if(op[0] == 'I') // IN
            {
                readi(A, B);
                Q[A].push((Node){id, B});
                id++;
            }
            else if(op[0] == 'O') // OUT
            {
                readi(A);
                if(Q[A].empty()) // 如果优先队列为空
                {
                    printf("EMPTY\n");
                }
                else // 否则优先级最高的病人出队
                {
                    printf("%d\n", Q[A].top().id);
                    Q[A].pop();
                }
                
            }
        }
    }
    return 0;
}