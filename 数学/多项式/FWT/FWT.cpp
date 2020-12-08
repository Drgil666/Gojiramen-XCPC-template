namespace FWT
{
    void FWT_or(ll *P, int n, int opt)
    {
        for(int i=2; i<=n; i<<=1)
        {
            for(int p=i>>1, j=0; j<n; j+=i)
            {
                for(int k=j; k<j+p; ++k)
                {
                    P[k+p]+=P[k]*opt;
                }
            }
        }
    }
    void FWT_and(ll *P, int n, int opt)
    {
        for(int i=2; i<=n; i<<=1)
            for(int p=i>>1, j=0; j<n; j+=i)
                for(int k=j; k<j+p; ++k)
                    P[k]+=P[k+p]*opt;
    }
    void FWT_xor(int *P, int n, int opt)
    {
        for(int i=2; i<=n; i<<=1)
        {
            for(int p=i>>1, j=0; j<n; j+=i)
            {
                for(int k=j; k<j+p; ++k)
                {
                    int x=P[k], y=P[k+p];
                    P[k]=(x+y);
                    P[k+p]=x-y;
                    if (pot==-1)
                    {
                        P[k]/=inv2;
                        P[k+p]/=inv2;
                    }
                }
            }
        }
    }
}