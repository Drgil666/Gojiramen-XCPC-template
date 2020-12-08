#include<stdio.h>
#include<string.h>
#include<algorithm>
#include<iostream>
using namespace std;
const int MAXN=150;
int k,n,u,v,t;
int uN,vN;//u,v数目
int g[MAXN][MAXN];
int linker[MAXN];
bool used[MAXN];
bool dfs(int u)//从左边开始找增广路径
{
    int v;
    for(v=1;v<=vN;v++)
        if(g[u][v]&&!used[v])
        {
            used[v]=true;
            if(linker[v]==-1||dfs(linker[v]))//找增广路，反向
            {
                linker[v]=u;
                return true;
            }
        }
    return false;
}
int hungary()
{
    int res=0;
    int u;
    memset(linker,-1,sizeof(linker));
    for(u=1;u<=uN;u++)
    {
        memset(used,0,sizeof(used));
        if(dfs(u)) res++;
    }
    return res;
}
main(void)
{

    scanf("%d",&t);
    while(t--)
    {
        scanf("%d%d",&n,&k);
        memset(g,0,sizeof(g));
        while(k--)
        {
            scanf("%d%d",&u,&v);
            g[u][v]=1;
        }
        uN=vN=n;
        printf("%d\n",n-hungary());//最小路径覆盖数=|G|-二分图最大匹配数
    }
}