/**
* Number:aizu0121
* Title:Seven Puzzle
* Status:AC
* Tag:[bfs, map]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cstring>
#include <queue>
#include <string>
#include <map>
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
#define clr(mem, val) memset(mem, val, sizeof(mem))
#define rep(i, begin, end) for (register int i = (begin); i <= (end); i++)
#define rep2(i1, begin1, end1, i2, begin2, end2) rep(i1, begin1, end1) rep(i2, begin2, end2)
#define repne(i, begin, end) for (register int i = (begin); i < (end); i++)
#define repne2(i1, begin1, end1, i2, begin2, end2) repne(i1, begin1, end1) repne(i2, begin2, end2)

const int dir[]={-1,1,-4,4};
map<string,int> ans;
struct Node
{
    string state;
    int step;
};
void bfs()
{
    queue<Node> Q;
    Q.push({"01234567",0});
    ans["01234567"]=0;
    while(!Q.empty())
    {
        Node cur=Q.front();
        Q.pop();
        int p=cur.state.find_first_of('0');
        for(int i=0;i<4;i++)
        {
            if(p%4==0 && dir[i]==-1)continue;
            if(p%4==3 && dir[i]==1)continue;
            if(p<4 && dir[i]==-4)continue;
            if(p>=4 && dir[i]==4)continue;
            Node nxt=cur;
            swap(nxt.state[p],nxt.state[p+dir[i]]);
            if(ans.count(nxt.state)==0)
            {
                nxt.step++;
                Q.push(nxt);
                ans[nxt.state]=nxt.step;
            }
        }
    }
}
int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    ios::sync_with_stdio(false); cin.tie(0);
    bfs();
    string state;
    int num;
    while(cin>>num)
    {
        state.clear();
        state.push_back(num|0x30);
        for(int i=1;i<8;i++)
        {
            cin>>num;
            state.push_back(num|0x30);
        }
        printf("%d\n",ans[state]);
    }
    return 0;
}