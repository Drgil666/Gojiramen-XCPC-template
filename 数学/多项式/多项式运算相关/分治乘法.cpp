void part_mul(ll *f1, ll *f2, ll *g, int l, int r) {
    if (l == r) return (void) (g[(l - 1) * 2] = f1[l], g[(l - 1) * 2 + 1] = f2[l]);
    int mid = (l + r) / 2;
    part_mul(f1, f2, g, l, mid);
    part_mul(f1, f2, g, mid+1, r);
    static ll a[maxn], b[maxn];
    int len1 = mid - l + 2, len2 = r - mid + 1;
    for (int i = 0; i < len1; i++) a[i] = g[(l - 1) * 2 + i];
    for (int i = 0; i < len2; i++) b[i] = g[mid * 2 + i];
    int n = r - l + 2, len = getBit(n);
    NTT(a, len, 1), NTT(b, len, 1);
    for (int i = 0; i < len; i++) a[i] = a[i] * b[i] % mod;
    NTT(a, len, -1);
    for (int i = 0; i < n; i++) g[(l - 1) * 2 + i] = a[i];
    for (int i = n; i < len; i++) g[(l - 1) * 2 + i] = 0;
    for (int i = 0; i < len; i++) a[i] = b[i] = 0;
}
