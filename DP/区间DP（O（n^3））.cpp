#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
int dp[MAXN][MAXN];
int a[MAXN];
#define INF 0x3f3f3f
void solve1()
{
    int n;
    memset(dp, INF, sizeof(dp));
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
        dp[i][i]=0;//[i,i]为0
    }
    for(int len=1; len<=n; len++)//枚举区间
    {
        for(int j=1; j+len-1<=n; j++)
        {
            int end=j+len-1;//区间为[j,end]
            for(int i=j; i<end; i++)//暴力枚举[j,i]+[i+1,end]
                dp[j][end]=min(dp[j][end], dp[j][i]+dp[i+1][end]+something);
        }
    }
    printf("%lld\n", dp[1][n]);
}