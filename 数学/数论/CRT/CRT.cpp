//模数要两两互质
#define ll long long
ll extended_gcd(ll a, ll b, ll &x, ll &y)
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
ll Solve_gcd(ll a, ll b, ll c)//solve ax+by=c
{
    ll x, y;
    ll gcd=extended_gcd(a, b, x, y);
    if (c%gcd)
        return -1;
    x=x*(c/gcd);
    ll t=abs(b/gcd);
    if (x>0)
        x%=t;
    else
        x=x%t+t;//最小正整数解
    return x;
}
ll Inv(ll a, ll p)//(ax=1(mod p))
{
    return Solve_gcd(a, -p, 1);
}
ll CRT(ll n, ll *a, ll *b)//num是个数,a是除数,b是余数
{
    ll mod=1;
    for(int i=1; i<=n; i++)
    {
        mod*=a[i];
    }
    ll ans=0;
    for(int i=1; i<=n; i++)
    {
        ll x=b[i]*(mod/a[i])%mod*Inv(mod/a[i],a[i])%mod;
        ans=(ans+x)%mod;
    }
    return ans;
}