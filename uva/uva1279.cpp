/**
 * Number:uva1279
 * Title:Asteroid Rangers 
 * Status:?
 * Tag:[mst]
**/

#include <cstdio>
#include <iostream>
#include <algorithm>
#include <cmath>
#include <cstring>
#include <vector>
#include <queue>
using namespace std;

#define INF 0x3f3f3f3f
typedef long long ll;

const int MAXN = 54;
inline int square(int x) { return x * x; }
int SolveEquation(int a, int b, int c, double &x1, double &x2)
{
    if (a == 0)
    {
        if (b == 0)
            return 0;
        x1 = double(-c) / b;
        return 1;
    }
    int delta = b * b - 4 * a * c;
    if (delta < 0)
        return 0;
    if (delta == 0)
    {
        x1 = x2 = double(-b) / (2 * a);
        return 1;
    }
    x1 = (-b - sqrt(delta)) / (2 * a);
    x2 = (-b + sqrt(delta)) / (2 * a);
    return 2;
}

struct Point
{
    int x, y, z;
    int vx, vy, vz;
    void Read()
    {
        scanf("%d %d %d %d %d %d", &x, &y, &z, &vx, &vy, &vz);
    }
};
Point points[54];
int cntp;

struct Segment
{
    int a, b, c; //len=a*t^2+b*t+c
    int p1, p2;
    void Build(int p1, int p2)
    {
        this->p1 = p1;
        this->p2 = p2;
        Point &pos1 = points[p1];
        Point &pos2 = points[p2];
        a = square(pos1.vx - pos2.vx) + square(pos1.vy - pos2.vy) + square(pos1.vz - pos2.vz);
        b = ((pos1.x - pos2.x) * (pos1.vx - pos2.vx) + (pos1.x - pos2.x) * (pos1.vx - pos2.vx) + (pos1.x - pos2.x) * (pos1.vx - pos2.vx)) << 1;
        c = square(pos1.x - pos2.x) + square(pos1.y - pos2.y) + square(pos1.z - pos2.z);
    }
    bool operator<(const Segment &rhs) const
    {
        return this->c < rhs.c;
    }
};
Segment segs[MAXN * MAXN];
int cnts;

struct Event
{
    int t;
    int olde, newe;
    Event(int t, int olde, int newe)
    {
        this->t = t;
        this->olde = olde;
        this->newe = newe;
    }
    bool operator<(const Event &rhs)
    {
        return this->t < rhs.t;
    }
};
vector<Event> evts;

int mst[MAXN];
bool onMst[MAXN * MAXN];
int ufs[MAXN];
void init_mst()
{
    for (int i = 0; i < cntp; i++)
    {
        ufs[i] = i;
        onMst[i] = false;
    }
}
int findRoot(int x)
{
    return x == ufs[x] ? x : ufs[x] = findRoot(ufs[x]);
}
bool merge(int x, int y)
{
    int rx = findRoot(x);
    int ry = findRoot(y);
    if (rx == ry)
        return false;
    ufs[rx] = ry;
    return true;
}

int main()
{
    int kase = 1;
    while (scanf("%d", &cntp) != EOF)
    {
        cnts = 0;
        evts.clear();
        for (int i = 0; i < cntp; i++)
            points[i].Read();
        for (int i = 1; i < cntp; i++)
        {
            for (int j = 0; j < i; j++)
            {
                segs[cnts].Build(i, j);
                cnts++;
            }
        }
        sort(segs, segs + cnts);
        for (int i = 1; i < cnts; i++)
        {
            Segment &s1 = segs[i];
            for (int j = 0; j < i; j++)
            {
                Segment &s2 = segs[j];
                double t1, t2;
                int a = s1.a - s2.a, b = s1.b - s2.b, c = s1.c - s2.c;
                int nt = SolveEquation(a, b, c, t1, t2);
                if (nt == 1 && t1 > 0)
                {
                    if (b > 0)
                        evts.emplace_back(t1, i, j);
                    else
                        evts.emplace_back(t1, j, i);
                }
                else if (nt == 2 && t2 > 0)
                {
                    if (t1 > 0)
                    {
                        if (a > 0)
                            evts.emplace_back(t1, j, i);
                        else
                            evts.emplace_back(t1, i, j);
                    }
                    if (a > 0)
                        evts.emplace_back(t1, i, j);
                    else
                        evts.emplace_back(t1, j, i);
                }
            }
        }
        sort(evts.begin(), evts.end());
        int ans = 1;
        for (int i = 0; i < cntp; i++)
        {
            ufs[i] = i;
            onMst[i] = false;
        }
        int c = cntp - 1;
        for (int i = 0; i < cnts; i++)
        {
            Segment &e = segs[i];
            if (merge(e.p1, e.p2))
            {
                onMst[i] = true;
                c--;
                if (c == 0)
                    break;
            }
        }
        for (Event &evt : evts)
        {
            // Segment &olde = segs[evt.olde];
            if (!onMst[evt.olde] || onMst[evt.newe])
                continue;
            // Segment &newe = segs[evt.newe];
            c = cntp - 1;
            for (int i = 0; i < cnts; i++)
            {
                Segment &e = segs[i];
                if (merge(e.p1, e.p2))
                {
                    onMst[i] = true;
                    c--;
                    if (c == 0)
                        break;
                }
            }

            ans++;
        }
        printf("Case %d: %d\n", kase++, ans);
    }
    return 0;
}