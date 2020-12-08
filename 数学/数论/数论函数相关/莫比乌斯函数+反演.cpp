#include<bits/stdc++.h>
using namespace std;
const long long MAX=1000000;
bool check[MAX+10];
int prime[MAX+10];
int mu[MAX+10];
long long sum[MAX+10];
void Moblus()
{
    memset(check,false,sizeof(check));
    mu[1] = 1;
    sum[1]=1;
    int tot = 0;
    for(int i = 2; i <= MAX; i++)
    {
        if( !check[i] ){
            prime[tot++] = i;
            mu[i] = -1;
        }
        for(int j = 0; j < tot; j++)
        {
            if(i * prime[j] > MAX) break;
            check[i * prime[j]] = true;
            if( i % prime[j] == 0){
                mu[i * prime[j]] = 0;
                break;
            }else{
                mu[i * prime[j]] = -mu[i];
            }
        }
        sum[i]=sum[i-1]+mu[i];
    }
}
long long fy(long long n,long long m,long long k)
{
    n/=k;
    m/=k;
    long long ans=0,r;
    for(int i=1;i<=min(m,n);i=r+1)
    {
        r=min(n/(n/i),m/(m/i));
        ans+=(sum[r]-sum[i-1])*(n/i)*(m/i);
    }
    //printf("ans=%lld\n",ans);
    return ans;
}
int main()
{
    Moblus();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        long long n,m,p;
        scanf("%lld%lld%lld",&n,&m,&p);
        long long ans1[100010];
        ans1[1]=fy(n,m,1);
        for(int i=2;i<=p;i++)
        {
            ans1[i]=fy(n,m,p);
        }
        long long anss=0;
        for(int i=1;i<=p;i++)
            anss+=ans1[i]*i;
        printf("%lld\n",anss);
    }
}