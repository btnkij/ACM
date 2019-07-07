#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

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

const ll INF=1e15;
struct Node
{
    ll pos;
    char val;
    bool operator<(ll rhs)
    {
        return pos<rhs;
    }
    bool operator==(const Node& rhs)const
    {
        return pos==rhs.pos && val==rhs.val;
    }
};
vector<Node> V[2];
void solve(int cur)
{
    vector<Node>& v=V[cur];
    v.push_back((Node){INF,0});
    char op[4];
    while(reads(op)!=EOF && op[0]!='E')
    {
        if(op[0]=='I')
        {
            ll pos;
            char ch[4];
            scanf("%lld %s",&pos,ch);
            auto ptr=lower_bound(v.begin(),v.end(),pos);
            for(auto it=ptr;it!=v.end();it++)
            {
                it->pos++;
            }
            v.insert(ptr,(Node){pos,ch[0]});
        }
        else if(op[0]=='D')
        {
            ll pos; scanf("%lld",&pos);
            auto tmp=lower_bound(v.begin(),v.end(),pos);
            if(tmp!=v.end() && tmp->pos!=pos+1 && tmp->pos!=pos)
            {
                v.insert(tmp,(Node){pos+1,0});
            }
            auto ptr=lower_bound(v.begin(),v.end(),pos);
            for(auto it=ptr;it!=v.end();it++)
            {
                it->pos--;
            }
            if(ptr!=v.end() && ptr->pos==pos-1)
            {
                v.erase(ptr);
            }
        }
    }
    // for(auto it:v)
    // {
    //     printf("(%lld %c) ",it.pos,it.pos);
    // }
    // printf("\n");
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    solve(0);
    solve(1);
    if(V[0]==V[1])printf("0");
    else printf("1");
    return 0;
}