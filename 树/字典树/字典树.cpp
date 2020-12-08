namespace Trie
{
    int change(char x)//�ַ����任��ʽ
    {
        return x-'a'+1;
    }
    int Next[maxn+10][30], cnt;
    int End[maxn+10];  // �ý���β���ַ����Ƿ����
    void init()
    {
        memset(Next[0], 0, sizeof(Next[0]));
        End[0]=0;
        cnt=0;
    }
    void insert(char *s, int l, int score)// �����ַ���
    {
        int p=0;
        for(int i=0; i<l; i++)
        {
            int c=change(s[i]);
            if (!Next[p][c])
            {
                Next[p][c]=++cnt;  // ���û�У�����ӽ��
                memset(Next[cnt], 0, sizeof(Next[cnt]));
                End[cnt]=0;
            }
            p=Next[p][c];
        }
        End[p]=score;
    }
    int find(char *s, int l)  // �����ַ���
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