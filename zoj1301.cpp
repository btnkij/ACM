/**
* Number:zoj1301
* Title:The New Villa 
* Status:AC
* Tag:[bfs]
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

//手动实现队列, 可以保存出队的结点
struct Node
{
    int room, light, step; // 当前状态的房间号, 灯的开关情况, 步数
    int pre; // 前驱结点的下标
}Q[12*(1<<12)];
int head, tail; // 队列的首尾指针, tail是下一个结点的入队位置

int r, d, s; // 房间数, 门数, 开关数
bool door[12][12]; // door[i][j] == true 表示房间i有门通向房间j
bool sw[12][12]; // sw[i][j] == true 表示房间i有控制房间j中灯的开关

int state1; // 目标状态灯的位标识
bool vis[12][1<<12]; // (房间号, 灯的状态)是否在访问过
int bfs()
{
    vis[1][2] = true;
    Q[tail] = (Node){1, 2, 0, 0}; // 初始状态 room = 1, light = 1 << room, step = 0
    tail++; // 下一个结点的入队位置
    while(head != tail) // 当队列不为空
    {
        Node& node = Q[head];
        if(node.room == r && node.light == state1) // 如果是目标状态
            return head; // 返回当前结点的下标
        head++;
        for(int v = 1; v <= r; v++)
        {
            // 状态转移: 移动到下一个房间
            // 条件: node.room到v有门 and 房间v的灯是开着的 and 转移后的状态没有访问过
            if(door[node.room][v] && (node.light & (1<<v)) && !vis[v][node.light])
            {
                Node& nxt = Q[tail++];
                nxt = (Node){v, node.light, node.step + 1, &node - Q};
                vis[v][node.light] = true;
            }
            // 状态转移: 切换开关的状态
            // 条件: node.room有控制v房间灯的开关 and 转移后的状态没有访问过
            int flip = node.light ^ (1 << v); // 翻转位标识的第v位
            if(sw[node.room][v] && !vis[node.room][flip])
            {
                Node& nxt = Q[tail++];
                nxt = (Node){node.room, flip, node.step + 1, &node - Q};
                vis[node.room][flip] = true;
            }
        }
    }
    return -1; // 没有到达目标状态
}

void showPath(int idx)
{
    if(idx == 0)return;
    if(Q[idx].pre)showPath(Q[idx].pre); // 如果有前驱结点, 先打印前面的操作
    Node& cur = Q[idx];
    Node& pre = Q[cur.pre];
    printf("\n");
    if(pre.room != cur.room)
    {
        printf("- Move to room %d.", cur.room);
        return;
    }
    int room = 0; // 哪一个房间的灯被动过
    int light = pre.light ^ cur.light; // 异或用来获取pre.light和cur.light不同的那一位
    while(light > 1)
    {
        room++;
        light >>= 1;
    }
    if(pre.light < cur.light)
        printf("- Switch on light in room %d.", room);
    else
        printf("- Switch off light in room %d.", room);
}

int main()
{
#ifdef __DEBUG__
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
#endif
    int kase = 1;
    while(readi(r, d, s)!=EOF && (r|d|s))
    {
        state1 = 1 << r;
        head = tail = 0;
        mset(door, false); // 全局变量使用前记得初始化
        while(d--)
        {
            int i, j; readi(i, j);
            door[i][j] = door[j][i] = true;
        }
        mset(sw, false);
        while(s--)
        {
            int k, l; readi(k, l);
            if(k == l)continue;
            sw[k][l] = true;
        }
        mset(vis, false);
        int idx = bfs();
        printf("Villa #%d\n", kase++);
        if(idx == -1)
        {
            printf("The problem cannot be solved.");
        }
        else
        {
            printf("The problem can be solved in %d steps:", Q[idx].step);
            showPath(idx); // 如果步数为0不打印任何东西
        }
        printf("\n\n"); // 坑点: 末尾的换行必须保留
    }
    return 0;
}