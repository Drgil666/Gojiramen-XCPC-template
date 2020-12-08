//��̬���kС
//��̬����
#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
int n, q, m, cnt=0;
#define ll long long
//cnt:�ܽڵ����
const int Mul=20;
int a[maxn+10], b[maxn+10], T[maxn+10];
//T:ǰ׺��,T[i]����1~i�е�i�ŵĸ��ڵ�
int sum[maxn*Mul+10], L[maxn*Mul+10], R[maxn*Mul+10];
//sum:ͳ��sum[i]��Ӧ������ֵ��[l',r']����
//L,R:L[i]ָȨֵ�߶����б��Ϊi�����Һ��ӱ��
inline int President_Tree_build(int l, int r)//���߶�������
{
    int rt=++cnt;
    sum[rt]=0;
    if (l<r)//���ﲻִ�е�ʱ�����Ҷ�ӽڵ�
    {
        int mid=(l+r)>>1;
        L[rt]=President_Tree_build(l, mid);
        R[rt]=President_Tree_build(mid+1, r);
    }
    return rt;
}
inline int President_Tree_update(int pre, int l, int r, int x)
{
    int rt=++cnt;//�����½ڵ�
    L[rt]=L[pre];
    R[rt]=R[pre];//
    sum[rt]=sum[pre]+1;//���¸���
    if (l<r)
    {
        int mid=(l+r)>>1;
        if (x<=mid) L[rt]=President_Tree_update(L[pre], l, mid, x);
        else R[rt]=President_Tree_update(R[pre], mid+1, r, x);
        //���϶��ֿ����½ڵ㣬ֱ����Ӧ�ĵ㱻����
    }
    return rt;//���ص�����һ���������ĵ�
}
inline int President_Tree_query1(int u, int v, int l, int r, int k)
//��kС����
//��ǰ���Ҷ��ӽڵ㡢��ǰ���䡢��k��
{
    if (l>=r) return l;
    int x=sum[L[v]]-sum[L[u]];//��������������ָ���
    int mid=(l+r)>>1;
    if (x>=k)//��ߵ���������Ƿ���k
        return President_Tree_query1(L[u], L[v], l, mid, k);
    return President_Tree_query1(R[u], R[v], mid+1, r, k-x);
}
inline int President_Tree_query2(int u, int v, int LL, int RR, int l, int r)
//�������ָ���
{
    if (LL<=l && r<=RR)
        return sum[v]-sum[u];
    int mid=(l+r)>>1;
    int res=0;
    if (LL<=mid)
    {
        res+=President_Tree_query2(L[u], L[v], LL, RR, l, mid);
    }
    if (mid+1<=RR)
    {
        res+=President_Tree_query2(R[u], R[v], LL, RR, mid+1, r);
    }
    return res;
}
inline ll President_Tree_query3(int l, int r, int LL, int RR, int x)
//������ĳ�����ֳ��ִ���
{
    if (l==r)
    {
        return sum[RR]-sum[LL];
    }
    int mid=(l+r)>>1;
    if (mid>=x)
    {
        return President_Tree_query3(l, mid, L[LL], L[RR], x);
    }
    else
    {
        return President_Tree_query3(mid+1, r, R[LL], R[RR], x);
    }
}
void solve()
{
    int t,tot=0;
    scanf("%d", &t);
    while(t--)
    {
        cnt=0;
        memset(L, 0, sizeof(L));
        memset(R, 0, sizeof(R));
        memset(sum, 0, sizeof(sum));
        memset(T, 0, sizeof(T));
        scanf("%d%d", &n, &q);
        for(int i=1; i<=n; i++)
        {
            scanf("%d", &a[i]);
            b[i]=a[i];
        }
        sort(b+1, b+1+n);
        m=unique(b+1, b+1+n)-(b+1);//��ɢ��(Ҫ����������ɢ��)
        T[0]=President_Tree_build(1, m);//����,���ص��Ǹ��ڵ�
        for(int i=1; i<=n; i++)
        {
            int tt=lower_bound(b+1, b+1+m, a[i])-b;
            T[i]=President_Tree_update(T[i-1], 1, m, tt);
        }
        printf("Case %d:\n", ++tot);
        while(q--)
        {
            int l, r, k;
            scanf("%d%d%d", &l, &r, &k);
            l++;
            r++;
            int index=upper_bound(b+1, b+m+1, k)-(b+1);
            if (index)
                printf("%d\n", President_Tree_query2(T[l-1], T[r], 1, index, 1, m));
            else
                printf("0\n");
//            int index=President_Tree_query1(T[l-1], T[r], 1, m, k);//����ǰ׺�͵õ�[l,r]
//            printf("%d\n", b[index]);
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