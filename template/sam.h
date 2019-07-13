/**
 * 
 * Suffix Automation 后缀自动机 SAM
 * 
**/

#include <cstring>

const int MAXN = 1e6 * 2 + 10;
struct SAM
{
    inline int _hash(char ch)
    {
        return ch - 'a';
    }
    struct State
    {
        int length, parent;
        int nxt[26];
    }dfa[MAXN];
    int size, last;
    void init()
    {
        size = 1;
        last = 0;
        dfa[0].length = 0;
        dfa[0].parent = -1;
    }
    void append(char ch)
    {
        int e = _hash(ch);
        int pre = last;
        int cur = size++;
        dfa[cur].length = dfa[last].length + 1;
        while(pre != -1 && !dfa[pre].nxt[e])
        {
            dfa[pre].nxt[e] = cur;
            pre = dfa[pre].parent;
        }
        if(pre == -1)
        {
            dfa[cur].parent = 0;
        }
        else
        {
            int origin = dfa[pre].nxt[e];
            if(dfa[pre].length + 1 == dfa[origin].length)
            {
                dfa[cur].parent = origin;
            }
            else
            {
                int clone = size++;
                dfa[clone].length = dfa[pre].length + 1;
                dfa[clone].parent = dfa[origin].parent;
                memcpy(dfa[clone].nxt, dfa[origin].nxt, sizeof(dfa[origin].nxt));
                dfa[cur].parent = dfa[origin].parent = clone;
                while(pre != -1 && dfa[pre].nxt[e] == origin)
                {
                    dfa[pre].nxt[e] = clone;
                    pre = dfa[pre].parent;
                }
            }
        }
        last = cur;
    }
};