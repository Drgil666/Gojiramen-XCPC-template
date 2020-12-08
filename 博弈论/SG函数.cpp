#define ll long long
const int maxn=1e5;
int f[maxn+10];//f表示能改变的方式
int SG[maxn+10];//注意，SG可以是多维度，f也可以
bool S[maxn+10];//后继状态集合
void getSG(int n)//总博弈的SG函数为所有SG函数的异或（Nim和）
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
