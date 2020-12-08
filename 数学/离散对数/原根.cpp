//root:2,4,p^k,2p^k
bool check(long long a,long long p)//判断是否是原根
{
    for(int i=1;i<=numprime;i++)
    {
        if(quick_pow (a,(p-1)/prime[i],p)==1)
            return 0;
    }
    return 1;
}
long long Root (long long p)//遍历寻找原根
{
    for (long long g=2;g<p;g++)
    {
        if(check(g,p))
            return g;
    }
}