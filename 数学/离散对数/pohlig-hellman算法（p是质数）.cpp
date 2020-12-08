#include<bits/stdc++.h>
using namespace std;
const long long numprime=2;
//分解质因子可以用pollard-rho
long long prime[numprime+1]={0, 2, 3};//因子
long long factor[numprime+1]={0};//因子次数
long long xishu[200]={0};//系数
long long pow_prime[200];//pi^k
long long numc=0LL;
long long crta[numprime+1], crtb[numprime+1];//a是余数，b是模数
long long quick_mul(long long a, long long b, long long c)//快速乘
{
    return (a*b-(long long) ((long double) a*b/c)*c+c)%c;
}
long long quick_pow(long long a, long long b, long long c)//快速幂
{
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
void fenjie(long long p)//分解质因子
{
    long long p0=p-1;
    for(int i=1; i<=numprime; i++)
    {
        factor[i]=0;
        while(p0%prime[i]==0)
        {
            factor[i]++;
            p0/=prime[i];
        }
    }
}
bool check(long long a, long long p)//判断原根
{
    for(int i=1; i<=numprime; i++)
    {
        if (quick_pow(a, (p-1)/prime[i], p)==1)
            return 0;
    }
    return 1;
}
long long Root(long long p)//遍历找原根
{
    for(long long g=1;; g++)
    {
        int flag=1;
        for(int j=1; j<=numprime; j++)
        {
            if (quick_pow(g, (p-1)/prime[j], p)==1)
            {
                flag=0;
                break;
            }
        }
        if (flag)
            return g;
    }
}
long long extended_gcd(long long a, long long b, long long &x, long long &y)
//扩展gcd
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
long long Inv(long long a, long long mod)//找逆元，ax=1(%mod)
{
//    printf("check?\n");
    long long p, x, y;
    p=extended_gcd(a, mod, x, y);//p是gcd=1
    x=x;
    long long t=mod;
    if (x>=0)
        x=x%t;
    else
    {
        while(x<0)
            x+=t;
        x%t;
    }//负数要加上t
    if (x==0)
        x+=t;
//    printf("check!\n");
    return x;
}
long long CRT(long long numc, long long a[], long long b[], long long p)
//普通CRT，不是扩展CRT
{
    long long ans=0;
    long long mod=p-1;
    for(long long i=1; i<=numc; i++)
    {
        long long x1=quick_mul(a[i]%mod, mod/b[i]%mod, mod);
        x1=quick_mul(x1%mod, Inv(mod/b[i], b[i])%mod, mod);
        ans=(ans+x1+mod)%mod;
    }
    return ans;
}
long long pohlig_hellman(long long g, long long b, long long p)
//g是原根！
{
    numc=0;
    //g^x=b(mod p)
    memset(crta, 0, sizeof(crta));
    memset(crtb, 0, sizeof(crtb));
    for(int i=1; i<=numprime; i++)//枚举每个质因子
    {
        memset(xishu, 0, sizeof(xishu));
        pow_prime[0]=1;
        for(int j=1; j<=factor[i]+1; j++)
        {
            pow_prime[j]=pow_prime[j-1]*prime[i];
        }
        long long sum=1;
        long long yushu=0, moshu=pow_prime[factor[i]];
        for(int j=1; j<=factor[i]; j++)//求出每个系数
        {
//            printf ("solve %lld*(%lld^%lld)^x=%lld^%lld(mod %lld)\n",sum,g,(p-1)/prime[i],b,(p-1)/pow_prime[j],p);
            long long a0=quick_pow(g, (p-1)/prime[i], p);
            long long b0=quick_pow(b, (p-1)/pow_prime[j], p);
            for(long long x=0; x<=prime[i]-1; x++)//遍历找出系数x
            {
                if (quick_mul(sum, quick_pow(a0, x, p), p)==b0)
                {
//                    printf ("find x:%lld\n",x);
                    xishu[j]=x;
                    long long xs=0;
                    for(long long k=1; k<=j; k++)
                    {
                        xs=(xs+(pow_prime[k-1]*xishu[k]%(p-1))+p-1)%(p-1)+p-1;
                    }
//                    printf ("xs=%lld\n",xs);
                    sum=quick_pow(g, quick_mul(xs, (p-1)/pow_prime[j+1], p-1)+p-1, p);
                    break;
                }
            }
            yushu+=pow_prime[j-1]*xishu[j];
        }
        if (factor[i])
        {
//            printf ("x==%lld(mod %lld)\n",yushu,moshu);
            numc++;
            crta[numc]=yushu;
            crtb[numc]=moshu;
        }
    }
//    printf("numc=%lld\n",numc);
//	printf("\n\n");
//    for(int i=1;i<=numc;i++)
//    {
//        printf("x=%lld(mod %lld)\n",crta[i],crtb[i]);
//    }
//    printf("\n\n");
    return CRT(numc, crta, crtb, p);
}
void solve1()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        long long a, b, p, g, xx, yy, rr, x1, x2;
        scanf("%lld%lld%lld", &p, &a, &b);
        fenjie(p);
        if (check(a, p))// if a is a root
        {
            printf("%lld\n", pohlig_hellman(a, b, p));
            continue;
        }
        g=Root(p);
//        printf ("%lld's Primitive Root :%lld\n",p,g);
        x1=pohlig_hellman(g, a, p);
        x2=pohlig_hellman(g, b, p);
//        printf("solve %lldx=%lld(mod %lld)\n",x1,x2,p-1);//x1x=x2(mod p-1)
        rr=extended_gcd(x1, p-1, xx, yy);
//        printf("gcd=%lld\n",rr);
        if (x2%rr!=0)
        {
            printf("-1\n");
            continue;
        }
        long long tt=(p-1)/rr;
        if (xx>=0)
        {
            xx=quick_mul(xx, (x2/rr), tt);
        }
        else
        {
            xx=xx%tt+tt;
            xx=quick_mul(xx, (x2/rr), tt);
        }
        printf("%lld\n", xx);
    }
}