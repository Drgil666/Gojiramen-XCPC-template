#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=500;
ll ans1[maxn+10][maxn+10], ans2[maxn+10][maxn+10];
//ans1[i][j]表示用j个物品价值为i
ll a[120+10];//单件物品的价值
ll b[120+10];//每件物品的个数
ll N=250;//理论上的最大值
ll ItemCount=5;//物品种类
void solve()
{
    int n;
    a[1]=1;
    a[2]=5;
    a[3]=10;
    a[4]=25;
    a[5]=50;
    memset(ans1, 0, sizeof(ans1));
    memset(ans2, 0, sizeof(ans2));
    for(int i=0; i<=min(N/a[1],b[1]); i++)//初始化
    {
        ans1[i*a[1]][i]=1;
    }
    for(int i=2; i<=ItemCount; ++i)//枚举第i个多项式(第1个的系数已经被初始化了所以从2开始)
    {
        for(int j=0; j<=N; ++j)//枚举结果的式子(一共N+1项)
        {
            for(int k=0; j+k<=N && k<=a[i]*b[i]; k+=a[i])//k就是第i个式子的每一项的系数
            {
                for(int l=0; l+k/a[i]<=min(N,b[i]); ++l)//物品个数
                {
                    ans2[j+k][l+k/a[i]]+=ans1[j][l];
                }
            }
        }
        for(int j=0; j<=N; ++j)//清零
        {
            for(int k=0; k<=N; k++)
            {
                ans1[j][k]=ans2[j][k];
                ans2[j][k]=0;
            }
        }
    }//接下来对ans1做相关处理即可
}

signed main()
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