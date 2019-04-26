/**
 * 
 * Trie 字典树
 * 
**/

#include <cstring>

struct Trie
{
    struct Node
    {
        int count;
        Node* to[16];
    }nodes[100010];
    int tot;
    Node* root;
    Node* createNode()
    {
        Node* nod = &nodes[tot++];
        memset(nod, 0, sizeof(Node));
        return nod;
    }
    void init()
    {
        tot = 0;
        root = createNode();
    }
    inline int ord(char ch)
    {
        return ch & 0xF;
    }
    int insert(const char* s)
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = ord(*p);
            if(!nod->to[v])
            {
                nod->to[v] = createNode();
            }
            nod = nod->to[v];
            p++;
        }
        return nod->count++;
    }
    int find(const char* s)
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = ord(*p);
            if(!nod->to[v])return 0;
            nod = nod->to[v];
            p++;
        }
        return nod->count;
    }
};