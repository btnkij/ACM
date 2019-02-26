/**
* Number:uva11491
* Title:Erasing and Winning
* Status:AC
* Tag:[greedy]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <deque>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

char num[100004];
vector<char> v;
int main()
{
    int n,m;
    while(scanf("%d %d",&n,&m)!=EOF && n && m){
        scanf("%s",num);
        int len=n-m;
        v.clear();
        for(int i=0;i<n;i++)
        {
            while(v.size() && m && num[i] > v.back())
            {
                v.pop_back();
                m--;
            }
            if(v.size()<len)v.push_back(num[i]);
            else m--;
        }
        for(char ch : v)
            putchar(ch);
        putchar('\n');
    }
    return 0;
}