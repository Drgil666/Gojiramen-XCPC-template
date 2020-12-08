void Part_FFT(ll *f, ll *g, int n) {
    //º∆À„g[i] = \sum_{j = 1}^{i} g[i - j] * f[j]
    static ll a[N];
    for (int i = 1; i < n; i++) a[i] = (mod - f[i]) % mod;//±‰∑˚∫≈
    a[0] = 1;
    ll g0 = g[0];
    getInv(a, g, n);
    for (int i = 0; i < n; i++) g[i] = g[i] * g0 % mod, a[i] = 0;
}