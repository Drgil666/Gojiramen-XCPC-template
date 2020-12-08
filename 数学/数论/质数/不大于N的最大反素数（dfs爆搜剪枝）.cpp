#include<bits/stdc++.h>
using namespace std;
long long prime[20]={0,2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53};
long long cnt[20];//第n个质因子的系数 
long long num_prime=16LL;
long long answer_max_anti_prime;
long long ant=0;
void dfs(int id,long long now,long long n)//id表示层数 
{
    if(id==num_prime+1)//到底了
    {
        long long tp=1;
        for(int i=1;i<=num_prime;i++)
            tp*=(cnt[i]+1);
        if(tp>ant)
        {
            ant=tp;
            answer_max_anti_prime=now;
        }
        else
        {
            if(tp==ant && now<answer_max_anti_prime)
                answer_max_anti_prime=now;
        }
        return;
    }
    cnt[id]=0;dfs(id+1,now,n);
    for(int i=1;i<=30;i++)//指数总和不超过30
    {
        now*=prime[id];
        if(now>n)
            break;
        cnt[id]=i;
        dfs(id+1,now,n);
    }
}
long long max_anti_prime(long long n)
{
    ant=0;
    dfs(1,1,n);
    return answer_max_anti_prime;
}
int main()
{
    int t,cnt=0;
    scanf("%d",&t);
    while(t--)
    {
        long long n;
        scanf("%lld",&n);
        printf("Case #%d: %lld\n",++cnt,max_anti_prime(n));
    }
}