/**
 * 
 * KMP 扩展KMP
 * 
**/

#include <cstdio>
#include <algorithm>

struct kmp
{
    int nxt[1000010];
    void init_nxt(const char* pat)
    {
        int pre = -1, cur = 0;
        nxt[0] = -1;
        while(pat[cur])
        {
            if(pre == -1 || pat[pre] == pat[cur])
            {
                pre++, cur++;
                nxt[cur] = (pat[pre] == pat[cur] ? nxt[pre] : pre); // next数组优化，表示最终回退位置
                // nxt[cur] = pre; //不优化，表示最大前后缀长度
            }
            else
            {
                pre = nxt[pre];
            }
        }
    }
    void operator()(const char* dst, const char* pat)
    {
        int i = 0, j = 0;
        while(dst[i])
        {
            if(j == -1 || dst[i] == pat[j])
            {
                i++, j++;
                if(pat[j] == '\0')
                {
                    // 匹配dst[i-j:i-1]
                    j=nxt[j];
                }
            }
            else j = nxt[j];
        }
    }
};


struct extend_kmp
{
    int nxt[1000010] /* 最长前缀 */, ext[1000010];
    void init_nxt(const char* pat)
    {
        int p = 0, mx = 0, i;
        for(i = 1; pat[i]; i++)
        {      
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)nxt[i] = nxt[i - p];
            else
            {
                k = mx + 1;
                int j = i > mx ? 0 : k - p;
                while(pat[k] && pat[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                nxt[i] = k - i;
            }
        }
        nxt[0] = i;
    }
    void operator()(const char* dst, const char* pat)
    {
        int p, mx = -1, i;
        for(i = 0; dst[i]; i++)
        {
            int k = i > mx ? i : i + nxt[i - p] - 1;
            if(k < mx)ext[i] = nxt[i - p];
            else
            {
                int k = mx + 1;
                int j = k - i;
                while(dst[k] && dst[k] == pat[j])k++, j++;
                p = i;
                mx = std::max(p, k - 1);
                ext[i] = k - i;
            }
        }
    }
};