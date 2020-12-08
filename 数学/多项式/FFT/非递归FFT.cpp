const double pi=acos(-1.0);
#define cp complex<double>
ll rev[maxn+10];
int getBit(int k)
{
    int bit=1;
    while(bit<(n<<1)) bit<<=1;
    for(int i=0; i<bit; i++) tr[i]=(tr[i>>1]>>1)|(i&1 ? bit>>1 : 0);
    return len;
}
void FFT(cp *a, int n, int flag)
//inv是1时是系数转点值,-1是点值转系数
{
    for(int i=0; i<n; ++i)
    {
        if (i<rev[i]) swap(a[i], a[rev[i]]);
    }
    for(int mid=1; mid<n; mid*=2)
    {
        cp w(cos(pi*1.0/mid), flag*sin(pi*1.0/mid));//单位根
        for(int i=0; i<n; i+=mid*2)
        {
            cp omega(1, 0);
            for(int j=0; j<mid; j++, omega*=w)
            {
                cp x=a[i+j];
                cp y=omega*a[i+j+mid];
                a[i+j]=x+y;
                a[i+j+mid]=x-y;
            }
        }
    }
}