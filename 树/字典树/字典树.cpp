namespace Trie
{
    int change(char x)//字符集变换方式
    {
        return x-'a'+1;
    }
    int Next[maxn+10][30], cnt;
    int End[maxn+10];  // 该结点结尾的字符串是否存在
    void init()
    {
        memset(Next[0], 0, sizeof(Next[0]));
        End[0]=0;
        cnt=0;
    }
    void insert(char *s, int l, int score)// 插入字符串
    {
        int p=0;
        for(int i=0; i<l; i++)
        {
            int c=change(s[i]);
            if (!Next[p][c])
            {
                Next[p][c]=++cnt;  // 如果没有，就添加结点
                memset(Next[cnt], 0, sizeof(Next[cnt]));
                End[cnt]=0;
            }
            p=Next[p][c];
        }
        End[p]=score;
    }
    int find(char *s, int l)  // 查找字符串
    {
        int p=0;
        for(int i=0; i<l; i++)
        {
            int c=change(s[i]);
            if (!Next[p][c]) return 0;
            p=Next[p][c];
        }
        return End[p];
    }
};