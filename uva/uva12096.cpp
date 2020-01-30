/**
* Number:uva12096
* Title:The SetStack Computer
* Status:AC
* Tag:[模拟, stl, set, inserter]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <map>
#include <set>
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

const set<int> EMPTY=set<int>();
map<set<int>,int> id;
vector<set<int> > rid;
int getid(const set<int>& S)
{
    if(id.count(S))return id[S];
    else
    {
        rid.push_back(S);
        return id[S]=rid.size()-1;
    }
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    vector<int> st;
    int T; readi(T);
    while(T--)
    {
        st.clear();
        int n; readi(n);
        while(n--)
        {
            char op[16]; reads(op);
            if(op[0]=='P') // PUSH
            {
                st.push_back(getid(EMPTY));
            }
            else if(op[0]=='D') // DUP
            {
                st.push_back(st.back());
            }
            if(op[0]=='U') // UNION
            {
                auto S1=rid[st.back()]; st.pop_back();
                auto S2=rid[st.back()]; st.pop_back();
                set<int> ans;
                set_union(S1.begin(),S1.end(),S2.begin(),S2.end(),inserter(ans,ans.begin()));
                int id=getid(ans);
                st.push_back(id);
            }
            if(op[0]=='I') // INTERSECT
            {
                auto S1=rid[st.back()]; st.pop_back();
                auto S2=rid[st.back()]; st.pop_back();
                set<int> ans;
                set_intersection(S1.begin(),S1.end(),S2.begin(),S2.end(),inserter(ans,ans.begin()));
                int id=getid(ans);
                st.push_back(id);
            }
            if(op[0]=='A') // ADD
            {
                auto S1=rid[st.back()]; st.pop_back();
                auto S2=rid[st.back()]; st.pop_back();
                S2.insert(getid(S1));
                int id=getid(S2);
                st.push_back(id);
            }
            printf("%d\n",rid[st.back()].size());
        }
        puts("***");
    }
    return 0;
}