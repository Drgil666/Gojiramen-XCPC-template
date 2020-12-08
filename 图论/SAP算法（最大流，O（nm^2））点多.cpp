#include<stdio.h>
#include<string.h>
#include<queue>
#include<iostream>
using namespace std;
const int maxn = 300;
const int INF = 1000000+10;
int cap[maxn][maxn];//容量
int flow[maxn][maxn];//流量
int a[maxn]; //a[i]：从起点s到i的最小容量
int p[maxn]; //p[i]: 记录点i的父亲
int main()
{
    int n,m;
    while(~scanf("%d%d",&n,&m))
    {
        memset(cap,0,sizeof(cap));//初始化容量为 0
        memset(flow,0,sizeof(flow));//初始化流量为 0
        int x,y,c;//x,y是坐标，c是容量 
        for(int i=1;i<=n;i++)
        {
            scanf("%d%d%d",&x,&y,&c);
            cap[x][y]+=c;//因为可能会出现两个点有多条边的情况,所以需要全部加起来
        }
        int s=1,t=m;//第一个点为源点, 第 m个点为汇点
        queue<int>q;
        int f=0;//总流量
        for(;;)//BFS找增广路
        {
            memset(a,0,sizeof(a));
            /*a[i]:从起点s到i的最小残量
            【每次for()时a[]重新清0因此同时可做标记数组 vis】*/
            a[s] = INF;//起点残量无限大
            q.push(s);//起点入队
            while(!q.empty())//BFS寻找增广路
            {
                int u=q.front();
                q.pop();//取出队首并弹出
                for(int v=1;v<=m;v++)
                    if(!a[v] && cap[u][v]>flow[u][v])
                        //找到新节点 v(a[v]为0说明还未流到该点,且容量大于流量)
                    {
                        p[v]=u;//记录u为v父亲
                        q.push(v);//将v加入队列
                        a[v]=min(a[u], cap[u][v]-flow[u][v]);
                        // s-v 路径上的最小残量【从而保证了最后,每条路都满足最小】
                    }
            }
            if(a[t]==0)
                break;//找不到, 则当前流已经是最大流, 跳出循环
            for(int u=t;u!=s;u=p[u])//从终点往起点的路径回走 
            {
                flow[p[u]][u]+=a[t];//利用之前留下的父亲数组，去为之前走过的路更新正向流
                flow[u][p[u]]-=a[t];//更新反向流
            }
            f+=a[t];//更新从s流出的总流量
        }
        printf("%d\n",f);
    }
    return 0;
}