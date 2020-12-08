struct UnionFind
{
    int father[100050];
    void Find_init(int n)//���鼯��ʼ��
    {
        for(int i=1; i<=n; i++)
        {
            father[i]=i;
        }
    }
    int Find(int x)//���鼯��ѹ��·����
    {
        return x==father[x] ? x : (father[x]=Find(father[x]));
    }
    void union_set(int x, int y)//�ϲ�
    {
        int fx=Find(x);
        int fy=Find(y);
        father[fx]=fy;
    }
};