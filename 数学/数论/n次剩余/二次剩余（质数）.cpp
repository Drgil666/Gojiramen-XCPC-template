#include<bits/stdc++.h>
using namespace std;
//如果p是奇质数，x^2=1(mod p)解为x=1或者x=p-1(mod p)
typedef struct
{
    long long x,y;//把求出的w作为虚部,a+bw
}num;
num num_mul(num a,num b,long long w,long long p)//复数乘法 
{
    num ans=num{0,0};
    ans.x=((a.x*b.x%p+a.y*b.y%p*w%p)%p+p)%p;
    ans.y=((a.x*b.y%p+a.y*b.x%p)%p+p)%p;
    return ans;
}
long long num_pow(num a,long long b,long long w,long long p)
{
    num ans=num{1,0};
    while(b)
    {
        if(b&1)
        {
            ans=num_mul(ans,a,w,p);
        }
        a=num_mul(a,a,w,p);
        b>>=1;
    }
    return ans.x%p;
}
long long quick_pow (long long a,long long b,long long c)//快速幂
{
    long long ans=1,base=a;
    while (b!=0)
    {
        if (b&1)
            ans=ans*base%c;
        base=base*base%c;
        b>>=1;
    }
    return ans%c;
}
long long legander(long long a,long long p)
{
    long long ans=quick_pow(a,(p-1)/2,p);
    if(ans+1==p)
        return -1;
    return ans;
}
long long Cipolla(long long n,long long p)
{
    n%=p;
    if(quick_pow(n,(p-1)/2,p)==p-1)
        return -1;//不存在
    long long a;
    long long w;
    while(1)
    {
        a=rand()%p;//随机成功的概率是50%,故期望次数为2
        w=((1LL*a*a-n)%p+p)%p;
//        printf("a=%lld w=%lld\n",a,w);
        if(legander(w,p)==-1)//找到w
            break;
    }
    num x={a,1};//代表a+w
    return num_pow(x,(p+1)/2,w,p);//由拉格朗日定理可以知道虚部为0
}
int main()
{
    srand((unsigned)time(NULL));
    long long n=17,p=998244353;
    printf("%lld\n",Cipolla(n,p));//一个解是x,另一个是p-x
} 