#include<bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=1e6;
const ll mod=998244353;//模数
ll G=3;//原根
ll rev[maxn+10];
inline ll read()
{
    register ll num=0, neg=1;
    register char ch=getchar();
    while(!isdigit(ch) && ch!='-')
    {
        ch=getchar();
    }
    if (ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=(num<<3)+(num<<1)+(ch-'0');
        ch=getchar();
    }
    return num*neg;
}
inline ll read_mod(ll mod)
{
    register ll num=0, neg=1;
    register char ch=getchar();
    while(!isdigit(ch) && ch!='-')
    {
        ch=getchar();
    }
    if (ch=='-')
    {
        neg=-1;
        ch=getchar();
    }
    while(isdigit(ch))
    {
        num=((num<<3)+(num<<1)+(ch-'0'))%mod;
        ch=getchar();
    }
    return num*neg;
}
ll quick_pow(ll a, ll b, ll mod)
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
ll invG=quick_pow(G, mod-2, mod);
ll inv2=quick_pow(2LL, mod-2, mod);
int getLen(int n)
{
    int len=1;
    while(len<(n<<1)) len<<=1;
    for(int i=0; i<len; i++)
    {
        rev[i]=(rev[i>>1]>>1)|(i&1 ? len>>1 : 0);
    }
    return len;
}
struct Complex { ll x, y; };
ll w;
void getDer(ll *f, ll *g, int len)
{
    for(int i=1; i<len; i++) g[i-1]=f[i]*i%mod;
    g[len-1]=0;
}
void getInt(ll *f, ll *g, int len)
{
    for(int i=1; i<len; i++) g[i]=f[i-1]*quick_pow(i, mod-2, mod)%mod;
    g[0]=0;
}
Complex mul(Complex a, Complex b, ll mod)
{
    Complex ans={0, 0};
    ans.x=((a.x*b.x%mod+a.y*b.y%mod*w%mod)%mod+mod)%mod;
    ans.y=((a.x*b.y%mod+a.y*b.x%mod)%mod+mod)%mod;
    return ans;
}
ll binpow_imag(Complex a, ll b, ll mod)
{
    Complex ans={1, 0};
    while(b)
    {
        if (b&1) ans=mul(ans, a, mod);
        a=mul(a, a, mod);
        b>>=1;
    }
    return ans.x%mod;
}
ll cipolla(ll n, ll mod)
{
    srand(time(0));
    n%=mod;
    if (mod==2) return n;
    if (quick_pow(n, (mod-1)/2, mod)==mod-1) return -1;
    ll a;
    while(1)
    {
        a=rand()%mod;
        w=((a*a%mod-n)%mod+mod)%mod;
        if (quick_pow(w, (mod-1)/2, mod)==mod-1) break;
    }
    Complex x={a, 1};
    return binpow_imag(x, (mod+1)/2, mod);
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
        ll w=quick_pow(G, (mod-1)/(mid*2), mod);//单位根
        if (flag==-1)
            w=quick_pow(w, mod-2, mod);//INTT变换用
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
    if (flag==-1)
    {
        ll invn=quick_pow(n, mod-2, mod);
        for(int i=0; i<n; ++i)
        {
            a[i]=a[i]*invn%mod;
        }
    }
}
void Poly_Inv(ll *f, ll *g, int n)
{
    if (n==1)
    {
        g[0]=quick_pow(f[0], mod-2, mod);
        return;
    }
    Poly_Inv(f, g, (n+1)>>1);
    int limit=getLen(n);
    static ll a[maxn+10];
    for(int i=0; i<limit; ++i)
    {
        a[i]=i<n ? f[i] : 0;
    }
    NTT(a, limit, 1);
    NTT(g, limit, 1);
    for(int i=0; i<limit; ++i)
    {
        g[i]=1LL*(2-1LL*a[i]*g[i]%mod+mod)%mod*g[i]%mod;
    }
    NTT(g, limit, -1);
    for(int i=n; i<limit; ++i)
    {
        g[i]=0;
    }
}
void Poly_Sqrt(ll *f, ll *g, int n)
{
    if (n==1)
    {
        if (f[0]==0)
        {
            g[0]=f[0];
        }
        else
        {
            ll t=cipolla(f[0], mod);
            g[0]=min(t, mod-t);
        }
        return;
    }
    Poly_Sqrt(f, g, (n+1)>>1);
    int len=getLen(n);
    static ll a[maxn+10], b[maxn+10];
    for(int i=0; i<len; ++i)
    {
        a[i]=i<n ? f[i] : 0;
    }
    Poly_Inv(g, b, n);
    NTT(a, len, 1);
    NTT(b, len, 1);
    for(int i=0; i<len; ++i)
    {
        a[i]=1LL*a[i]*b[i]%mod;
    }
    NTT(a, len, -1);
    for(int i=0; i<n; ++i)
    {
        g[i]=(g[i]+a[i])%mod*inv2%mod;
    }
    for(int i=n; i<len; ++i)
    {
        g[i]=0;
    }
    for(int i=0; i<len; ++i)
    {
        a[i]=b[i]=0;
    }
}
void Poly_Ln(ll *f, ll *g, int n)
{
    static ll a[maxn+10], b[maxn+10];
    getDer(f, a, n);
    Poly_Inv(f, b, n);
    int len=getLen(n);
    NTT(a, len, 1), NTT(b, len, 1);
    for(int i=0; i<len; i++) a[i]=a[i]*b[i]%mod;
    NTT(a, len, -1);
    getInt(a, g, len);
    for(int i=n; i<len; i++) g[i]=0;
    for(int i=0; i<len; i++) a[i]=b[i]=0;
}
void Poly_Exp(ll *f, ll *g, int n)
{
    if (n==1) return (void) (g[0]=1);
    Poly_Exp(f, g, (n+1)>>1);
    static ll a[maxn+10];
    Poly_Ln(g, a, n);
    a[0]=(f[0]+1-a[0]+mod)%mod;
    for(int i=1; i<n; i++) a[i]=(f[i]-a[i]+mod)%mod;
    int len=getLen(n);
    NTT(a, len, 1), NTT(g, len, 1);
    for(int i=0; i<len; i++) g[i]=g[i]*a[i]%mod;
    NTT(g, len, -1);
    for(int i=n; i<len; i++) g[i]=0;
}
void Poly_Pow(ll *f, ll *g, int n, ll k)
{
    static ll a[maxn+10];
    Poly_Ln(f, a, n);
    for(int i=0; i<n; i++) a[i]=a[i]*k%mod;
    Poly_Exp(a, g, n);
    for(int i=0, len=getLen(n); i<len; i++) a[i]=0;
}
void Poly_ExPow(ll *f, ll *g, int n, ll k1, ll k2)
//k1为原始幂数, k2为幂数模phi(mod - 1)
{
    int pos=0;
    while(pos<n && !f[pos]) pos++;
    if (k1*pos>=n)
    {
        for(int i=0; i<n; i++) g[i]=0;
        return;
    }
    static ll a[maxn+10], b[maxn+10];
    int m=n-pos, inv=quick_pow(f[pos], mod-2, mod), t=quick_pow(f[pos], k2, mod);
    for(int i=0; i<m; i++) a[i]=f[i+pos]*inv%mod;
    Poly_Ln(a, b, m);
    for(int i=0; i<m; i++) b[i]=b[i]*k1%mod;
    Poly_Exp(b, g, m);
    for(int i=0; i<m; i++) g[i]=g[i]*t%mod;
    pos=min(1ll*pos*k1, 1ll*n);
    for(int i=n-1; i>=pos; i--) g[i]=g[i-pos];
    for(int i=pos-1; i>=0; i--) g[i]=0;
    for(int i=0, len=getLen(m); i<len; i++) a[i]=b[i]=0;
}