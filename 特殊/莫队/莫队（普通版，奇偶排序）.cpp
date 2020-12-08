//ά������ÿ�����ֳ��ָ�����ƽ��
#pragma GCC optimize(2)//O2����
#include<bits/stdc++.h>
using namespace std;
const int maxn=5e4;
int n, m;
int BLOCK_SIZE;
#define _rep(i, a, b) for(int i=(a);i<=(b);++i)
#define _repp(i, a, b) for(int i=(a);i<(b);++i)
#define _per(i, a, b) for(int i=(b);i>=(a);--i)
#define _pper(i, a, b) for(int i=(b);i>(a);--i)
#define mem(a) memset(a,0,sizeof(a))
inline void read(int &_n)
{
    register int x=0, f=1;
    register char c=getchar();
    while(c<'0' || c>'9')
    {
        if (c=='-') f=-1;
        c=getchar();
    }
    while(c>='0' && c<='9') x=(x<<3)+(x<<1)+(c^48), c=getchar();
    _n=x*f;
}
struct Mo_Node
{
    int l;
    int r;//��ѯ����
    int id;//ԭ��λ��
    bool operator<(const Mo_Node &x) const//�ֿ�+��ż����
    {
        if (l/BLOCK_SIZE!=x.l/BLOCK_SIZE)
        {
            return l<x.l;
        }
        return (l/BLOCK_SIZE)&1 ? r<x.r : r>x.r;
    }
};//��ѯ��
int a[maxn+10];
int cnt[maxn+10];//cnt[i]��ʾi��ɫ�ĸ���
long long ans1[maxn+10];
long long ans2[maxn+10];
struct Mo//Ī��
{
    Mo_Node moNode[maxn+10];
    int siz;
    long long sum=0;//ͳ�ƽ����
    inline void add(int pos)//���
    {
//        printf("%d add:\n", a[pos]);
        sum-=cnt[a[pos]]*cnt[a[pos]];
        cnt[a[pos]]++;
        sum+=cnt[a[pos]]*cnt[a[pos]];
//        printf("cnt[%d]=%d\n",a[pos],cnt[a[pos]]);
    }
    inline void del(int pos)//���
    {
//        printf("%d del:\n", a[pos]);
        sum-=cnt[a[pos]]*cnt[a[pos]];
        cnt[a[pos]]--;
        sum+=cnt[a[pos]]*cnt[a[pos]];
//        printf("cnt[%d]=%d\n",a[pos],cnt[a[pos]]);
    }
    inline void work()
    {
        sort(moNode+1, moNode+siz+1);
        int l=1, r=0;//����ָ��
        _rep(i, 1, siz)
        {
            Mo_Node moNode1=moNode[i];
//            printf("l=%d r=%d\n",moNode1.l,moNode1.r);
            if (moNode1.l==moNode1.r)
            {
                ans1[moNode1.id]=0;
                ans2[moNode1.id]=1;
            }
            while(r<moNode1.r) add(++r);//r����
            while(r>moNode1.r) del(r--);//r����
            while(l<moNode1.l) del(l++);//l����
            while(l>moNode1.l) add(--l);//l����
//            printf("[%d,%d]\n", l, r);
//            printf("sum=%lld\n", sum);
            ans1[moNode1.id]=sum-(r-l+1);
            ans2[moNode1.id]=(long long) (r-l+1)*(r-l);
        }
    }
};
inline void solve()
{
    read(n);
    read(m);
    BLOCK_SIZE=int(ceil(pow(n, 0.5)));
    _rep(i, 1, n)
    {
        read(a[i]);
    }
    Mo mo;
    mo.siz=m;
    _rep(i, 1, m)
    {
        read(mo.moNode[i].l);
        read(mo.moNode[i].r);
        mo.moNode[i].id=i;
    }
    mo.work();
    _rep(i, 1, m)
    {
        if (ans1[i])
        {
            long long g=__gcd(ans1[i], ans2[i]);
            ans1[i]/=g;
            ans2[i]/=g;
        }
        else
            ans2[i]=1;
        printf("%lld/%lld\n", ans1[i], ans2[i]);
    }
}
signed main()
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