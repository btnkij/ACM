#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <algorithm>
#include <vector>
#include <string>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

int hextodec(char ch1,char ch2)
{
    int n1,n2;
    if('0'<=ch1 && ch1<='9')n1=ch1&0xF;
    else n1=(ch1|0x20)-'a'+10;
    if('0'<=ch2 && ch2<='9')n2=ch2&0xF;
    else n2=(ch2|0x20)-'a'+10;
    return (n1<<4)|n2;
}
string rgb(const string& s)
{
    string color;
    if(s.length()==2)
    {
        string num=to_string(hextodec(s[1],s[1]));
        color+=num;
        color.push_back(';');
        color+=num;
        color.push_back(';');
        color+=num;
    }
    else if(s.length()==4)
    {
        color+=to_string(hextodec(s[1],s[1]));
        color.push_back(';');
        color+=to_string(hextodec(s[2],s[2]));
        color.push_back(';');
        color+=to_string(hextodec(s[3],s[3]));
    }
    else
    {
        color+=to_string(hextodec(s[1],s[2]));
        color.push_back(';');
        color+=to_string(hextodec(s[3],s[4]));
        color.push_back(';');
        color+=to_string(hextodec(s[5],s[6]));
    }
    return color;
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt","r",stdin);
    freopen("out.txt","w",stdout);
#endif
    int m,n,p,q;
    scanf("%d %d %d %d",&m,&n,&p,&q);
    m/=p, n/=q;
    string pre="";
    string cur;
    for(int i=0;i<n;i++)
    {
        for(int j=0;j<m;j++)
        {

        }
    }
    return 0;
}