/**
* Number:loj104
* Title:普通平衡树 
* Status:AC
* Tag:[平衡树, treap]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <cassert>
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

struct Treap
{
    int data;
    int value;
    int left;
    int right;
    int siz;
};
Treap t[100005];
int cnt;
int root;
void up(int x)
{
    t[x].siz=t[t[x].left].siz+t[t[x].right].siz+1;
}
void right_rorate(int &now)
{
    int tmp=t[now].left;
    t[now].left=t[tmp].right;
    t[tmp].right=now;
    t[tmp].siz=t[now].siz;
    up(now);
    now=tmp;
}
void left_rorate(int &now)
{
    int tmp=t[now].right;
    t[now].right=t[tmp].left;
    t[tmp].left=now;
    t[tmp].siz=t[now].siz;
    up(now);
    now=tmp;
}
void insert(int &now,int data)
{
    if(now==0)
    {
        now=++cnt;
        t[now].siz=1;
        t[now].data=data;
        t[now].value=rand()*rand()%19620817;
        return ;
    }
    t[now].siz++;
    if(data>=t[now].data)
    {
        insert(t[now].right,data);
    }
    else
    {
        insert(t[now].left,data);
    }
    if(t[now].left!=0&&t[now].value>t[t[now].left].value)
    {
        right_rorate(now);
    }
    if(t[now].right!=0&&t[now].value>t[t[now].right].value)
    {
        left_rorate(now);
    }
    up(now);
}
void erase(int &now,int data)
{
    t[now].siz--;
    if(t[now].data==data)
    {
        if(t[now].left==0&&t[now].right==0)
        {
            now=0;
            return ;
        }
        if(t[now].left==0||t[now].right==0)
        {
            now=t[now].left+t[now].right;
            return ;
        }
        if(t[t[now].left].value<t[t[now].right].value)
        {
            right_rorate(now);
            erase(t[now].right,data);
            return ;
        }
        else
        {
            left_rorate(now);
            erase(t[now].left,data);
            return ;
        }
    }
    if(t[now].data>=data)
    {
        erase(t[now].left,data);
    }
    else
    {
        erase(t[now].right,data);
    }
    up(now);
}
int Rank(int now,int data)
{
    if(now==0)
    {
        return 0;
    }
    if(data>t[now].data)
    {
        return t[t[now].left].siz+1+Rank(t[now].right,data);
    }
    return Rank(t[now].left,data);
}
int find(int now,int rk)
{
    if(rk==t[t[now].left].siz+1)
    {
        return t[now].data;
    }
    if(rk>t[t[now].left].siz+1)
    {
        return find(t[now].right,rk-t[t[now].left].siz-1);
    }
    return find(t[now].left,rk);
}
int query_pre(int now,int data)
{
    if(now==0)
    {
        return 0;
    }
    if(t[now].data>=data)
    {
        return query_pre(t[now].left,data);
    }
    int tmp=query_pre(t[now].right,data);
    if(tmp==0)
    {
        return t[now].data;
    }
    return tmp;
}
int query_suf(int now,int data)
{
    if(now==0)
    {
        return 0;
    }
    if(t[now].data<=data)
    {
        return query_suf(t[now].right,data);
    }
    int tmp=query_suf(t[now].left,data);
    if(tmp==0)
    {
        return t[now].data;
    }
    return tmp;
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n; readi(n);
    while(n--)
    {
        int op, val; readi(op,val);
        switch(op)
        {
            case 1:
            insert(root, val);
            break;
            case 2:
            erase(root,val);
            break;
            case 3:
            printf("%d\n", Rank(root,val)+1);
            break;
            case 4:
            printf("%d\n", find(root,val));
            break;
            case 5:
            printf("%d\n",query_pre(root,val));
            break;
            case 6:
            printf("%d\n",query_suf(root,val));
            break;
        }
    }
    return 0;
}