/**
* Number:uva156
* Title:Ananagrams
* Status:AC
* Tag:[模拟, map]
**/

#include <cstdio>
#include <iostream>
#include <cstring>
#include <cmath>
#include <algorithm>
#include <numeric>
#include <vector>
#include <string>
#include <map>
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

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(nullptr);
    map<string,string> dict;
    string word;
    while(cin>>word && word!="#")
    {
        string norm=word;
        transform(norm.begin(),norm.end(),norm.begin(),[](char ch){
            return tolower(ch);
        });
        sort(norm.begin(),norm.end());
        auto it=dict.find(norm);
        if(it!=dict.end())it->second="#";
        else dict[norm]=word;
    }
    vector<string> ans;
    for(auto it:dict)
    {
        if(it.second!="#")ans.push_back(it.second);
    }
    sort(ans.begin(),ans.end());
    for(auto it:ans)cout<<it<<endl;
    return 0;
}