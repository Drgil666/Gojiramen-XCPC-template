//埃式筛法：复杂度O(nlognlogn)
const int maxn=1e5;
int prime[maxn+10];//素数数组
bool is_prime[maxn+10];//is_pri[i]表示i是素数
//返回n以内素数的个数
int sieve(int siz)
{
    for(int i=0; i<=siz; i++)
        is_prime[i]=true;
    is_prime[0]=is_prime[1]=false;//首先标记0和1不是素数
    is_prime[2]=true;//标记2是素数
    prime[0]=0;
    for(int i=2; i<=siz; i++)
    {
        if (is_prime[i]) //如果i是素数
        {
            prime[++prime[0]]=i;//将素数放进素数表
            for(int j=i*i; j<=siz; j+=i)//所有i的倍数都不是素数
                is_prime[j]=false;
        }
    }
    return prime[0];
}