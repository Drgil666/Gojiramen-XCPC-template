struct UnionFind
{
    int father[100050];
    void Find_init(int n)//并查集初始化
    {
        for(int i=1; i<=n; i++)
        {
            father[i]=i;
        }
    }
    int Find(int x)//并查集（压缩路径）
    {
        return x==father[x] ? x : (father[x]=Find(father[x]));
    }
    void union_set(int x, int y)//合并
    {
        int fx=Find(x);
        int fy=Find(y);
        father[fx]=fy;
    }
};