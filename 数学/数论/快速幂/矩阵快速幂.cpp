#include <bits/stdc++.h>
using namespace std;
#define ll long long
const long long mod=1e9+7;
const int maxn=5;
ll ax, bx, ay, by;
struct matrix
{
    ll m[maxn][maxn];
    void print()
    {
        for(int i=0; i<maxn; i++)
        {
            for(int j=0; j<maxn; j++)
            {
                printf("%d ", m[i][j]);
            }
            printf("\n");
        }
    }
};
matrix I={1, 0, 0, 0, 0,
          0, 1, 0, 0, 0,
          0, 0, 1, 0, 0,
          0, 0, 0, 1, 0,
          0, 0, 0, 0, 1};
matrix mul(matrix A, matrix B)
{
    matrix C;
    for(int i=0; i<maxn; i++)//枚举行
        for(int j=0; j<maxn; j++)//枚举列
        {
            C.m[i][j]=0;
            for(int k=0; k<maxn; k++)
                C.m[i][j]=(C.m[i][j]+((A.m[i][k]+mod)%mod)*((B.m[k][j]+mod)%mod)+mod)%mod;
        }
    return C;
}
matrix pow(matrix A, ll n)
{
    matrix ret=I;
    while(n)
    {
        if (n&1)
            ret=mul(ret, A);
        A=mul(A, A);
        n>>=1;
    }
    return ret;
}
void solve()
{
    ll n;
    while(~scanf("%lld", &n))
    {
        ll a0, b0;
        scanf("%lld%lld%lld%lld%lld%lld", &a0, &ax, &ay, &b0, &bx, &by);
        if (n==0)
        {
            printf("0\n");
            continue;
        }
        a0%=mod;
        ax%=mod;
        ay%=mod;
        b0%=mod;
        bx%=mod;
        by%=mod;
        matrix A;
        A.m[0][0]=A.m[1][0]=a0*b0%mod;
        A.m[2][0]=a0;
        A.m[3][0]=b0;
        A.m[4][0]=1;
//        A.print();
        matrix ret;
        ret.m[0][0]=ret.m[4][4]=1;
        ret.m[0][1]=ret.m[1][1]=(long long) ax*bx%mod;
        ret.m[0][2]=ret.m[1][2]=(long long) ax*by%mod;
        ret.m[0][3]=ret.m[1][3]=(long long) ay*bx%mod;
        ret.m[0][4]=ret.m[1][4]=(long long) ay*by%mod;
        ret.m[1][0]=0;
        ret.m[2][0]=0;
        ret.m[2][1]=0;
        ret.m[2][2]=ax;
        ret.m[2][3]=0;
        ret.m[2][4]=ay;
        ret.m[3][0]=ret.m[3][1]=ret.m[3][2]=0;
        ret.m[3][3]=bx;
        ret.m[3][4]=by;
        ret.m[4][0]=ret.m[4][1]=ret.m[4][2]=ret.m[4][3]=0;
        matrix ans=pow(ret, n-1);
//        ret.print();
//        ans.print();
        ll answer=0;
        for(int i=0; i<maxn; i++)
        {
            answer=(answer+ans.m[0][i]*A.m[i][0]%mod)%mod;
        }
        printf("%lld\n", answer%mod);
    }
}
int main()
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