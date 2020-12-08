#include<bits/stdc++.h>
using namespace std;
const long long N=5e6;
long long prime[800000];
bool vis[N+10];
long long sum_prime=0;
void prime_sieve(long long n)
{
    memset(vis,1,sizeof(vis));
    vis[0]=0;vis[1]=0;
    for(long long i=2;i<=n;i++)
    {
        if(vis[i])
        {
            prime[++sum_prime]=i;
            for(long long j=2*i;j<=n;j+=i)
            {
                vis[j]=0;
            }
        }
    }
}
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
long long extended_gcd (long long a,long long b,long long &x,long long &y)//扩展gcd
{
    long long r,t;
    if (b==0)
    {
        x=1;
        y=0;
        return a;
    }
    r=extended_gcd (b,a%b,x,y);
    t=x;
    x=y;
    y=t-(a/b)*y;
    return r;
}
long long Inv (long long a,long long mod)//逆元
{
    long long p,x,y;
    p=extended_gcd (a,mod,x,y);//p是gcd
    x=x/p;
    long long t=mod/p;
    if (x>=0)
        x=x%t;
    else
    {
        x=x%t+t;
    }
    return x;
}
long long CRT (long long numc,long long a[],long long b[],long long mod)//中国剩余定理
{
    long long ans=0;
    for (long long i=1;i<=numc;i++)
    {
        long long x1=quick_mul (a[i]%mod,mod/b[i]%mod,mod);
        x1=quick_mul (x1%mod,Inv (mod/b[i],b[i])%mod,mod);
        ans=(ans+x1+mod)%mod;
    }
    return ans;
}
long long f(long long n,long long p,long long pk)
{
    if(n==0)
        return 1;
    long long rou=1;//循环节
    long long rem=1;//余项
    for(long long i=1;i<=pk;i++)
    {
        if(i%p)
        {
            rou=rou*i%pk;
        }
    }
    rou=quick_pow(rou,n/pk,pk);
    for(long long i=pk*(n/pk);i<=n;i++)
    {
        if(i%p)
            rem=rem*(i%pk)%pk;
    }
    return f(n/p,p,pk)*rou%pk*rem%pk;
}
long long g(long long n,long long p)
{
    if(n<p)
        return 0;
    return g(n/p,p)+(n/p);
}
long long Comp(long long n,long long m,long long p,long long pk)//f(n)/(f(m)*f(n-m))*P^{g(x)-g(y)-g(z)}%P^k
{
    if(n<m)
        return 0;
    if(n==m)
        return 1;
    if(m>n-m)
        m=n-m;
    long long f1=f(n,p,pk);
    long long f2=Inv(f(m,p,pk),pk);
    long long f3=Inv(f(n-m,p,pk),pk);
    long long f4=quick_pow(p,g(n,p)-g(m,p)-g(n-m,p),pk);
    return f1*f2%pk*f3%pk*f4%pk;
}
long long ex_lucas(long long n,long long m,long long mod)
{
    long long a[60000],b[60000];//a是余数、b是模数
    long long prime_factor=0;
    long long p0=mod;
    for(long long i=1;i<=sum_prime;i++)
    {
        long long pk=1;
        while(p0%prime[i]==0)
        {
            pk*=prime[i];
            p0/=prime[i];
        }
        if(pk!=1)
        {
            prime_factor++;
            a[prime_factor]=Comp(n,m,prime[i],pk);
            b[prime_factor]=pk;
        }
    }
    if(p0!=1)
    {
        prime_factor++;
        a[prime_factor]=Comp(n,m,p0,p0);
        b[prime_factor]=p0;
    }
    return CRT(prime_factor,a,b,mod);
}
int main()
{
    prime_sieve(N);
    long long n,m,mod;
    scanf("%lld%lld%lld",&n,&m,&mod);
    printf("%lld\n",ex_lucas(n,m,mod));
} 