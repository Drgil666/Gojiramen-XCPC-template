//带单点修改的莫队:多维护一个时间维
#pragma GCC optimize(2)//O2加速
#include <bits/stdc++.h>
using namespace std;
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
const int maxn=1e6;
int block[maxn+10];
int BLOCK_SIZE;
int n, m, sumQuery=0, sumChange=0;
int sum=0;
int a[maxn+10];
int cnt[1000010], ans[maxn+10];
struct Mo_Query
{
    int l, r, pre, id;
    //区间,版本号,id
    Mo_Query() {}
    Mo_Query(int _l, int _r, int _pre, int _id)
    {
        l=_l, r=_r, pre=_pre, id=_id;
    }
    bool operator<(Mo_Query x)
    {
        return (block[l]^block[x.l]) ? block[l]<block[x.l] : ((block[r]^block[x.r]) ? block[r]<block[x.r] : pre<x.pre);
    }
} Query[maxn];
struct Mo_Update
{
    int pos, val;
    Mo_Update() {}
    Mo_Update(int _pos, int _val)
    {
        pos=_pos, val=_val;
    }
} Update[maxn];
void add(int pos)
{
    sum-=cnt[a[pos]] ? 1 : 0;
    cnt[a[pos]]++;
    sum+=cnt[a[pos]] ? 1 : 0;
}
void del(int pos)
{
    sum-=cnt[a[pos]] ? 1 : 0;
    cnt[a[pos]]--;
    sum+=cnt[a[pos]] ? 1 : 0;
}
void Time_update(int now, int ql, int qr)//更新版本
{
    int POS=Update[now].pos;
    if (POS>=ql && POS<=qr)
    {
        sum-=cnt[a[Update[now].pos]]?1:0;
        cnt[a[Update[now].pos]]--;
        sum+=cnt[a[Update[now].pos]]?1:0;
        sum-=cnt[Update[now].val]?1:0;
        cnt[Update[now].val]++;
        sum+=cnt[Update[now].val]?1:0;
    }
    swap(a[Update[now].pos], Update[now].val);
}
void solve()
{
    scanf("%d", &n);
    scanf("%d", &m);
    BLOCK_SIZE=ceil(pow(n, (long double) 2.0/3));
    _rep(i, 1, n)
    {
        scanf("%d", &a[i]);
        block[i]=(i-1)/BLOCK_SIZE+1;
    }
    while(m--)
    {
        char op[5];
        scanf("%s", op);
        int x, y;
        scanf("%d%d", &x, &y);
        if (op[0]=='Q')
        {
            sumQuery++;
            Query[sumQuery].l=x;
            Query[sumQuery].r=y;
            Query[sumQuery].pre=sumChange;
            Query[sumQuery].id=sumQuery;
        }
        else
        {
            sumChange++;
            Update[sumChange].pos=x;
            Update[sumChange].val=y;
        }
    }
    sort(Query+1, Query+sumQuery+1);
    int l=1, r=0, now=0;
    _rep(i, 1, sumQuery)
    {
        int L=Query[i].l, R=Query[i].r, PRE=Query[i].pre;
        while(l<L) del(l++);//l右移
        while(l>L) add(--l);//l左移
        while(r<R) add(++r);//r右移
        while(r>R) del(r--);//r左移
        while(now<PRE) Time_update(++now, L, R);//版本不够新
        while(now>PRE) Time_update(now--, L, R);//版本太新了
        ans[Query[i].id]=sum;
    }
    _rep(i, 1, sumQuery)printf("%d\n", ans[i]);
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