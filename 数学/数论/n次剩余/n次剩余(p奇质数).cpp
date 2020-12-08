//对于x^a=b(mod p),p is odd prime
//1.find Root g,that x=g^c
//2.solve (g^c)^a=b(mod p)->solve (g^a)^c=b(mod p) with BSGS
//3.after find c,calculate x=g^c(mod p)
//4.find all solution for x:
//x=g^(c+i*phi(p)/(gcd(a,phi(p)))(mod p)
long long quick_mul (long long a,long long b,long long c)//快速乘
{
    return (a*b-(long long)((long double)a*b/c)*c+c)%c;
}
long long quick_pow (long long a,long long b,long long c)//快速幂
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
bool check(long long a,long long p)//判断原根
{
    for(int i=1;i<=numprime;i++)
    {
        if(quick_pow (a,(p-1)/prime[i],p)==1)
            return 0;
    }
    return 1;
}
long long Root (long long p)//遍历找原根
{
    for (long long g=1;;g++)
    {
        int flag=1;
        for (int j=1;j<=numprime;j++)
        {
            if (quick_pow (g,(p-1)/prime[j],p)==1)
            {
                flag=0;
                break;
            }
        }
        if (flag)
            return g;
    }
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
long long residue_n(long long a,long long b,long long p)
{
    long long g=Root(p);
    printf("Root: %lld\n",g);
    long long c=-1;
    printf("(%lld^%lld)^c=%lld(mod %lld)\n",g,a,b,p);
    return quick_pow(g,BSGS(quick_pow(g,a,p),b,p),p);
}
