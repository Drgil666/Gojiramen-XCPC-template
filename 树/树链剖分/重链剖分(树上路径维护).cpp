#include <bits/stdc++.h>
using namespace std;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)
//左儿子
#define rson(n) (n<<1|1)
//右儿子
#define NodeType int
const int maxn=2e5;
int mod;
struct Edge
{
    int to, next;
};
Edge edge[(maxn<<1)+10];
int Head[maxn+10];
int sumEdge=0;
int cnt=0;//dfs用计数
int Father[maxn+10];//父亲(根节点的父亲为0)
int Depth[maxn+10];//深度(从1开始)
int Size[maxn+10];//子树节点个数
int Son[maxn+10];//重儿子
int Top[maxn+10];//重链顶部节点
int Dfn[maxn+10];//x的dfs序(线段树中的编号)
int Rank[maxn+10];
//Dfn的逆运算,dfs序中对应的节点编号,Rank[Dfn[x]]=x
NodeType ReadArray[maxn+10];//输入图/树用的数组
struct Node
{
    NodeType l=0, r=0, sum=0, lazyTag=0;
    //左边界、右边界、区间和、懒惰标记
    Node()
    {
        l=r=sum=lazyTag=0;
    }
};
Node Tree[(maxn<<2)+10];
inline void Edge_HLD_init(int n)
{
    memset(Head, 0, sizeof(int)*n);
    memset(edge, 0, sizeof(int)*n);
//    memset(Father,0,sizeof(int)*n);
    memset(Son,0,sizeof(int)*n);
//    memset(Top,0,sizeof(int)*n);
    memset(Dfn,0,sizeof(int)*n);
    sumEdge=0;
    cnt=0;
}
inline void add_edge(int u, int v)
{
    edge[++sumEdge].to=v;
    edge[sumEdge].next=Head[u];
    Head[u]=sumEdge;
}
inline void Edge_Print(int n)
{
    for(int i=1; i<=n; i++)
    {
        printf("%d\n", i);
        for(int j=Head[i]; j; j=edge[j].next)
        {
            printf("%d ", edge[j].to);
        }
        printf("\n");
    }
}
void Tree_pushUp(int k)//更新最值
{
    Tree[k].sum=(Tree[lson(k)].sum+Tree[rson(k)].sum)%mod;
}
void Tree_build(int k, int l, int r)
//建树(当前节点编号,区间范围)
{
    Tree[k].l=l;
    Tree[k].r=r;
    if (Tree[k].l==Tree[k].r)//叶子节点
    {
        Tree[k].sum=ReadArray[Rank[l]]%mod;
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);//二分区间
    Tree_pushUp(k);//更新最值
}
void Tree_pushDown(int k)
{
    if (Tree[k].lazyTag)
    {
        Tree[lson(k)].sum=(long long)(Tree[lson(k)].sum+1LL*(Tree[lson(k)].r-Tree[lson(k)].l+1)*Tree[k].lazyTag%mod)%mod;
        Tree[rson(k)].sum=(long long)(Tree[rson(k)].sum+1LL*(Tree[rson(k)].r-Tree[rson(k)].l+1)*Tree[k].lazyTag%mod)%mod;
        Tree[lson(k)].lazyTag=(Tree[lson(k)].lazyTag+Tree[k].lazyTag)%mod;
        Tree[rson(k)].lazyTag=(Tree[rson(k)].lazyTag+Tree[k].lazyTag)%mod;
        Tree[k].lazyTag=0;
    }
}
inline void Tree_add(int k, int l, int r, int x)
//当前结点，目标范围，要加的值
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        Tree[k].sum=(long long)(Tree[k].sum+1LL*(Tree[k].r-Tree[k].l+1)*x%mod)%mod;
        Tree[k].lazyTag=(Tree[k].lazyTag+x)%mod;
        return;
    }
    Tree_pushDown(k);
    if (l<=Tree[lson(k)].r)
    {
        Tree_add(lson(k), l, r, x);
    }
    if (Tree[rson(k)].l<=r)
    {
        Tree_add(rson(k), l, r, x);
    }
    Tree_pushUp(k);
}
inline NodeType Tree_query(int k, int l, int r)
//当前结点、目标区间
{
    if (Tree[k].lazyTag)//先更新后查询
    {
        Tree_pushDown(k);
    }
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].sum;
    }
    if (Tree[k].r<l || Tree[k].l>r)
        return 0;
    long long ans=0;
    if (l<=Tree[lson(k)].r)
    {
        ans=(ans+Tree_query(lson(k), l, r))%mod;
    }
    if (Tree[rson(k)].l<=r)
    {
        ans=(ans+Tree_query(rson(k), l, r))%mod;
    }
    return ans;
}
void Tree_Debug(int n)
{
    printf("Tree debug:\n");
    _rep(i, 1, n)
    {
        printf("%d ", Tree_query(1, i, i));
    }
    printf("\n");
}
inline void HLD_dfs1(int now, int fa, int dep)
//第一次dfs求Father,Size,Son,Depth
{
    Depth[now]=dep;
    Son[now]=-1;
    Size[now]=1;//自己也属于子树
    Father[now]=fa;//父亲
    int maxSon=-1;
    for(int i=Head[now]; i; i=edge[i].next)
    {
        if (edge[i].to==fa)
        {
            continue;//因为建的双向边所以可能会回去
        }
        HLD_dfs1(edge[i].to, now, dep+1);//向下递归
        Size[now]+=Size[edge[i].to];
        if (Size[edge[i].to]>maxSon)
        {
            maxSon=Size[edge[i].to];
            Son[now]=edge[i].to;
        }//更新重儿子、个数
    }
}
inline void HLD_dfs2(int now, int TopRoot)
//第二次dfs求Top,Dfn,Rank,先处理重儿子再处理轻儿子
{
    Dfn[now]=++cnt;//更新dfs序
    Rank[cnt]=now;//更新Rank
    Top[now]=TopRoot;//更新Top
    if (Son[now]==-1)//没有儿子(叶子节点)
        return;
    HLD_dfs2(Son[now], TopRoot);
    //直接先处理重儿子,保证重链上点dfs连续
    for(int i=Head[now]; i; i=edge[i].next)
    {
        if (edge[i].to!=Father[now] && edge[i].to!=Son[now])//没处理过的轻儿子
            //这里虽然可以写成if(!Dfn[edge[i].to]),但多次树剖时Dfn需要初始化
        {
            HLD_dfs2(edge[i].to, edge[i].to);//Top就是自己
        }
    }
}
int HLD_lca(int u,int v)
//跳链求LCA
{
    while(Top[u]!=Top[v])
    {
        if(Depth[Top[u]]<Depth[Top[v]])
            v=Father[Top[v]];
        else
            u=Father[Top[u]];
    }
    if(Depth[u]<Depth[v])
        return u;
    return v;
}
void HLD_update(int x, int y, int z)
//在x,y的路径之间加上z(跳链),其他维护也类似
{
    while(Top[x]!=Top[y])//不断跳链知道两个点在同一链上，一遍跳一遍更新和
    {
        if (Depth[Top[x]]<Depth[Top[y]])
            swap(x, y);//让x的重链顶深度更大些,让x跳链
        Tree_add(1, Dfn[Top[x]], Dfn[x], z);//跳链时更新
        x=Father[Top[x]];//跳链
    }
    //当x,y在同一链时再更新x,y之间
    if (Depth[x]>Depth[y])
        swap(x, y);
    Tree_add(1, Dfn[x], Dfn[y], z);
}
int HLD_query(int x, int y)
{
    int ans=0;
    while(Top[x]!=Top[y])
        //不断跳链知道两个点在同一链上，一遍跳一遍更新和
    {
        if (Depth[Top[x]]<Depth[Top[y]])
            swap(x, y);//让x的重链顶深度更大些,让x跳链
        ans=(ans+Tree_query(1, Dfn[Top[x]], Dfn[x]))%mod;//跳链时更新
        x=Father[Top[x]];//跳链
    }
    //当x,y在同一链时再更新x,y之间
    if (Depth[x]>Depth[y])
        swap(x, y);
    ans=(ans+Tree_query(1, Dfn[x], Dfn[y]))%mod;
    return ans;
}
void HLD_Debug(int n)
{
    printf("Father: ");
    _rep(i, 1, n)
    {
        printf("%d ", Father[i]);
    }
    printf("\n");
    printf("Depth: ");
    _rep(i, 1, n)
    {
        printf("%d ", Depth[i]);
    }
    printf("\n");
    printf("Size: ");
    _rep(i, 1, n)
    {
        printf("%d ", Size[i]);
    }
    printf("\n");
    printf("Son: ");
    _rep(i, 1, n)
    {
        printf("%d ", Son[i]);
    }
    printf("\n");
    printf("Top: ");
    _rep(i, 1, n)
    {
        printf("%d ", Top[i]);
    }
    printf("\n");
    printf("Dfn: ");
    _rep(i, 1, n)
    {
        printf("%d ", Dfn[i]);
    }
    printf("\n");
}
void solve()
{
    int n;
    scanf("%d",&n);
    _repp(i,1,n)
    {
        int u,v;
        scanf("%d%d",&u,&v);
        add_edge(u,v);
        add_edge(v,u);
    }
    HLD_dfs1(1,0,1);//假定1是根
    HLD_dfs2(1,1);//假定1是根
}
int main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    long long test_index_for_debug=1;
    char acm_local_for_debug;
    while(cin>>acm_local_for_debug)
    {
        cin.putback(acm_local_for_debug);
        if (test_index_for_debug>100)
        {
            throw runtime_error("Check the stdin!!!");
        }
        auto start_clock_for_debug=clock();
        solve();
        auto end_clock_for_debug=clock();
        cout<<"\nTest "<<test_index_for_debug<<" successful"<<endl;
        cerr<<"Test "<<test_index_for_debug++<<" Run Time: "
            <<double(end_clock_for_debug-start_clock_for_debug)/CLOCKS_PER_SEC<<"s"<<endl;
        cout<<"--------------------------------------------------"<<endl;
    }
#else
    solve();
#endif
    return 0;
}