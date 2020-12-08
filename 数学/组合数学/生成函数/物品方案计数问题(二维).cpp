#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=500;
ll ans1[maxn+10][maxn+10], ans2[maxn+10][maxn+10];
//ans1[i][j]��ʾ��j����Ʒ��ֵΪi
ll a[120+10];//������Ʒ�ļ�ֵ
ll b[120+10];//ÿ����Ʒ�ĸ���
ll N=250;//�����ϵ����ֵ
ll ItemCount=5;//��Ʒ����
void solve()
{
    int n;
    a[1]=1;
    a[2]=5;
    a[3]=10;
    a[4]=25;
    a[5]=50;
    memset(ans1, 0, sizeof(ans1));
    memset(ans2, 0, sizeof(ans2));
    for(int i=0; i<=min(N/a[1],b[1]); i++)//��ʼ��
    {
        ans1[i*a[1]][i]=1;
    }
    for(int i=2; i<=ItemCount; ++i)//ö�ٵ�i������ʽ(��1����ϵ���Ѿ�����ʼ�������Դ�2��ʼ)
    {
        for(int j=0; j<=N; ++j)//ö�ٽ����ʽ��(һ��N+1��)
        {
            for(int k=0; j+k<=N && k<=a[i]*b[i]; k+=a[i])//k���ǵ�i��ʽ�ӵ�ÿһ���ϵ��
            {
                for(int l=0; l+k/a[i]<=min(N,b[i]); ++l)//��Ʒ����
                {
                    ans2[j+k][l+k/a[i]]+=ans1[j][l];
                }
            }
        }
        for(int j=0; j<=N; ++j)//����
        {
            for(int k=0; k<=N; k++)
            {
                ans1[j][k]=ans2[j][k];
                ans2[j][k]=0;
            }
        }
    }//��������ans1����ش�����
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