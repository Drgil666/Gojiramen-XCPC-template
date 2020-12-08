#include <bits/stdc++.h>
using namespace std;
const int mod=1e9+7;
long long quick_mod(long long a, long long b)
{
    long long ans=1;
    while(b)
    {
        if (b&1)
        {
            ans=(ans*a)%mod;
            b--;
        }
        b/=2;
        a=a*a%mod;
    }
    return ans;
}//内部也用快速幂
long long quick_log10_mod(long long a, char *b, int len)
{
    long long ans=1;
    while(len>0)
    {
        if (b[len-1]!='0')
        {
            int s=b[len-1]-'0';
            ans=ans*quick_mod(a, s)%mod;
        }
        a=quick_mod(a, 10)%mod;
        len--;
    }
    return ans;
}
int main()
{
    char s[100050];
    int a;
    while(~scanf("%d", &a))         //求a^s%mod
    {
        scanf("%s", s);
        int len=strlen(s);
        printf("%I64d\n", quick_log10_mod(a, s, len));
    }
    return 0;
}