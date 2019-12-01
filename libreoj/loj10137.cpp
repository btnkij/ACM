/**
* Number:loj10137
* Title:「一本通 4.4 练习 4」跳跳棋 
* Status:AC
* Tag:[lca, 二分]
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
    int a,b,c;
    bool operator==(const Node& rhs)
    {
        return a==rhs.a && b==rhs.b && c==rhs.c;
    }
};

Node getfa(const Node& cur, int maxlev, int& lev)
{
    Node node = cur;
    int k;
    for(lev=0; lev<maxlev; lev+=k)
    {
        int lab=node.b-node.a, lbc=node.c-node.b;
        if(lab == lbc)break;
        if(lab < lbc)
        {
            k = min(maxlev-lev, (lbc-1)/lab);
            node.b=node.c-(lbc-lab*k);
            node.a=node.b-lab;
        }
        else
        {
            k = min(maxlev-lev, (lab-1)/lbc);
            node.b=node.a+(lab-lbc*k);
            node.c=node.b+lbc;
        }
    }
    return node;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    Node x,y;
    readi(x.a,x.b,x.c);
    readi(y.a,y.b,y.c);
    sort((int*)&x,(int*)&x+3);
    sort((int*)&y,(int*)&y+3);
    int dep1, dep2;
    if(getfa(x,INF,dep1)==getfa(y,INF,dep2))
    {
        if(dep1<dep2)
        {
            swap(x,y);
            swap(dep1,dep2);
        }
        int diff=dep1-dep2;
        x=getfa(x,dep1-dep2,dep1);
        int lt=0, rt=dep2;
        while(lt<rt)
        {
            int mid=(lt+rt)>>1;
            if(getfa(x,mid,dep1)==getfa(y,mid,dep2))rt=mid;
            else lt=mid+1;
        }
        printf("YES\n%d",diff+lt*2);
    }
    else
    {
        printf("NO");
    }
    return 0;
}