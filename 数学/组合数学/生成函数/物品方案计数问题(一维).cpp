#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=500;
namespace GeneratingFunction
{
    ll ans1[maxn+10], ans2[maxn+10];
    ll a[120+10];//单件物品的价值
    ll b[120+10];//每件物品的个数
    ll N=0;//理论上的最大值
    ll ItemCount=0;//物品种类
    void GetValue()//权值
    {

    }
    void GetStock()//每个物品的个数
    {

    }
    void solve()
    {
        memset(ans1, 0, sizeof(ans1));
        memset(ans2, 0, sizeof(ans2));
        for(int i=0; i<=min(N/a[1], b[1]); i++)//初始化
        {
            ans1[i*a[1]]=1;
        }
        for(int i=2; i<=ItemCount; ++i)//枚举第i个多项式(第1个的系数已经被初始化了所以从2开始)
        {
            for(int j=0; j<=N; ++j)//枚举结果的式子(一共N+1项)
            {
                for(int k=0; j+k<=N && k<=b[i]*a[i]; k+=a[i])//k就是第i个式子的每一项的系数
                {
                    ans2[j+k]+=ans1[j];
                }
            }
            for(int j=0; j<=N; ++j)//清零
            {
                ans1[j]=ans2[j];
                ans2[j]=0;
            }
        }
        //接下来对ans1做相关处理即可
    }
};
void solve()
{
}