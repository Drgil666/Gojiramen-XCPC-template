#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
struct Edge
{
    int to, next;
};
Edge edge[(maxn<<1)+10];
int Head[maxn+10];
int sumEdge=0;
int f[maxn+10][31];//f[i][j]表示i的第2^j个祖先
int depth[maxn+10];
int n, q, m, cnt=0;
const int Mul=30;
int a[maxn+10], b[maxn+10], T[maxn+10];
int sum[maxn*Mul+10], L[maxn*Mul+10], R[maxn*Mul+10];
inline void add_edge(int u, int v)
{
    edge[++sumEdge].to=v;
    edge[sumEdge].next=Head[u];
    Head[u]=sumEdge;
}
inline void Edge_Print(int size)
{
    for(int i=1; i<=size; i++)
    {
        printf("%d\n", i);
        for(int j=Head[i]; j; j=edge[j].next)
        {
            printf("%d ", edge[j].to);
        }
        printf("\n");
    }
}
void init()
{
    memset(Head, -1, sizeof(Head));
    memset(edge, 0, sizeof(edge));
    memset(Head, 0, sizeof(Head));
    sumEdge=0;
}
int getLCA(int u, int v)
{
    if (depth[u]<depth[v])
        swap(u, v);
    for(int i=20; i>=0; i--)
        if (depth[f[u][i]]>=depth[v]) u=f[u][i];
    if (u==v)
        return u;
    for(int i=20; i>=0; i--)
        if (f[u][i]!=f[v][i])
        {
            u=f[u][i];
            v=f[v][i];
        }
    return f[u][0];
}
inline int President_Tree_build(int l, int r)//和线段树类似
{
    int rt=++cnt;
    sum[rt]=0;
    if (l<r)//这里不执行的时候就是叶子节点
    {
        int mid=(l+r)>>1;
        L[rt]=President_Tree_build(l, mid);
        R[rt]=President_Tree_build(mid+1, r);
    }
    return rt;
}
inline int President_Tree_update(int pre, int l, int r, int x)
{
    int rt=++cnt;//开辟新节点
    L[rt]=L[pre];
    R[rt]=R[pre];//
    sum[rt]=sum[pre]+1;//更新个数
    if (l<r)
    {
        int mid=(l+r)>>1;
        if (x<=mid) L[rt]=President_Tree_update(L[pre], l, mid, x);
        else R[rt]=President_Tree_update(R[pre], mid+1, r, x);
    }
    return rt;
}
inline int President_Tree_query(int ql, int qr, int k, int l, int r)
{
    int lca=getLCA(ql, qr);
    int lf=f[lca][0];
    ql=T[ql], qr=T[qr], lca=T[lca], lf=T[lf];
    while(l<r)
    {
        int mid=(l+r)>>1;
        if (k<=(sum[L[ql]]+sum[L[qr]]-sum[L[lca]]-sum[L[lf]]))
        {
            ql=L[ql];
            qr=L[qr];
            lca=L[lca];
            lf=L[lf];
            r=mid;
        }
        else
        {
            k-=(sum[L[ql]]+sum[L[qr]]-sum[L[lca]]-sum[L[lf]]);
            ql=R[ql];
            qr=R[qr];
            lca=R[lca];
            lf=R[lf];
            l=mid+1;
        }
    }
    return l;
}
inline void depth_Print()//调试用，输出depth
{
    for(int i=1; i<=sumEdge/2; i++)
    {
        printf("%d ", depth[i]);
    }
    printf("\n");
}
void LCA_dfs(int u, int pre)
{
    int tt=lower_bound(b+1, b+1+m, a[u])-b;
    T[u]=President_Tree_update(T[pre], 1, m, tt);
    depth[u]=depth[pre]+1;
    f[u][0]=pre;
    for(int i=1; (1<<i)<=depth[u]; i++)
        f[u][i]=f[f[u][i-1]][i-1];
    for(int k=Head[u]; k; k=edge[k].next)
    {
        if (edge[k].to!=pre)
            LCA_dfs(edge[k].to, u);
    }
}
void solve()
{
    init();
    scanf("%d%d", &n, &q);
    for(int i=1; i<=n; i++)
    {
        scanf("%d", &a[i]);
        b[i]=a[i];
    }
    sort(b+1, b+1+n);
    m=unique(b+1, b+1+n)-(b+1);
    T[0]=President_Tree_build(1, m);
    for(int i=1; i<=n-1; i++)
    {
        int u, v;
        scanf("%d%d", &u, &v);
        add_edge(u, v);
        add_edge(v, u);
    }
    LCA_dfs(1, 0);
//    depth_Print();
    while(q--)
    {
        int l, r, k;
        scanf("%d%d%d", &l, &r, &k);
        int lca=getLCA(l, r);
//        printf("%d\n",lca);
        int index=President_Tree_query(l, r, k, 1, m);
//        printf("index=%d\n",index);
        printf("%d\n", b[index]);
    }
}