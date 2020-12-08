#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=2e6;
const double pi=acos(-1.0);
#define cp complex<double>
char s1[maxn+10], s2[maxn+10];
cp a1[maxn+10], a2[maxn+10], a3[maxn+10];
cp b[maxn+10];
int ans[maxn+10];
int tobit(int k)
{
    int bit=0;
    while((1<<bit)<k)
        bit++;
    return 1<<bit;
}
void FFT(cp *a, int n, int inv)
//inv是1时是系数转点值,-1是点值转系数
{
    if (n==1)
        return;
    int mid=n/2;
    for(int i=0; i<mid; ++i)
    {
        b[i]=a[i*2];
        b[i+mid]=a[i*2+1];
    }
    for(int i=0; i<n; ++i)
    {
        a[i]=b[i];
    }
    FFT(a, mid, inv);
    FFT(a+mid, mid, inv);
    for(int i=0; i<mid; ++i)
    {
        cp w(cos(2.0*pi*i/n), inv*sin(2.0*pi*i/n));//w是单位根
        b[i]=a[i]+w*a[i+mid], b[i+mid]=a[i]-w*a[i+mid];
    }
    for(int i=0; i<n; ++i)
    {
        a[i]=b[i];
    }
    return;
}
void solve()
{
    scanf("%s%s", s1, s2);
    int len1=strlen(s1), len2=strlen(s2);
    for(int i=len1-1; i>=0; i--)
    {
        a1[len1-1-i].real((s1[i]-'0')*1.0);
        a1[len1-1-i].imag(0.0);
    }
    for(int i=len2-1; i>=0; i--)
    {
        a2[len2-1-i].real((s2[i]-'0')*1.0);
        a2[len2-1-i].imag(0.0);
    }
    int len3=tobit(len1+len2);
//    printf("len1=%d len2=%d len3=%d\n", len1, len2, len3);
    FFT(a1, len3, 1);
    FFT(a2, len3, 1);
    for(int i=0; i<len3; i++)
    {
        a3[i]=a1[i]*a2[i];
    }
    FFT(a3, len3, -1);
    for(int i=0; i<len3; ++i)
    {
        ans[i]=(int) (a3[i].real()/len3+0.5);
    }
    for(int i=0; i<len3; ++i)
    {
        if (ans[i]>=10)
        {
            if (i==len3-1)
            {
                len3++;
            }
            ans[i+1]+=ans[i]/10;
            ans[i]%=10;
        }
    }
    int index=len3-1;
    for(int i=len3-1; i>=0; i--)
    {
        if (ans[i])
        {
            index=i;
            break;
        }
    }
    for(int i=index; i>=0; i--)
        printf("%d", ans[i]);
}
signed main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    long long test_index_for_debug=1;
    char acm_local_for_debug;
    while(cin>>acm_local_for_debug)
    {
        cin.putback(acm_local_for_debug);
        if (test_index_for_debug>100)
        {
            throw runtime_error("Check the stdin!!!");
        }
        auto start_clock_for_debug=clock();
        solve();
        auto end_clock_for_debug=clock();
        cout<<"\nTest "<<test_index_for_debug<<" successful"<<endl;
        cerr<<"Test "<<test_index_for_debug++<<" Run Time: "
            <<double(end_clock_for_debug-start_clock_for_debug)/CLOCKS_PER_SEC<<"s"<<endl;
        cout<<"--------------------------------------------------"<<endl;
    }
#else
    solve();
#endif
    return 0;
}