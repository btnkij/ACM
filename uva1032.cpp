/**
* Number:uva1032
* Title:Intersecting Dates
* Status:AC
* Tag:[模拟]
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

struct Date
{
    int year,month,day;
    // bool operator<(const Date& rhs)const
    // {
    //     return year<rhs.year 
    //     || year==rhs.year && month<rhs.month 
    //     || year==rhs.year && month==rhs.month && day<rhs.day;
    // }
};
inline bool isLeapYear(int year)
{
    return year%400==0 || year%100!=0 && year%4==0;
}
inline int dayOfYear(const Date& date)
{
    return 365+isLeapYear(date.year);
}
inline int dayOfMonth(const Date& date)
{
    if(date.month==2)return 28+isLeapYear(date.year);
    else return 30+((0x15AA>>date.month)&1);
}
int toTimestamp(const Date& date)
{
    Date d={1700,1,1};
    int ans=date.day-d.day;
    while(d.year<date.year)
    {
        ans+=dayOfYear(d);
        d.year++;
    }
    while(d.month<date.month)
    {
        ans+=dayOfMonth(d);
        d.month++;
    }
    // printf("%d %d %d -> %d\n",date.year,date.month,date.day,ans);
    return ans;
}
Date toDate(int timestamp)
{
    Date d={1700,1,1};
    while(timestamp>=dayOfYear(d))
    {
        timestamp-=dayOfYear(d);
        d.year++;
    }
    while(timestamp>=dayOfMonth(d))
    {
        timestamp-=dayOfMonth(d);
        d.month++;
    }
    d.day+=timestamp;
    return d;
}

struct Interval
{
    int left, right;
    bool operator<(const Interval& rhs)const
    {
        return left<rhs.left || left==rhs.left && right<rhs.right;
    }
    Interval operator-(const Interval& rhs)const
    {
        Interval ans=*this;
        if(left<=rhs.right && rhs.right<=right)ans.left=rhs.right+1;
        if(left<=rhs.left && rhs.left<=right)ans.right=rhs.left-1;
        return ans;
    }
};

Date readDate()
{
    char s[20];
    reads(s);
    repne(i,0,8)s[i]&=0xF;
    Date ans;
    ans.year=s[0]*1000+s[1]*100+s[2]*10+s[3];
    ans.month=s[4]*10+s[5];
    ans.day=s[6]*10+s[7];
    return ans;
}
vector<Interval> pre,cur;
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int n,m;
    int kase=1;
    while(readi(n,m)!=EOF && (n|m))
    {
        pre.clear();
        cur.clear();
        repne(i,0,n)
            pre.push_back({toTimestamp(readDate()), toTimestamp(readDate())});
        repne(i,0,m)
            cur.push_back({toTimestamp(readDate()), toTimestamp(readDate())});
        for(auto it:pre)
        {
            for(int i=0;i<cur.size();i++)
            {
                if(it.left<=cur[i].left && cur[i].right<=it.right)
                {
                    cur.erase(cur.begin()+i);
                    i--;
                }
                else if(cur[i].left<=it.left && it.right<=cur[i].right)
                {
                    if(cur[i].left==it.left)cur[i].left=it.right+1;
                    else if(cur[i].right==it.right)cur[i].right=it.left-1;
                    else
                    {
                        cur.insert(cur.begin()+i,cur[i]);
                        cur[i].right=it.left-1;
                        i++;
                        cur[i].left=it.right+1;
                    }
                }
                else if(cur[i].left<=it.left && it.left<=cur[i].right)
                {
                    cur[i].right=it.left-1;
                }
                else if(cur[i].left<=it.right && it.right<=cur[i].right)
                {
                    cur[i].left=it.right+1;
                }
            }
        }
        if(kase>1)putchar('\n');
        printf("Case %d:\n",kase++);
        if(cur.empty())
        {
            printf("    No additional quotes are required.\n");
        }
        else
        {
            sort(cur.begin(), cur.end());
            // for(auto it:cur)
            // {
            //     printf("%d %d\n",it.left,it.right);
            // }
            Interval t={0,-1};
            for(int i=0;i<cur.size();i++)
            {
                if(t.left>t.right)t=cur[i];
                if(i+1<cur.size() && t.right+1>=cur[i+1].left)
                    t.right=max(t.right,cur[i+1].right);
                else
                {
                    Date d=toDate(t.left);
                    printf("    %d/%d/%d",d.month,d.day,d.year);
                    if(t.left<t.right)
                    {
                        d=toDate(t.right);
                        printf(" to %d/%d/%d",d.month,d.day,d.year);
                    }
                    putchar('\n');
                    t={0,-1};
                }
            }
        }
    }
    return 0;
}