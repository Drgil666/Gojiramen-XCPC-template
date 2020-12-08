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
NodeType a[maxn+10];
struct Node
{
    NodeType l, r, sum;
};
Node Tree[(maxn<<2)+10];
inline void Tree_build(int k, int l, int r)
//建树(当前节点编号,区间范围)
{
    Tree[k].l=l;
    Tree[k].r=r;
    Tree[k].sum=0;
    if (Tree[k].l==Tree[k].r)//叶子节点
    {
        Tree[k].sum=a[l];
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);//二分区间
    Tree[k].sum=Tree[lson(k)].sum+Tree[rson(k)].sum;
}
inline void Tree_update(int k, int l, int r)
//当前节点，目标范围
{
    if (Tree[k].l==Tree[k].r)
    {
        Tree[k].sum=(long long) sqrt(Tree[k].sum);
        return;
    }
    if (Tree[k].sum==Tree[k].r-Tree[k].l+1)
    {
        return;
    }
    if (l<=Tree[lson(k)].r)
    {
        Tree_update(lson(k), l, r);
    }
    if (Tree[rson(k)].l<=r)
    {
        Tree_update(rson(k), l, r);
    }
    Tree[k].sum=Tree[lson(k)].sum+Tree[rson(k)].sum;
}
inline NodeType Tree_query(int k, int l, int r)
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].sum;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    long long ans=0;
    if (l<=Tree[lson(k)].r)
    {
        ans=(ans+Tree_query(lson(k), l, r));
    }
    if (Tree[rson(k)].l<=r)
    {
        ans=(ans+Tree_query(rson(k), l, r));
    }
    return ans;
}
inline void Tree_print(int n)
{
    _rep(i, 1, n)
    {
        printf("%lld ", Tree_query(1, i, i));
    }
    printf("\n");
}
void solve()
{
    long long n;
    int tot=0;
    while(~scanf("%lld", &n))
    {
        printf("Case #%d:\n", ++tot);
        for(int i=1; i<=n; i++)
        {
            scanf("%lld", &a[i]);
        }
        Tree_build(1, 1, n);
        long long m;
        scanf("%lld", &m);
        while(m--)
        {
            int z;
            scanf("%d", &z);
            if (z==0)
            {
                int l, r;
                scanf("%d%d", &l, &r);
                if(l>r)
                    swap(l,r);
                Tree_update(1, l, r);
            }
            if (z==1)
            {
                int l, r;
                scanf("%d%d", &l, &r);
                if(l>r)
                    swap(l,r);
                printf("%lld\n", Tree_query(1, l, r));
            }
//            Tree_print(n);
        }
        printf("\n");
    }
}
int main()
{
//    ios_base::sync_with_stdio(false);
//    cin.tie(0);
//    cout.tie(0);
#ifdef ACM_LOCAL
    freopen("in.txt", "r", stdin);
    freopen("out.txt", "w", stdout);
    long long test_index_for_debug=1;
    char acm_local_for_debug;
    while(cin>>acm_local_for_debug)
    {
        cin.putback(acm_local_for_debug);
        if (test_index_for_debug>100)
        {
            throw runtime_error("Check the stdin!!!");
        }
        auto start_clock_for_debug=clock();
        solve();
        auto end_clock_for_debug=clock();
        cout<<"\nTest "<<test_index_for_debug<<" successful"<<endl;
        cerr<<"Test "<<test_index_for_debug++<<" Run Time: "
            <<double(end_clock_for_debug-start_clock_for_debug)/CLOCKS_PER_SEC<<"s"<<endl;
        cout<<"--------------------------------------------------"<<endl;
    }
#else
    solve();
#endif
    return 0;
}