#include <bits/stdc++.h>
using namespace std;
#define ll long long
const int maxn=500;
namespace GeneratingFunction
{
    ll ans1[maxn+10], ans2[maxn+10];
    ll a[120+10];//������Ʒ�ļ�ֵ
    ll b[120+10];//ÿ����Ʒ�ĸ���
    ll N=0;//�����ϵ����ֵ
    ll ItemCount=0;//��Ʒ����
    void GetValue()//Ȩֵ
    {

    }
    void GetStock()//ÿ����Ʒ�ĸ���
    {

    }
    void solve()
    {
        memset(ans1, 0, sizeof(ans1));
        memset(ans2, 0, sizeof(ans2));
        for(int i=0; i<=min(N/a[1], b[1]); i++)//��ʼ��
        {
            ans1[i*a[1]]=1;
        }
        for(int i=2; i<=ItemCount; ++i)//ö�ٵ�i������ʽ(��1����ϵ���Ѿ�����ʼ�������Դ�2��ʼ)
        {
            for(int j=0; j<=N; ++j)//ö�ٽ����ʽ��(һ��N+1��)
            {
                for(int k=0; j+k<=N && k<=b[i]*a[i]; k+=a[i])//k���ǵ�i��ʽ�ӵ�ÿһ���ϵ��
                {
                    ans2[j+k]+=ans1[j];
                }
            }
            for(int j=0; j<=N; ++j)//����
            {
                ans1[j]=ans2[j];
                ans2[j]=0;
            }
        }
        //��������ans1����ش�����
    }
};
void solve()
{
}