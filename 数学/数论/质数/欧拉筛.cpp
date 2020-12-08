const int maxn=1e5;
int prime[maxn+10];
int vis[maxn+10];
//欧拉筛：复杂度O(n)
int sieve(int siz)
{
    for(int i=2; i<=siz; i++)
    {
        if (!vis[i])
        {
            prime[++prime[0]]=i;
        }
        for(int j=1; j<=prime[0] && i*prime[j]<=siz; j++)
        {
            vis[i*prime[j]]=1;
            if (i%prime[j]==0)
            {
                break;
            }
        }
    }
    return prime[0];
}