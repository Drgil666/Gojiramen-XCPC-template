inline long long quick_mul (long long a,long long b,long long c)//快速乘
{
    return (a*b-(long long)((long double)a/c*b)*c+c)%c;
}//O(1)快速乘的限制很大,mod要很大才可以
inline ll quick_mul (ll a,ll b,ll c)//快速乘
{
    ll ans=0, base=a;
    while(b!=0)
    {
        if (b&1)
            ans=(ll) (ans+base)%c;
        base=(ll) base*2%c;
        b>>=1;
    }
    return ans;
}
inline ll quick_mul (ll a,ll b,ll c)//快速乘
{
    ll ans=0, base=a;
    while(b!=0)
    {
        if (b&1)
            ans=(ll) (ans+base)%c;
        base=(ll) base*2%c;
        b>>=1;
    }
    return ans;
}
inline long long quick_pow(long long a, long long b,long long mod)//快速幂
{
    long long ans=1, base=a;
    while(b!=0)
    {
        if (b&1)
            ans=(long long) ans*base%mod;
        base=(long long) base*base%mod;
        b>>=1;
    }
    return ans;
}