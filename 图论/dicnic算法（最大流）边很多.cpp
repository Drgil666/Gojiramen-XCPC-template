#include<bits/stdc++.h>
using namespace std;
#define maxn 1005
#define ll long long
const ll inf = 0x3f3f3f3f3f3f3f3f;
struct Edge
{
    ll to,nxt,w;
}e[maxn<<1];
int head[maxn],tot,n,m;
void init()
{
    memset(e,0,sizeof e);
    memset(head,-1,sizeof(head));
    tot=0;
}
void add(ll u,ll v,ll w)
{
    e[tot].to=v;
    e[tot].nxt=head[u];//head[u]存放u对应编号
    e[tot].w=w;
    head[u]=tot++;
}
int d[maxn];//d数组为分层标记
bool bfs()//在残量网络上构造分层图
{
    memset(d,0,sizeof d);
    queue<int>q;
    while(q.size())
        q.pop();//初始化队列
    q.push(1);
    d[1]=1;//从第一个点开始
    while(q.size())
    {
        int x=q.front();//取出队列元素
        q.pop();
        for(int i=head[x];i!=-1;i=e[i].nxt)//路径回溯
        {
            int y=e[i].to;
            if(d[y] || e[i].w==0)//流量为0或者该点已经标记过
                continue;
            q.push(y);
            d[y]=d[x]+1;//y点位于x点下一层
            if(y==n)
                return 1;//全部标记完了
        }
    }
    return 0;
}
int dinic(int x,ll flow)
{
    if (x==n)
        return flow;//所有点都被取到
    ll rest=flow;//剩下的点
    for(int i=head[x];i!=-1 && rest>0;i=e[i].nxt)//路径回溯
    {
        int y=e[i].to;
        if(e[i].w==0 || d[y]!=d[x]+1)//权值为0或者d[x]与d[y]不相连（相连层数差为1）
            continue;
        ll k=dinic(y,min(rest,e[i].w));//用DFS寻找一条路径，并获得该条路径的流量
        if(!k)
            d[y]=0;    //y点已经被增广完毕
        e[i].w-=k;
        e[i^1].w+=k;
        rest-=k;//更新路径与结果
    }
    return flow-rest;
}
int main()
{
    while(cin>>m>>n)
    {
        init();
        for(int i=1;i<=m;i++)
        {
            ll u,v,w;
            cin>>u>>v>>w;
            add(u,v,w);
            add(v,u,0);//正向w方向0
        }
        ll flow=0,ans=0;
        while(bfs())
            while(flow=dinic(1,inf))
                ans+=flow;
        cout<<ans<<'\n';
    }
}