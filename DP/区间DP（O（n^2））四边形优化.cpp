#include<bits/stdc++.h>
using namespace std;
const int MAXN=1000+10;
int dp[MAXN][MAXN];
int a[MAXN];
int s[MAXN][MAXN];
int sum[MAXN];
#define INF 0x3f3f3f
void solve1()
{
    int n;
    scanf("%d", &n);
    memset(dp, INF, sizeof(dp));
    sum[0]=0;
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
        sum[i]=sum[i-1]+a[i];
        dp[i][i]=0;//[i,i]为0
        s[i][i]=i;
    }
    for(int len=1; len<=n; len++)//枚举区间
    {
        for(int j=1; j+len-1<=n; j++)
        {
            int end=j+len-1;//区间为[j,end]
            for(int i=s[j][end-1]; i<=s[j+1][end]; i++)//s[j][end]表示[j,k]+[k,end]的最优区间位置k
            {
                if (dp[j][end]>dp[j][i]+dp[i+1][end]+(sum[end]-sum[j-1]))
                {
                    dp[j][end]=dp[j][i]+dp[i+1][end]+(sum[end]-sum[j-1]);
                    s[j][end]=i;
                }
            }
        }
    }
    printf("%lld\n", dp[1][n]);
}