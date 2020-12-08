#include<bits/stdc++.h>
using namespace std;
const long long maxn=2e5;
#define _rep(i, a, b) for(int i=(a);i<=(b);i++)
#define _repp(i, a, b) for(int i=(a);i<(b);i++)
#define _per(i, a, b) for(int i=(b);i>=(a);i--)
#define _pper(i, a, b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
#define lson(n) (n<<1)//左儿子
#define rson(n) (n<<1|1)//右儿子
#define NodeType long long
struct Seg
{
    double l, r, h;//区间、高度
    int d;//1为下边标记，-1为上边标记
    bool operator < (const Seg &x) const
    {
        return h<x.h;
    }
};
Seg seg[maxn+10];
struct Node
{
    double sum;//区间长度
    int cnt;
    //下边数-上边数(理论上是个非负数)
    //如果子节点下边数-上边数不同我们直接赋值-1
};
double Discretize[maxn+10];
Node Tree[(maxn<<2)+10];
void Tree_pushUp(int k)
{
    if (Tree[lson(k)].cnt==-1 || Tree[rson(k)].cnt==-1)
    {
        Tree[k].cnt=-1;
    }
    else if (Tree[lson(k)].cnt!=Tree[rson(k)].cnt)
    {
        Tree[k].cnt=-1;
    }
    else
    {
        Tree[k].cnt=Tree[lson(k)].cnt;
    }
    Tree[k].sum=Tree[lson(k)].sum+Tree[rson(k)].sum;
}
void Tree_pushDown(int k, int l, int r)
{
    int mid=(l+r)>>1;
    if (Tree[k].cnt!=-1)
    {
        Tree[lson(k)].cnt=Tree[rson(k)].cnt=Tree[k].cnt;
        if (Tree[k].cnt==0)
        {
            Tree[lson(k)].sum=Tree[rson(k)].sum=0;
        }
        else
        {
            Tree[lson(k)].sum=Discretize[mid+1]-Discretize[l];
            Tree[rson(k)].sum=Discretize[r+1]-Discretize[mid+1];
        }
    }
}
void Tree_Build(int k, int l, int r)
{
    Tree[k].sum=0;
    Tree[k].cnt=0;
    if (l==r)
    {
        Tree[k].sum=0;
        Tree[k].cnt=0;
        return;
    }
    int mid=(l+r)>>1;
    Tree_Build(lson(k), l, mid);
    Tree_Build(rson(k), mid+1, r);
    Tree_pushUp(k);
}
void Tree_Update(int k, int l, int r, int L, int R, int d)
//区间更新
{
    if (L<=l && r<=R)
    {
        if (Tree[k].cnt!=-1)
        {
            Tree[k].cnt+=d;
            Tree[k].sum=(Tree[k].cnt ? (Discretize[r+1]-Discretize[l]) : 0);
            return;
        }
    }
    Tree_pushDown(k, l, r);
    int mid=(l+r)>>1;
    if (L<=mid)
    {
        Tree_Update(lson(k), l, mid, L, R, d);
    }
    if (mid+1<=R)
    {
        Tree_Update(rson(k), mid+1, r, L, R, d);
    }
    Tree_pushUp(k);
}
void solve()
{
    int n, tot=0;
    while(~scanf("%d", &n) && n)
    {
        printf("Test case #%d\n", ++tot);
        int sumSeg=0, sumX=0;
        _rep(i, 1, n)
        {
            double x1, y1, x2, y2;//矩形左下、右上端点
            scanf("%lf%lf%lf%lf", &x1, &y1, &x2, &y2);
            Discretize[++sumX]=x1;
            seg[++sumSeg].l=x1;
            seg[sumSeg].r=x2;
            seg[sumSeg].h=y1;
            seg[sumSeg].d=1;
            Discretize[++sumX]=x2;
            seg[++sumSeg].l=x1;
            seg[sumSeg].r=x2;
            seg[sumSeg].h=y2;
            seg[sumSeg].d=-1;
        }
        sort(Discretize+1,Discretize+sumX+1);
        sort(seg+1,seg+sumSeg+1);
        int k=unique(Discretize+1,Discretize+sumX+1)-(Discretize+1);
        Tree_Build(1,1,k-1);
//        printf("sumSeg=%d sumX=%d\n",sumSeg,sumX);
        double ans=0;
        _repp(i,1,sumSeg)
        {
//            int x=1,y=1;
            int x=lower_bound(Discretize+1,Discretize+k+1,seg[i].l)-Discretize;
            int y=lower_bound(Discretize+1,Discretize+k+1,seg[i].r)-Discretize-1;
//            printf("x=%d y=%d\n",x,y);
            if(x<=y)
            {
                Tree_Update(1,1,k-1,x,y,seg[i].d);
            }
//            printf("%.2f*%.2f\n",Tree[1].sum,(seg[i+1].h-seg[i].h));
            ans+=Tree[1].sum*(seg[i+1].h-seg[i].h);
        }
        printf("Total explored area: %.2f\n",ans);
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