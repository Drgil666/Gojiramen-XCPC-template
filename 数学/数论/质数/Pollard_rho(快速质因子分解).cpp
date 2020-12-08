#include<bits/stdc++.h>
using namespace std;
unordered_map<long long ,long long >P;
long long sumfactor=0;
long long quick_mul (long long a,long long b,long long c)
{
    return (a*b-(long long)((long double)a*b/c)*c+c)%c;
}
long long quick_pow (long long a,long long b,long long c)
{
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
bool Miller_Rabin(long long p)
{
    const long long time=50;
    if(p==2)
        return 1;
    if(p<2 || p%2==0)
        return 0;
    long long m=p-1;
    long long r=0;
    //p-1=2^r*m
    while(m%2==0)
    {
        r++;
        m>>=1;
    }
    for(long long i=1;i<=time;i++)
    {
        long long a=rand()%(p-1)+1;//[1,p-1]
        long long x=quick_pow(a,m,p);
        long long tmp=0;
        for(long long j=0;j<r;j++)
        {
            tmp=quick_mul(x,x,p);
            if(tmp==1 && x!=1 && x!=p-1)
                return 0;
            x=tmp;
        }
        if(tmp!=1)
            return 0;
    }
    return 1;
}
long long Pollard_rho(long long n,long long c)
{
    long long i=1,k=2,x2=rand()%(n-2)+1,x1=x2;
    while(1)
    {
        i++;
        x2=(quick_mul(x2,x2,n)+c)%n;
        long long p=__gcd((x1-x2+n)%n,n);//gcd(x1-x2,n);
        if(p!=1 && p!=n)
            return p;
        if(x1==x2)
            return n;
        if(i==k)
        {
            x1=x2;
            k<<=1;
        }
    }
}
void Find(long long n,long long c)
{
    if(n==1)
    {
        return;
    }
    if(Miller_Rabin(n))
    {
        if(P.find(n)!=P.end())
        {
            P[n]++;
        }
        else
        {
            P[n]=1;
        }
        return;
    }
    long long p=n,k=c;
    while(p>=n)
    {
        p=Pollard_rho(p,c--);
    }
    Find(p,k);
    Find(n/p,k);//递归求解
}
int main()
{
    P.clear();
    srand((unsigned)time(NULL));
    long long n;
    scanf("%lld",&n);
    if(Miller_Rabin(n))
    {
        printf("%lld is a Prime!\n",n);
    }
    else
    {
        Find(n,2333);
        printf("%lld=",n);
        for(auto i:P)
        {
            printf("%lld^%lld*",i.first,i.second);
        }
        printf("\n");
    }
} 