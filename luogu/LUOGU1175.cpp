/**
* Number:LUOGU1175
* Title:表达式的转换
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

int prior(char op){
    switch(op){
        case '+':case '-':
            return 1;
        case '*':case '/':
            return 2;
        case '^':
            return 3;
    }
}
int main(){
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    vector<char> num, opt;
    string s;
    cin>>s;
    for(int i=0;i<s.length();i++){
        if(isdigit(s[i])){
            num.push_back(s[i]);
        }else if(s[i]!=')'){
            int p=prior(s[i]);
            if(opt.empty() || opt.back()=='(' || prior(opt.back())<p){
                opt.push_back(s[i]);
            }else{
                while(!opt.empty() && opt.back()!='(' && prior(opt.back())>=p){
                    num.push_back(opt.back());
                    opt.pop_back();
                }
                opt.push_back(s[i]);
            }
        }else{
            while(opt.back()!='('){
                num.push_back(opt.back());
                opt.pop_back();
            }
            opt.pop_back();
        }
    }
    while(!opt.empty()){
        num.push_back(opt.back());
        opt.pop_back();
    }
    vector<pair<bool,ll>> ans;
    for(int i=0;i<num.size();i++){
        if(isdigit(num[i]))ans.emplace_back(true,num[i]&0xF);
        else ans.emplace_back(false, num[i]);
    }
    while(true){
        for(int i=0;i<ans.size();i++){
            if(ans[i].first)printf("%lld ",ans[i].second);
            else printf("%c ",(char)ans[i].second);
        }
        puts("");
        if(ans.size()==1)break;
        int pos=find_if(ans.begin(),ans.end(),
            [](const pair<bool,ll>& it){
                return it.first==false;
        })-ans.begin();
        ll t;
        ll a=ans[pos-2].second, b=ans[pos-1].second;
        switch((char)ans[pos].second){
            case '+': t=a+b; break;
            case '-': t=a-b; break;
            case '*': t=a*b; break;
            case '/': t=a/b; break;
            case '^': t=(ll)pow(a,b); break;
        }
        ans[pos-2].second=t;
        ans.erase(ans.begin()+pos-1,ans.begin()+pos+1);
    }
    return 0;
}