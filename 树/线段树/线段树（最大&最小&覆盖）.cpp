#include <bits/stdc++.h>
using namespace std;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)//左儿子
#define rson(n) (n<<1|1)//右儿子
#define NodeType int
const long long maxn=2e5;
NodeType a[maxn+10];
struct Node
{
    NodeType l, r, maxv, minv;
};
Node Tree[(maxn<<2)+10];
inline void Tree_build(int k, int l, int r)
//建树(当前节点编号,区间范围)
{
    Tree[k].l=l;
    Tree[k].r=r;
    Tree[k].maxv=-1;
    Tree[k].minv=100000;
    if (Tree[k].l==Tree[k].r)//叶子节点
    {
        Tree[k].maxv=a[l];
        Tree[k].minv=a[l];
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);//二分区间
    Tree[k].maxv=max(Tree[lson(k)].maxv, Tree[rson(k)].maxv);
    Tree[k].minv=min(Tree[lson(k)].minv, Tree[rson(k)].minv);
}
inline void Tree_update(int k, int x, int y)
{
    if (x==Tree[k].l && x==Tree[k].r)
    {
        Tree[k].maxv=y;
        Tree[k].minv=y;
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    if (x<=mid)
    {
        Tree_update(lson(k), x, y);
    }
    else
    {
        Tree_update(rson(k), x, y);
    }
    Tree[k].maxv=max(Tree[lson(k)].maxv, Tree[rson(k)].maxv);
    Tree[k].minv=min(Tree[lson(k)].minv, Tree[rson(k)].minv);
}
inline NodeType Tree_query_max(int k, int l, int r)
//当前结点、目标区间
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].maxv;
    }
    if (Tree[k].r<l || Tree[k].l>r)
        return 0;
    int ans=-1;
    if (l<=Tree[lson(k)].r)
    {
        ans=max(ans, Tree_query_max(lson(k), l, r));
    }
    if (Tree[rson(k)].l<=r)
    {
        ans=max(ans, Tree_query_max(rson(k), l, r));
    }
    return ans;
}
inline NodeType Tree_query_min(int k, int l, int r)
//当前结点、目标区间
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].minv;
    }
    if (Tree[k].r<l || Tree[k].l>r)
        return 0;
    int ans=100000000;
    if (l<=Tree[lson(k)].r)
    {
        ans=min(ans, Tree_query_min(lson(k), l, r));
    }
    if (Tree[rson(k)].l<=r)
    {
        ans=min(ans, Tree_query_min(rson(k), l, r));
    }
    return ans;
}
inline void Tree_Print(int n)//输出每个结点用
{
    _rep(i, 1, n)
    {
        printf("%d ", Tree_query_max(1, i, i));
    }
    printf("\n");
    _rep(i, 1, n)
    {
        printf("%d ", Tree_query_min(1, i, i));
    }
    printf("\n");
}
void solve()
{
    int n, m;
    while(~scanf("%d%d", &n, &m))
    {
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &a[i]);
        }
        Tree_build(1, 1, n);
        while(m--)
        {
            int l,r;
            scanf("%d%d",&l,&r);
            printf("%d\n",Tree_query_max(1,l,r)-Tree_query_min(1,l,r));
        }
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