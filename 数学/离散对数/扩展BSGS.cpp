#include<bits/stdc++.h>
using namespace std;
long long quick_mul(long long a, long long b, long long c)
{
    return (a*b-(long long) ((long double) a*b/c)*c+c)%c;
}
long long quick_pow(long long a, long long b, long long c)
{
    a%=c;
    long long ans=1, base=a;
    while(b!=0)
    {
        if (b&1)
            ans=quick_mul(ans, base, c);
        base=quick_mul(base, base, c);
        b>>=1;
    }
    return ans%c;
}
long long extended_gcd(long long a, long long b, long long &x, long long &y)//扩展gcd
{
    long long r, t;
    if (b==0)
    {
        x=1;
        y=0;
        return a;
    }
    r=extended_gcd(b, a%b, x, y);
    t=x;
    x=y;
    y=t-(a/b)*y;
    return r;
}
long long Inv(long long a, long long mod)//逆元
{
    long long p, x, y;
    p=extended_gcd(a, mod, x, y);
    x/=p;
    long long t=mod/p;
    if (x>0)
        x=x%t;
    else
    {
        x=x%t+t;
    }
    return x;
}
long long BSGS(long long a, long long b, long long p)//a^x=b(mod p)
{
    if (!a)
        return b ? -1 : 1;
    if (b==1)
        return 0;
    long long m=ceil(sqrt(p));
    //a^(im+j)=b(mod p)
    //a^j=b*a^(-mi)(mod p)
    long long aj=1;
    unordered_map<long long, long long> P;
    for(long long i=0; i<m; i++)
    {
        P[aj]=i;
        aj=quick_mul(aj, a, p);
    }
    long long ax=Inv(a, p);
    ax=quick_pow(ax, m, p);//ax=a^-m
    long long ay=1;
    for(long long i=0; i<=m; i++)
    {
        long long z=quick_mul(b, ay, p);
        if (P.find(z)!=P.end())
            return i*m+P[z];
        ay=quick_mul(ay, ax, p);
    }
    return -1;
}
long long EXBSGS(long long a, long long b, long long p)
{
    a%=p;
    b%=p;
    if (b==1)
        return 0;
    if (b%__gcd(a, p)!=0)
        return -1;
    if (__gcd(a, p)==1)
        return BSGS(a, b, p);
    long long d=1;//除掉的东西之积 
    long long k=0;//次数
    long long bb=b, pp=p;//backup
    while(__gcd(a, p)!=1)
    {
        long long z=__gcd(a, p);
        if (b%z!=0)
            return -1;
        b/=z;
        p/=z;
        k++;
        d*=z;
    }
    for(long long i=1; i<k; i++)//暴力枚举(1,k)的部分
    {
        if (quick_pow(a, i, pp)==bb)
        {
//			printf("find %lld in bruce force!\n",i);
            return i;
        }
    }
    long long ax=1;
    for(int i=1; i<=k; i++)
    {
        ax*=a;
    }
    ax/=d;//ax=a^k/d;
    //a^(x-k)*ax=b(mod p)
//	printf("solve %lld^(x-%lld)*%lld=%lld(mod %lld)\n",a,k,ax,b,p);
    long long ans=BSGS(a, quick_mul(b, Inv(ax, p), p), p);
    if (ans==-1)
        return -1;
    return ans+k;
}
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        long long a, b, p;
        scanf("%lld%lld%lld", &a, &b, &p);
        long long ans=EXBSGS(a, b, p);
        if (ans==-1)
        {
            printf("no solution\n");
        }
        else
        {
            printf("%lld\n", ans);
        }
    }
}