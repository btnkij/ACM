/**
* Number:ybt1418
* Title:猴子选大王
* Status:AC
* Tag:[链表]
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

int readu()
{
    int num = 0;
    char ch;
    do{ ch = getchar(); }while(ch < '0' || ch > '9');
    do{ num = (num << 3) + (num << 1) + (ch & 0xF); ch = getchar(); }while('0' <= ch && ch <= '9');
    return num;
}

struct Node
{
    int x;
    Node *prev,*nxt;
}link[1000010];

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; n=readu();
    rep(i,1,n)
    {
        link[i].x=readu();
        link[i].prev=&link[i-1];
        link[i].nxt=&link[i+1];
    }
    link[1].prev=&link[n];
    link[n].nxt=&link[1];
    int x;
    Node* p=&link[1];
    while(n>1)
    {
        x=p->x-1;
        while(x)
        {
            p=p->nxt;
            x--;
        }
        n--;
        p->prev->nxt=p->nxt;
        p->nxt->prev=p->prev;
        p=p->nxt;
    }
    printf("%d",p-link);
    return 0;
}