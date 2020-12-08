struct Edge
{
    int to,next;
};
const long long maxn=1e5;
Edge edge[maxn+10];
int Start[maxn+10],End[maxn+10];//dfs序用数组
bool used[maxn+10];
int Head[maxn+10];
int sumEdge;
int cnt=0;
inline void init()
{
    memset(Head,0, sizeof(Head));
    memset(edge,0, sizeof(edge));
    memset(used,false, sizeof(used));
    memset(End,0, sizeof(End));
    sumEdge=0;
    cnt=0;
}
inline void add_edge(int u,int v)
{
    edge[++sumEdge].to=v;
    edge[sumEdge].next=Head[u];
    Head[u]=sumEdge;
}
inline void dfs(int x)
{
    cnt++;
    Start[x]=cnt;
    for(int i=Head[x];i;i=edge[i].next)
    {
        dfs(edge[i].to);
    }
    End[x]=cnt;
}
inline void Edge_Print(int n)
{
    for(int i=1;i<=n;i++)
    {
        printf("%d\n",i);
        for(int j=Head[i];j;j=edge[j].next)
        {
            printf("%d ",edge[j].to);
        }
        printf("\n");
    }
}
inline void useIt()
{
    long long n;
    init();
    scanf("%lld", &n);
    for(int i=1; i<=n-1; i++)
    {
        int u,v;
        scanf("%d%d", &u,&v);
        used[v]=true;
        add_edge(u,v);
    }
//        Edge_Print(n);
    for(int i=1;i<=n;i++)
    {
        if(!used[i])//入度为0是这个图的入口
        {
            dfs(i);
            break;
        }
    }
}