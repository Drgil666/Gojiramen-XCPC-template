#include <bits/stdc++.h>
using namespace std;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)
//�����
#define rson(n) (n<<1|1)
//�Ҷ���
#define NodeType long long
const long long maxn=2e5;
NodeType a[maxn+10];
struct Node
{
    NodeType l=0, r=0, sum=0, lazyTag=0;
    //��߽硢�ұ߽硢����͡�������
    Node()
    {
        l=r=sum=lazyTag=0;
    }
};
Node Tree[(maxn<<2)+10];
void Tree_pushUp(int k)//������ֵ
{
    Tree[k].sum=Tree[lson(k)].sum+Tree[rson(k)].sum;
}
void Tree_build(int k, int l, int r)
//����(��ǰ�ڵ���,���䷶Χ)
{
    Tree[k].l=l;
    Tree[k].r=r;
    if (Tree[k].l==Tree[k].r)//Ҷ�ӽڵ�
    {
        Tree[k].sum=a[l];
        return;
    }
    int mid=(Tree[k].l+Tree[k].r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);//��������
    Tree_pushUp(k);//������ֵ
}
void Tree_pushDown(int k)
{
    if (Tree[k].lazyTag)
    {
        Tree[lson(k)].sum+=(Tree[lson(k)].r-Tree[lson(k)].l+1)*Tree[k].lazyTag;
        Tree[rson(k)].sum+=(Tree[rson(k)].r-Tree[rson(k)].l+1)*Tree[k].lazyTag;
        Tree[lson(k)].lazyTag+=Tree[k].lazyTag;
        Tree[rson(k)].lazyTag+=Tree[k].lazyTag;
        Tree[k].lazyTag=0;
    }
}
void Tree_add(int k, int l, int r, int x)
//��ǰ��㣬Ŀ�귶Χ��Ҫ�ӵ�ֵ
{
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        Tree[k].sum+=(Tree[k].r-Tree[k].l+1)*x;
        Tree[k].lazyTag+=x;
        return;
    }
    Tree_pushDown(k);
    if (l<=Tree[lson(k)].r)
    {
        Tree_add(lson(k), l, r, x);
    }
    if (Tree[rson(k)].l<=r)
    {
        Tree_add(rson(k), l, r, x);
    }
    Tree_pushUp(k);
}
long long Tree_query(int k, int l, int r)
//��ǰ��㡢Ŀ������
{
    if (Tree[k].lazyTag)//�ȸ��º��ѯ
    {
        Tree_pushDown(k);
    }
    if (l<=Tree[k].l && Tree[k].r<=r)
    {
        return Tree[k].sum;
    }
    if (Tree[k].r<l || Tree[k].l>r)
        return 0;
    long long ans=0;
    if (l<=Tree[lson(k)].r)
    {
        ans+=Tree_query(lson(k), l, r);
    }
    if (Tree[rson(k)].l<=r)
    {
        ans+=Tree_query(rson(k), l, r);
    }
    return ans;
}
void solve()
{
    int n, m;
    scanf("%d%d", &n, &m);
    for(int i=1; i<=n; i++)
    {
        scanf("%lld", &a[i]);
    }
    Tree_build(1, 1, n);
    while(m--)
    {
        int z;
        scanf("%d", &z);
        if (z==1)
        {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            Tree_add(1, l, r, k);
        }
        if (z==2)
        {
            int l, r;
            scanf("%d%d",&l,&r);
            printf("%lld\n",Tree_query(1,l,r));
        }
//        printf("\n");
//        _rep(i,1,n)
//        {
//            printf("%d ",Tree_query(1,i,i));
//        }
//        printf("\n");
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