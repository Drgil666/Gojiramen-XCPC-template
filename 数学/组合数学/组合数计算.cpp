const int maxn=1e3;
const ll mod=1e9+7;//Ä£Êý
ll factor[maxn+10];
ll invFactor[maxn+10];
void init()
{
    factor[0] = 1;
    for (int i = 1; i <= maxn; i++)
        factor[i] = i * factor[i - 1] % mod;
    invFactor[maxn] = quick_pow(factor[maxn], mod - 2);
    for (int i = maxn; i >= 1; i--) invFactor[i - 1] = invFactor[i] * i % mod;
}
ll C(ll n, ll m)
{
    if(n<0 || m<0 || n<m)
        return 0;
    ll sum=factor[n];
    sum=(ll) sum*invFactor[n-m]%mod;
    sum=(ll) sum*invFactor[m]%mod;
    return sum;
}