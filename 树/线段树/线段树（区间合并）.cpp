//���⿪ʼʱ�����еķ��䶼�ǿշ��䣬������������
//1����ѯ����Ϊx���������䣬��������ȫ�������������˵�ֵ��
//2����ʾ�˷�����x,��x+y-1�ķ����˷���
//ά������ֵ:��ǰ�շ�����������ֵ������ӿշ�������ֵ�����Ҷ��ӿշ�������ֵ
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
const long long maxn=5e4;
NodeType a[maxn+10];
struct Node
{
    NodeType sum, lmax, rmax;
    int lazyTag;
    //�����סΪ1���˷�Ϊ2
};
Node Tree[(maxn<<2)+10];
void Tree_pushup(int k, int l, int r)//���ϸ���
{
    int mid=(l+r)>>1;
    if (Tree[lson(k)].sum==(mid-l+1))//��������һ�ζ���
    {
        Tree[k].lmax=Tree[lson(k)].sum+Tree[rson(k)].lmax;//�����һ��+�ұߵ����һ��
    }
    else
    {
        Tree[k].lmax=Tree[lson(k)].lmax;//������������ξ��Ǹ��������
    }
    if (Tree[rson(k)].sum==r-mid)//��������������
    {
        Tree[k].rmax=Tree[lson(k)].rmax+Tree[rson(k)].sum;
    }
    else
    {
        Tree[k].rmax=Tree[rson(k)].rmax;//��������ұ���ξ��Ǹ��������
    }
    Tree[k].sum=max(Tree[lson(k)].rmax+Tree[rson(k)].lmax, max(Tree[lson(k)].sum, Tree[rson(k)].sum));
    //�������������ֵ���������������ֵ�����������м䲢�����Ĳ���
}
void Tree_pushdown(int k, int l, int r)//���¸���
{
    if (Tree[k].lazyTag==1)//����ס
    {
        Tree[lson(k)].sum=Tree[lson(k)].lmax=Tree[lson(k)].rmax=0;
        Tree[rson(k)].sum=Tree[rson(k)].lmax=Tree[rson(k)].rmax=0;
        Tree[lson(k)].lazyTag=Tree[rson(k)].lazyTag=1;
    }
    else if (Tree[k].lazyTag==2)//�˷�
    {
        int mid=(l+r)>>1;
        Tree[lson(k)].sum=Tree[lson(k)].lmax=Tree[lson(k)].rmax=mid-l+1;
        Tree[rson(k)].sum=Tree[rson(k)].lmax=Tree[rson(k)].rmax=r-mid;
        Tree[lson(k)].lazyTag=Tree[rson(k)].lazyTag=2;
    }
    Tree[k].lazyTag=0;
}
void Tree_build(int k, int l, int r)
//����(��ǰ�ڵ���,���䷶Χ)
{
    Tree[k].sum=Tree[k].lmax=Tree[k].rmax=r-l+1;
    Tree[k].lazyTag=0;
    if (l==r)
    {
        return;//�������
    }
    int mid=(l+r)>>1;
    Tree_build(lson(k), l, mid);
    Tree_build(rson(k), mid+1, r);
}
void Tree_update(int k, int l, int r, int L, int R, int t)
//��ǰ��㣬��ǰ����,Ŀ�귶Χ��Ҫ���µ�ֵ
{
    if (L<=l && r<=R)
    {
        if (t==1)//��ס״̬
        {
            Tree[k].sum=Tree[k].rmax=Tree[k].lmax=0;//������û�пշ���
        }
        else
        {
            Tree[k].sum=Tree[k].rmax=Tree[k].lmax=r-l+1;//�������䶼�ǿշ���
        }
        Tree[k].lazyTag=t;//����lazyTag
        return;
    }
    Tree_pushdown(k, l, r);//����lazyTag;
    int mid=(l+r)>>1;
    if (L<=mid)
        Tree_update(lson(k), l, mid, L, R, t);
    if (mid+1<=R)
        Tree_update(rson(k), mid+1, r, L, R, t);
    Tree_pushup(k, l, r);
}
long long Tree_query(int k, int l, int r, int x)
//��ǰ��㡢��ǰ����,����x��
{
    Tree_pushdown(k, l, r);
    if (l==r)
    {
        return l;//���ص�������ߵķ�����
    }
    int mid=(l+r)>>1;
    if (Tree[lson(k)].sum>=x)//�������������Ҫ��
    {
        return Tree_query(lson(k), l, mid, x);//��������ȥ
    }
    if (Tree[lson(k)].rmax+Tree[rson(k)].lmax>=x)
        //�а���������ߺ��������ұ�����Ҫ��Ļ�
    {
        return mid-Tree[lson(k)].rmax+1;//��������ߵ�λ��
    }
    return Tree_query(rson(k), mid+1, r, x);//���������
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
            if (Tree[1].sum>=x)//������ȥ��õ�
            {
                int ans=Tree_query(1, 1, n, x);
                printf("%d\n", ans);
                Tree_update(1, 1, n, ans, x+ans-1, 1);//�޸�Ϊ�Ѿ���ס��
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
            Tree_update(1, 1, n, x, x+y-1, 2);//�˷�
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