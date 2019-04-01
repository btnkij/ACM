/**
 * 
 * manacher 最长回文串
 * 
**/

#include <algorithm>

struct manacher
{
    char s[2000100];
    int palin[2000100];
    void loadString(const char* str)
    {
        char* p = s;
        *(p++) = '#';
        const char* q = str;
        while(*q)
        {
            *(p++) = *(q++);
            *(p++) = '#';
        }
    }
    void init()
    {
        int p, far = 0;
        for(int i = 0; s[i]; i++)
        {
            int lt, rt;
            if(i < far)rt = std::min(i + palin[(p << 1) - i] - 1, far);
            else rt = i;
            lt = (i << 1) - rt;
            while(lt >= 0 && s[lt] == s[rt])lt--, rt++;
            if(rt - 1 > far)
            {
                far = rt - 1;
                p = i;
            }
            palin[i] = rt - i;
        }
    }
};