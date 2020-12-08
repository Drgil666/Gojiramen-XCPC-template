//此题开始时，所有的房间都是空房间，有两个操作：
//1、查询长度为x的连续房间，并将房间全部填满，输出左端点值。
//2、表示退房，将x,到x+y-1的房间退房。
//维护三个值:当前空房间的连续最大值，左儿子空房间的最大值还是右儿子空房间的最大值
#include <bits/stdc++.h>
using namespace std;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)
//左儿子
#define rson(n) (n<<1|1)
//右儿子
#define NodeType long long
const long long maxn=5e4;
NodeType a[maxn+10];
struct Node
{
    NodeType sum, lmax, rmax;
    int lazyTag;
    //如果入住为1，退房为2
};
Node Tree[(maxn<<2)+10];
void Tree_pushup(int k, int l, int r)//向上更新
{
    int mid=(l+r)>>1;
    if (Tree[lson(k)].sum==(mid-l+1))//左区间整一段都是
    {
        Tree[k].lmax=Tree[lson(k)].sum+Tree[rson(k)].lmax;//左边整一段+右边的左边一段
    }
    else
    {
        Tree[k].lmax=Tree[lson(k)].lmax;//左区间的左边这段就是父区间这段
    }
    if (Tree[rson(k)].sum==r-mid)//右区间整个都是
    {
        Tree[k].rmax=Tree[lson(k)].rmax+Tree[rson(k)].sum;
    }
    else
    {
        Tree[k].rmax=Tree[rson(k)].rmax;//右区间的右边这段就是父区间这段
    }
    Tree[k].sum=max(Tree[lson(k)].rmax+Tree[rson(k)].lmax, max(Tree[lson(k)].sum, Tree[rson(k)].sum));
    //左区间最大连续值、右区间最大连续值、左右区间中间并起来的部分
}
void Tree_pushdown(int k, int l, int r)//向下更新
{
    if (Tree[k].lazyTag==1)//已入住
    {
        Tree[lson(k)].sum=Tree[lson(k)].lmax=Tree[lson(k)].rmax=0;
        Tree[rson(k)].sum=Tree[rson(k)].lmax=Tree[rson(k)].rmax=0;
        Tree[lson(k)].lazyTag=Tree[rson(k)].lazyTag=1;
    }
    else if (Tree[k].lazyTag==2)//退房
    {
        int mid=(l+r)>>1;
        Tree[lson(k)].sum=Tree[lson(k)].lmax=Tree[lson(k)].rmax=mid-l+1;
        Tree[rson(k)].sum=Tree[rson(k)].lmax=Tree[rson(k)].rmax=r-mid;
        Tree[lson(k)].lazyTag=Tree[rson(k)].lazyTag=2;
    }
    Tree[k].lazyTag=0;
}
void Tree_build(int k, int l, int r)
//建树(当前节点编号,区间范围)
{
    Tree[k].sum=Tree[k].lmax=Tree[k].rmax=r-l+1;
    Tree[k].lazyTag=0;
    if (l==r)
    {
        return;//本题如此
    }
    int mid=(l+r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);
}
void Tree_update(int k, int l, int r, int L, int R, int t)
//当前结点，当前区间,目标范围，要更新的值
{
    if (L<=l && r<=R)
    {
        if (t==1)//入住状态
        {
            Tree[k].sum=Tree[k].rmax=Tree[k].lmax=0;//该区间没有空房间
        }
        else
        {
            Tree[k].sum=Tree[k].rmax=Tree[k].lmax=r-l+1;//整个区间都是空房间
        }
        Tree[k].lazyTag=t;//设置lazyTag
        return;
    }
    Tree_pushdown(k, l, r);//更新lazyTag;
    int mid=(l+r)>>1;
    if (L<=mid)
        Tree_update(lson(k), l, mid, L, R, t);
    if (mid+1<=R)
        Tree_update(rson(k), mid+1, r, L, R, t);
    Tree_pushup(k, l, r);
}
long long Tree_query(int k, int l, int r, int x)
//当前结点、当前区间,至少x个
{
    Tree_pushdown(k, l, r);
    if (l==r)
    {
        return l;//返回的是最左边的房间编号
    }
    int mid=(l+r)>>1;
    if (Tree[lson(k)].sum>=x)//左区间可能满足要求
    {
        return Tree_query(lson(k), l, mid, x);//继续搜下去
    }
    if (Tree[lson(k)].rmax+Tree[rson(k)].lmax>=x)
        //有半个区间的左边和左半个的右边满足要求的话
    {
        return mid-Tree[lson(k)].rmax+1;//返回最左边的位置
    }
    return Tree_query(rson(k), mid+1, r, x);//右区间查找
}
void Tree_print(int i,int l,int r)
{
    if(l==r)
    {
        printf("l:%d %d %d %d\n",Tree[i].sum,Tree[i].lmax,Tree[i].rmax,Tree[i].lazyTag);
        return;
    }
    int mid=(l+r)>>1;
    Tree_print(lson(i),l,mid);
    Tree_print(rson(i),mid+1,r);
}
void solve()
{
    int n, m;
    scanf("%d%d", &n, &m);
    Tree_build(1, 1, n);
    while(m--)
    {
        int z;
        scanf("%d", &z);
        if (z==1)
        {
            int x;
            scanf("%d", &x);
            if (Tree[1].sum>=x)//有条件去查得到
            {
                int ans=Tree_query(1, 1, n, x);
                printf("%d\n", ans);
                Tree_update(1, 1, n, ans, x+ans-1, 1);//修改为已经被住下
            }
            else
            {
                printf("0\n");
            }
        }
        else
        {
            int x, y;
            scanf("%d%d", &x, &y);
            Tree_update(1, 1, n, x, x+y-1, 2);//退房
        }
//        Tree_print(1,1,n);
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