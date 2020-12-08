namespace ST
{
    const int logn=30;
    int f[maxn+10][logn], Log[maxn+10];
    void init_log()
    {
        Log[0]=-1;
        Log[1]=0;
        Log[2]=1;
        for(int i=3; i<maxn; i++)
        {
            Log[i]=Log[i/2]+1;
        }
    }
    void build(int n, int *a)
    {
        for(int i=1; i<=n; i++)
        {
            f[i][0]=a[i];
        }
        init_log();
        for(int j=1; j<=logn; j++)
        {
            for(int i=1; i+(1<<j)-1<=n; i++)
            {
                f[i][j]=min(f[i][j-1], f[i+(1<<(j-1))][j-1]);
            }
        }
    }
    int query(int l, int r)
    {
        if (l>r)
            swap(l, r);
        l++;
        int s=Log[r-l+1];
        return min(f[l][s], f[r-(1<<s)+1][s]);
    }
}