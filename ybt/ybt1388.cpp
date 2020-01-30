/**
* Number:ybt1388
* Title:家谱(gen)
* Status:AC
* Tag:[并查集, map]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <string>
#include <map>
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

map<string,string> fa;
string& find(string& x)
{
    return x==fa[x]?x:fa[x]=find(fa[x]);
}
void merge(string& x,string& y)
{
    string &rx=find(x),&ry=find(y);
    if(rx!=ry)
    {
        // cout<<"merge "<<x<<" "<<y<<endl;
        fa[ry]=rx;
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string pre,s;
    char op[4];
    while(scanf("%1s",op)!=EOF)
    {
        if(op[0]=='#')
        {
            cin>>pre;
            if(fa.find(pre)==fa.end())fa[pre]=pre;
        }
        else if(op[0]=='+')
        {
            cin>>s;
            if(fa.find(s)==fa.end())fa[s]=s;
            merge(pre,s);
        }
        else if(op[0]=='?')
        {
            cin>>s;
            cout<<s.c_str()<<' '<<find(s).c_str()<<endl;
        }
        else if(op[0]=='$')
        {
            break;
        }
    }
    return 0;
}