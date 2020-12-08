const ll mod=998244353;//模数
ll g=3;//原根
ll rev[maxn+10];
ll quick_pow(ll a, ll b)
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
int getBit(int k)
{
    int bit=1;
    while(bit<(n<<1)) bit<<=1;
    for(int i=0; i<bit; i++) tr[i]=(tr[i>>1]>>1)|(i&1 ? bit>>1 : 0);
    return len;
}
void NTT(ll *a, int n, int flag)
//flag是1时是系数转点值,-1是点值转系数
{
    for(int i=0; i<n; ++i)
    {
        if (i<rev[i]) swap(a[i], a[rev[i]]);
    }
    for(int mid=1; mid<n; mid*=2)
    {
        ll w=quick_pow(g, (mod-1)/(mid*2));//单位根
        if (flag==-1)
            w=quick_pow(w, mod-2);//INTT变换用
        for(int i=0; i<n; i+=mid*2)
        {
            ll omega=1;
            for(int j=0; j<mid; j++, omega=(ll) omega*w%mod)
            {
                ll x=a[i+j]%mod;
                ll y=(ll) omega*a[i+j+mid]%mod;
                a[i+j]=(x+y)%mod;
                a[i+j+mid]=(x-y+mod)%mod;
            }
        }
    }
}