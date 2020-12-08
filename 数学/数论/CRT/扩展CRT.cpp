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
    p=extended_gcd (a,mod,x,y);
    x/=p;
    long long t=mod/p;
    if (x>=0)
        x=x%t;
    else
    {
        x=x%t+t;
    }
    return x;
}
long long EXCRT(long long n, long long *a, long long *b)
{
    long long aa=a[1],bb=b[1];
    for(long long i=2;i<=n;i++)
    {
        long long d=__gcd(bb,b[i]);
        if((a[i]-aa)%d!=0)
        {
            return -1;//no solution!
        }
        long long mod=b[i]/d;
        aa=(quick_mul(quick_mul(Inv(bb/d,mod),((a[i]-aa)/d%mod+mod),mod),bb,bb*(b[i]/d))+aa);
        bb=bb*(b[i]/d);
        aa%=bb;
    }
    return aa;
}
int main()
{
    long long n;
    scanf("%lld",&n);
    long long a[100010],b[100010];
    for(int i=1;i<=n;i++)
    {
        scanf("%lld%lld",&a[i],&b[i]);//a[i]余数,b[i]模数
    }
    printf("%lld\n",EXCRT(n,a,b));
}