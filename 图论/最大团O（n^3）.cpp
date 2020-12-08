#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
const int maxn = 60;
bool mp[60][60];//矩阵存储 
int some[60][60], none[60][60], all[60][60];
/*all为已确定的极大团顶点的集合
some为未处理顶点集（初始状态是全部顶点）
none为不取的(但已搜过的)顶点集。
三个数组都是第i趟处理的结果放在第i行。 
故当且仅当some、none都为空集合的时候all才是一个极大团。
*/
int n,m,ans;
void dfs(int d,int an,int sn,int nn)//d为层数（即第d个点） an,sn,nn分别为all,some,none元素总数 
{
    if(!sn&&!nn) ans=max(ans,an);//ans是所有情况中all元素最大值，但some与none为空时，ans就是答案。
    int u=some[d][0];//拿出第一个点
    for(int i=0;i<sn;i++)//判断每一个点是否应该加入
    {
        int v=some[d][i];//在some中取出一点v
        if(mp[u][v])
            continue;//第一个能顺利进行的是第一个点本身
        for(int j=0;j<an;j++)
            all[d+1][j]=all[d][j];//保留上一次的处理的结果，其每一行都是处理后加入最大团的编号
        all[d+1][an]=v;//第an个点为v
        int tsn=0,tnn=0;
        for(int j=0;j<sn;j++)
            if(mp[v][some[d][j]])//如果some中的点与v相连则加入some下一次处理
                some[d+1][tsn++]=some[d][j];
        for(int j=0;j<nn;j++)
            if(mp[v][none[d][j]])//如果none中的点与v相连则加入none下一次处理
                none[d+1][tnn++]=none[d][j];
        dfs(d+1,an+1,tsn,tnn);//进行下一趟，用tsn，tnn来代替sn，nn，是因为只需要判断剩下的即可
        some[d][i]=0,none[d][nn++]=v;//回溯时将v从some取出加入none，说明该点不可加入。
    }
}
int work()
{
    ans = 0;
    for(int i=0;i<n;i++)
        some[1][i]=i+1;//将所有顶点加入some
    dfs(1,0,n,0);
    return ans;
}
int main()
{
    while(scanf("%d",&n)!=EOF && n)
    {
        for(int i=1;i<=n;i++)
            for(int j=1;j<=n;j++)
            {
                int x;
                scanf("%d",&x);
                mp[i][j]=mp[j][i]=x;
            }
        printf("%d\n", work());
    }
    return 0;
}