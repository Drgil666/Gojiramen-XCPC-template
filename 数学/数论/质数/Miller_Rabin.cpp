#include<bits/stdc++.h>
using namespace std;
// Miller_Rabin进行素数测试
//速度快，而且可以判断 <2^63的数
//一个数不是质数的概率是(1/2)^判断次数 
//卡迈尔克数：
// 561, 41041, 825265, 321197185,
// 5394826801, 232250619601, 9746347772161,1436697831295441
// 60977817398996785, 7156857700403137441
inline long long quick_mul (long long a,long long b,long long c)//快速乘
{
    return (a*b-(long long)((long double)a/c*b)*c+c)%c;
}
long long quick_pow (long long a,long long b,long long c)
{
    long long ans=1,base=a;
    while (b!=0)
    {
        if (b&1)
            ans=(long long)ans*base%c;
        base=(long long)base*base%c;
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
int main()
{
    srand((unsigned)time(NULL));
    long long n;
    while(~scanf("%lld",&n))
    printf("%s",Miller_Rabin(n)?"YES":"NO");
} 