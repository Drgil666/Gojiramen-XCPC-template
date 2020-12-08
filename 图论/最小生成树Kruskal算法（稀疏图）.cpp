#include <stdio.h>
#include <string.h>
#include <algorithm>
#define MAXN 200  //顶点个数的最大值
#define MAXM 200  //边的个数的最大值
using namespace std;
struct edge  //边
{
    int u, v, w; //边的起点与终点、权值
}edges[MAXM]; //边的数组
int parent[MAXN];//parent[i]为顶点i所在集合对应的树中的根结点
int n,m;//顶点个数、边的个数
int i,j;//循环变量
void UFset()//初始化
{
    for(i=1;i<=n;i++)parent[i]=-1;
}
int Find(int x) //查找并返回节点x所属集合的根结点
{
    int s;//查找位置
    for(s=x;parent[s]>=0;s=parent[s]);
    while(s!=x) //优化方案―压缩路径，使后续的查找操作加速。
    {
        int tmp=parent[x];
        parent[x]=s;
        x=tmp;
    }//反复递归s，直到s=x（即x变为了根节点） 
    return s;
}
void Union(int R1,int R2)//将两个不同集合的元素进行合并，使两个集合中任两个元素都连通
{
    int r1 = Find(R1), r2 = Find(R2);//r1为R1的根结点，r2为R2的根结点
    int tmp = parent[r1] + parent[r2];//两个集合结点个数之和(负数)
    //如果 R2 所在树结点个数>R1所在树结点个数(注意 parent[r1]是负数)
    if( parent[r1]>parent[r2]) //优化方案――加权法则
    {
        parent[r1]=r2;//优化,若有与r1有关的会到r2 
        parent[r2]=tmp;//r2变为新的根结点（原r2被r1使用了） 
    }
    else
    {
        parent[r2]=r1;
        parent[r1]=tmp;
    }
}
bool cmp(edge a,edge b) //快排用的函数
{
    return a.w <= b.w;
}
void Kruskal()
{
    int sumweight = 0;  //生成树的权值
    int num = 0;  //已选用的边的数目
    int u,v;//选用边的两个顶点
    UFset(); //初始化parent[]
    for(i=0;i<m;i++)
    {
        u=edges[i].u;v=edges[i].v;
        if(Find(u)!=Find(v))//不同根节点，防止成环 
        {
            printf("走%d %d,权值为%d\n",u,v,edges[i].w);//输出路径用
            sumweight+=edges[i].w;num++;
            Union(u,v);//和并u与v，使之成为整体
        }
        if(num>=n-1) break;//n个节点n-1条边 
    }
    printf( "weight of MST is %d\n", sumweight);//最短路径 
}
int main( )
{
    int u, v, w; //边的起点和终点及权值
    scanf("%d%d",&n,&m); //读入顶点个数 n
    for(int i=0;i<m;i++)
    {
        scanf("%d%d%d",&u,&v,&w); //读入边的起点和终点
        edges[i].u=u;edges[i].v=v;edges[i].w=w;
    }
    sort(edges,edges+m,cmp);//对deges[i].w快排
    /*for(int i=0;i<m;i++)
     printf("%d %d %d\n",edges[i].u,edges[i].v,edges[i].w);*/
    Kruskal();
    return 0;
}