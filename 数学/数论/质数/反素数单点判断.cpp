#include<bits/stdc++.h>
using namespace std;
//反素数，记g(x)为x约数个数
//若x满足对于全体0<i<x,g(x)>g(i),则g为反素数
//性质1:一个反素数质因子必然是从2开始的连续整数
//性质2:p=2^k1*3^k2*5^k3...,有k1>=k2>=k3
long long prime[20]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
//前10个质因子的乘积大于1e9
//唯一分解后，所有质数的指数之和小于30,所以可以暴力
long long num_prime=16LL;
bool check_anti_prime(long long n)
{
    long long pow[20];
    memset(pow,0,sizeof(0));
    long long factor=0;
    for(int i=1;i<=num_prime;i++)
    {
        if(n%prime[i]==0)
        {
            factor++;
            while(n%prime[i]==0)
            {
                n/=prime[i];
                pow[factor]++;
            }
        }
        else
            break;//必定连续质因子
    }
    if(n!=1)
        return 0;//剩下如果还有得多，说明肯定不是反素数
    for(int i=1;i<=factor-1;i++)
    {
        if(pow[i]<pow[i+1])
            return 0;
    }
    return 1;
}
int main()
{
    long long n;
    scanf("%lld",&n);
    printf("%s\n",check_anti_prime(n)?"YES":"NO");
}