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
    if (x>0)
        x=x%t;
    else
    {
        x=x%t+t;
    }
    return x;
}
long long BSGS(long long a,long long b,long long p)//a^x=b(mod p) 
{
    if(!a)
        return b?-1:1;
    if(b==1)
        return 0;
    long long m=ceil(sqrt(p));
    //a^(im+j)=b(mod p)
    //a^j=b*a^(-mi)(mod p)
    long long aj=1;
    unordered_map<long long ,long long >P;
    for(long long i=0;i<m;i++)
    {
        P[aj]=i;
        aj=quick_mul(aj,a,p);
    }
    long long ax=Inv(a,p);
    ax=quick_pow(ax,m,p);//ax=a^-m
    long long ay=1;
    for(long long i=0;i<=m;i++)
    {
        long long z=quick_mul(b,ay,p);
        if(P.find(z)!=P.end())
            return i*m+P[z];
        ay=quick_mul(ay,ax,p);
    }
    return -1;
}
int main()
{
    long long a,b,p;
    scanf("%lld%lld%lld",&p,&a,&b);
    long long ans=BSGS(a,b,p);
    if(ans==-1)
    {
        printf("no solution\n");
    }
    else
    {
        printf("%lld\n",ans);
    }
}