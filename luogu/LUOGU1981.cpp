/**
* Number:LUOGU1981
* Title:表达式求值
* Status:AC
* Tag:[栈]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <queue>
#include <cassert>
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

constexpr int MOD=10000;
void calc(vector<int>& num, vector<char>& opt)
{
    int t1=num.back();
    num.pop_back();
    int t2=num.back();
    num.pop_back();
    char x=opt.back();
    opt.pop_back();
    if(x=='*')num.push_back(t1*t2%MOD);
    else if(x=='+')num.push_back((t1+t2)%MOD);
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    string s;
    cin>>s;
    vector<int> num;
    vector<char> opt;
    int i=0;
    while(i<s.length())
    {
        if(isdigit(s[i]))
        {
            int t=0;
            while(i<s.length() && isdigit(s[i]))
            {
                t=t*10+(s[i]&0xF);
                i++;
            }
            num.push_back(t%MOD);
        }
        else
        {
            while(!opt.empty() && !(opt.back()=='+' && s[i]=='*'))
                calc(num,opt);
            opt.push_back(s[i]);
            i++;
        }
    }
    while(!opt.empty())calc(num,opt);
    printf("%d\n",num.front());
    return 0;
}