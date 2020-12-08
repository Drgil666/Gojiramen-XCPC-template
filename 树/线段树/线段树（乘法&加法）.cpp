#include <bits/stdc++.h>
using namespace std;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)//左儿子
#define rson(n) (n<<1|1)//右儿子
#define NodeType long long
const long long maxn=2e5;
long long mod;
NodeType a[maxn+10];
struct Node
{
    NodeType l=0, r=0, sum=0, add=0, mul=1;
    //左边界、右边界、区间和、加标记、乘标记
};
Node Tree[(maxn<<2)+10];
inline void Tree_build(int k, int l, int r)
//建树(当前节点编号,区间范围)
{
    Tree[k].l=l;
    Tree[k].r=r;
    Tree[k].mul=1;
    Tree[k].add=0;
    if (Tree[k].l==Tree[k].r)//叶子节点
    {
        Tree[k].sum=a[l]%mod;
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);//二分区间
    Tree[k].sum=(Tree[lson(k)].sum+Tree[rson(k)].sum)%mod;//更新最值
}
inline void Tree_pushdown(int k)//更新标记（待更新）
{
    if (Tree[k].add || Tree[k].mul!=1)
    {
        Tree[lson(k)].sum=((long long) Tree[lson(k)].sum*Tree[k].mul%mod+
                           (long long) ((Tree[lson(k)].r-Tree[lson(k)].l+1)*Tree[k].add%mod))%mod;
        Tree[lson(k)].mul=(long long) Tree[lson(k)].mul*Tree[k].mul%mod;
        Tree[lson(k)].add=(Tree[lson(k)].add*Tree[k].mul%mod+Tree[k].add)%mod;
        Tree[rson(k)].sum=((long long) Tree[rson(k)].sum*Tree[k].mul%mod+
                           (long long) ((Tree[rson(k)].r-Tree[rson(k)].l+1)*Tree[k].add%mod))%mod;
        Tree[rson(k)].mul=(long long) Tree[rson(k)].mul*Tree[k].mul%mod;
        Tree[rson(k)].add=(Tree[rson(k)].add*Tree[k].mul%mod+Tree[k].add)%mod;
        Tree[k].add=0;
        Tree[k].mul=1;
    }
    return;
}
inline void Tree_add(int k, int l, int r, long long x)
//当前结点，目标范围，要加的值
//考虑到加的是个负数所以取模时要加个mod
{
    if (Tree[k].r<l || Tree[k].l>r)
        return;
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        x=(x%mod+mod)%mod;
        Tree[k].sum=(long long) (Tree[k].sum+(Tree[k].r-Tree[k].l+1)*x%mod)%mod;
        Tree[k].add=(Tree[k].add+x+mod)%mod;
        return;
    }
    Tree_pushdown(k);
    if (l<=Tree[lson(k)].r)
    {
        Tree_add(lson(k), l, r, x);
    }
    if (Tree[rson(k)].l<=r)
    {
        Tree_add(rson(k), l, r, x);
    }
    Tree[k].sum=(Tree[lson(k)].sum+Tree[rson(k)].sum)%mod;
}
inline void Tree_multi(int k, int l, int r, long long x)
//当前结点，目标范围，要乘的值
{
//    printf("k=%d l=%d r=%d\n", k, l, r);
    if (Tree[k].r<l || Tree[k].l>r)
        return;
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        x%=mod;
        Tree[k].mul=(long long) (Tree[k].mul*x)%mod;
        Tree[k].add=(long long) (Tree[k].add*x)%mod;
        Tree[k].sum=(long long) (Tree[k].sum*x)%mod;
        return;
    }
    Tree_pushdown(k);
    if (l<=Tree[lson(k)].r)
    {
        Tree_multi(lson(k), l, r, x);
    }
    if (Tree[rson(k)].l<=r)
    {
        Tree_multi(rson(k), l, r, x);
    }
    Tree[k].sum=(Tree[lson(k)].sum+Tree[rson(k)].sum)%mod;
}
inline long long Tree_query(int k, int l, int r)
//当前结点、目标区间
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].sum%mod;
    }
    if (Tree[k].r<l || Tree[k].l>r)
        return 0;
    Tree_pushdown(k);
    long long ans=0;
    if (l<=Tree[lson(k)].r)
    {
        ans=(ans+Tree_query(lson(k), l, r))%mod;
    }
    if (Tree[rson(k)].l<=r)
    {
        ans=(ans+Tree_query(rson(k), l, r))%mod;
    }
    return ans%mod;
}
inline void Tree_Print(int n)//输出每个结点用
{
    _rep(i, 1, n)
    {
        printf("%d ", Tree_query(1, i, i));
    }
    printf("\n");
}
void solve()
{
    int n, m;
    scanf("%d%d%lld", &n, &m, &mod);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
    }
    Tree_build(1, 1, n);
    while(m--)
    {
        int z;
        scanf("%d", &z);
        if (z==2)
        {
            int l, r;
            long long k;
            scanf("%d%d%lld", &l, &r, &k);
            Tree_add(1, l, r, (k%mod+mod)%mod);
        }
        if (z==3)
        {
            int l, r;
            scanf("%d%d", &l, &r);
            printf("%lld\n", Tree_query(1, l, r));
        }
        if (z==1)
        {
            int l, r;
            long long k;
            scanf("%d%d%lld", &l, &r, &k);
            Tree_multi(1, l, r, (k%mod+mod)%mod);
        }
//        Tree_Print(n);
    }
}