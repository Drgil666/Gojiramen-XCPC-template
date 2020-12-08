#include<bits/stdc++.h>
using namespace std;
const int N=1e6+5;
const int mod=1e9+7;
const int inv6=166666668;
const int inv2=500000004;
long long phi[N];
bool vis[N];
int prime[N];
int cnt;
void init()
{
    phi[1]=1;
    cnt=0;
    for(int i=2; i<N; i++)
    {
        if(!vis[i])
        {
            prime[cnt++]=i;
            phi[i]=i-1;
        }
        for(int j=0; j<cnt&&i*prime[j]<N; j++)
        {
            vis[i*prime[j]]=1;
            if(i%prime[j]==0)
            {
                phi[i*prime[j]]=phi[i]*prime[j];
                break;
            }
            else
                phi[i*prime[j]]=phi[i]*(prime[j]-1);
        }
    }
    for(int i=1; i<N; i++)
        phi[i]=(phi[i-1]+1ll*i%mod*phi[i]%mod)%mod;
}
unordered_map<long long,long long>P;
long long S(long long n)
{
    if(n<N) return phi[n];
    if(P.find(n)!=P.end()) return P[n];
    long long sum=n*(n+1)%mod*(2*n+1)%mod*inv6%mod;
    for(long long i=2,last; i<=n; i=last+1)
    {
        last=n/(n/i);
        sum=(sum-(last+i)*(last-i+1+mod)%mod*inv2%mod*(S(n/i)%mod)%mod+mod)%mod;
    }
    P[n]=sum;
    return sum;
}
int main()
{
    init();
    int t;
    scanf("%d",&t);
    while(t--)
    {
        int n,a,b;
        scanf("%d%d%d",&n,&a,&b);
        long long ans=(S(n)-1+mod)%mod;
        printf("%lld\n",ans*inv2%mod);
    }
    return 0;
}