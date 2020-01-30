/**
* Number:ybt1371
* Title:看病
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

#define readi(i1) scanf("%d", &i1)
#define readi2(i1, i2) scanf("%d %d", &i1, &i2)
#define readi3(i1, i2, i3) scanf("%d %d %d", &i1, &i2, &i3)
#define readi4(i1, i2, i3, i4) scanf("%d %d %d %d", &i1, &i2, &i3, &i4)
#define reads(s1) scanf("%s", s1)
#define mset(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

struct Node
{
    char* name;
    int prior;
    bool operator<(const Node& rhs)const
    {
        return prior<rhs.prior;
    }
};
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    priority_queue<Node> Q;
    int q; readi(q);
    char op[8];
    while(q--)
    {
        reads(op);
        if(op[1]=='u') // push
        {
            Node node;
            node.name=new char[30];
            reads(node.name);
            readi(node.prior);
            Q.push(node);
        }
        else if(op[1]=='o') // pop
        {
            if(Q.empty())printf("none\n");
            else
            {
                Node node=Q.top(); Q.pop();
                printf("%s %d\n", node.name, node.prior);
            }
        }
    }
    return 0;
}