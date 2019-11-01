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
        int count; // 当前节点是多少个单词的结尾
        Node* nxt[26];
    }nodes[100010];
    int sz; // 节点总数
    Node* root; // 根节点
    Node* createNode()
    {
        Node* nod = &nodes[sz++];
        memset(nod, 0, sizeof(Node));
        return nod;
    }
    void init() // 初始化，清空字典树
    {
        sz = 0;
        root = createNode();
    }
    inline int id(char ch) // 字符映射到边
    {
        return ch - 'a';
    }
    int insert(const char* s) // 插入单词
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])
            {
                nod->nxt[v] = createNode();
            }
            nod = nod->nxt[v];
            p++;
        }
        return nod->count++;
    }
    int find(const char* s) // 查找单词，返回出现次数
    {
        Node* nod = root;
        const char* p = s;
        while(*p)
        {
            int v = id(*p);
            if(!nod->nxt[v])return 0;
            nod = nod->nxt[v];
            p++;
        }
        return nod->count;
    }
};