#define ll long long
const int maxn=1e5;
int f[maxn+10];//f��ʾ�ܸı�ķ�ʽ
int SG[maxn+10];//ע�⣬SG�����Ƕ�ά�ȣ�fҲ����
bool S[maxn+10];//���״̬����
void getSG(int n)//�ܲ��ĵ�SG����Ϊ����SG���������Nim�ͣ�
{
    memset(SG, 0, sizeof(SG));//SG[0]=0
    for(int i=1; i<=n; i++)
    {
        memset(S, false, sizeof(S));
        for(int j=0; f[j]<=i && j<=n; j++)
        {
            S[SG[i-f[j]]]=true;
        }
        for(int j=0;; j++)//mex(S)
        {
            if (!S[j])
            {
                SG[i]=j;
                break;
            }
        }
    }
}
