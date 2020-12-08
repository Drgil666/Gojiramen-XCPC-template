#include<bits/stdc++.h>
using namespace std;
long long quick_mul (long long a,long long b,long long c)
{
    return (a*b-(long long)((long double)a*b/c)*c+c)%c;
}
long long quick_pow (long long a,long long b,long long c)
{
    a%=c;
    long long ans=1,base=a;
    while (b!=0)
    {
        if (b&1)
            ans=quick_mul (ans,base,c);
        base=quick_mul (base,base,c);
        b>>=1;
    }
    return ans%c;
}
long long Comp(long long n,long long m,long long mod)//C(n,m)%mod 
{
    if(n<m)
        return 0;
    if(n==m)
        return 1;
    if(m>n-m)
        m=n-m;
    long long ans=1,ca=1,cb=1;
    for(int i=0;i<m;i++)
    {
        ca=ca*(n-i)%mod;
        cb=cb*(m-i)%mod;
    }
    ans=ca*quick_pow(cb,mod-2,mod)%mod;
    return ans;
}
long long lucas(long long n,long long m,long long mod)
{
    long long ans=1;
    while(n && m)
    {
        ans=(ans*Comp(n%mod,m%mod,mod))%mod;
        n/=mod;
        m/=mod;
    }
    return ans;
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        long long n,m,mod;
        scanf("%lld%lld%lld",&n,&m,&mod);
        printf("%lld\n",lucas(n,m,mod));
    }
} 