#include<bits/stdc++.h>
using namespace std;
typedef long long LL;
long long a,b,m;
long long MOD(long long a,long long mm)
{
    return a>mm?a%mm+mm:a;
}
long long phi(long long n)
{
    long long ans = n;
    for(int i = 2; i*i <= n; i++)
    {
        if(n % i == 0)
        {
            ans -= ans/i; //等价于通项，把n乘进去
            while(n % i == 0) //确保下一个i是n的素因数
                n /= i;
        }
    }
    if(n > 1)ans -= ans/n; //最后可能还剩下一个素因数没有除
    return ans;
}
long long gcd(long long a,long long b)
{
    if(b==0)
        return a;
    return gcd(b,a%b);
}
long long qsm(long long a,long long b,long long c)
{
    if(!c)
        return 0;
    long long ans=1,base=a;
    while(b!=0)
    {
        if(b&1)
            ans=MOD(ans*base,c);
        base=MOD(base*base,c);
        b>>=1;
    }
    return MOD(ans,c);
}
long long f(long long b,long long mm)
{
    if(mm==1)
        return MOD(a,1);
    if(b==1)
    {
        return MOD(a,mm);
    }
    return qsm(a,f(b-1,phi(mm)),mm);
}
int main()
{
    int t;
    scanf("%d",&t);
    while(t--)
    {
        scanf("%lld%lld%lld",&a,&b,&m);
        //b个a mod m
        if(b==0 || a==1 || m==1)
        {
            printf("%lld\n",1%m);
            continue;
        }
        if(b==1)
        {
            printf("%lld\n",a%m);
            continue;
        }
        long long ans=f(b,m)%m;
        printf("%lld\n",ans);
    }
}