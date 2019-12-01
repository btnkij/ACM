/**
* Number:
* Title:
* Status:?
* Tag:[]
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

struct Node
{
    int val, t;
    bool operator<(const Node& rhs)const
    {
        return t<rhs.t;
    }
}A[1000010],B[1000010],C[1000010];
Node *pa,*pb,*pc;
int la,lb;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    char op[8];
    int kase=1;
    int n;
    while(readi(n)!=EOF && n)
    {
        printf("Case #%d:\n",kase++);
        la=lb=0;
        pa=A,pb=B,pc=C;
        repne(timer,0,n)
        {
            reads(op);
            if(op[1]=='u') // push
            {
                reads(op);
                int t; readi(t);
                if(op[0]=='A')pa[la].t=timer,pa[la++].val=t;
                else if(op[0]=='B')pb[lb].t=timer,pb[lb++].val=t;
            }
            else if(op[1]=='o') // pop
            {
                reads(op);
                if(op[0]=='A')printf("%d\n",pa[--la]);
                else if(op[0]=='B')printf("%d\n",pb[--lb]);
            }
            else if(op[1]=='e') // merge
            {
                reads(op);
                if(op[0]=='A')
                {
                    merge(pa,pa+la,pb,pb+lb,pc);
                    la=la+lb;
                    lb=0;
                    swap(pa,pc);
                }
                else if(op[0]=='B')
                {
                    merge(pa,pa+la,pb,pb+lb,pc);
                    lb=lb+la;
                    la=0;
                    swap(pb,pc);
                }
                reads(op);
            }
        }
    }
    return 0;
}