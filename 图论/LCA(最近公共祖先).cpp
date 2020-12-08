#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
struct Edge
{
    int to, next;
};
Edge edge[maxn+10];
int Head[maxn+10];
int sumEdge;
int f[maxn][31];//f[i][j]表示i的第2^j个祖先
int depth[maxn];
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
void init()
{
    memset(Head, 0, sizeof(Head));
    memset(edge, 0, sizeof(edge));
    memset(Head, 0, sizeof(Head));
    sumEdge=0;
}
void LCA_dfs(int u, int pre)
{
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
int getLCA(int u, int v)
{
    if (depth[u]<depth[v])
        swap(u, v);
    for(int i=30; i>=0; i--)
        if (depth[f[u][i]]>=depth[v]) u=f[u][i];
    if (u==v)
        return u;
    for(int i=30; i>=0; i--)
        if (f[u][i]!=f[v][i])
        {
            u=f[u][i];
            v=f[v][i];
        }
    return f[u][0];
}
void solve()
{
    LCA_dfs(1,0);
}