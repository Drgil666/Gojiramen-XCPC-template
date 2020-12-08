#include <bits/stdc++.h>
using namespace std;
#define _rep(i,a,b) for(int i=(a);i<=(b);i++)
#define _repp(i,a,b) for(int i=(a);i<(b);i++)
#define _per(i,a,b) for(int i=(b);i>=(a);i--)
#define _pper(i,a,b) for(int i=(b);i>(a);i--)
#define mem(a) memset(a,0,sizeof(a))
struct TreeArray
{
    static const int maxn=1e5;
    int array[maxn+50];
    int differ[maxn+50];
    int sumArray;
    TreeArray()
    {
        sumArray=0;
        mem(array);
        mem(differ);
    };
    TreeArray(int a[],int n)
    {
        sumArray=n;
        for(int i=1;i<=sumArray;i++)
        {
            update(i,a[i]);
        }
    };
    int lowbit(int x)//计算2^k
    {
        return x&(-x);
    }
    void update(int i,int k)//单点更新
    {
        int x=i;
        while(i<=sumArray)
        {
            array[i]+=k;
            differ[i]+=k*(x-1);
            i+=lowbit(i);
        }
    }
    void update(int l,int r,int k)
    {
        update(l,k);
        update(r+1,-k);
    }
    int getSum(int i)//[1,i]
    {
        int x=i;
        int sum=0;
        while(i>0)
        {
            sum+=array[i]*x-differ[i];
            i-=lowbit(i);
        }
        return sum;
    }
    int getSum(int l,int r)//[l,r]
    {
        return getSum(r)-getSum(l-1);
    }
    void print()
    {
        printf("\n");
        printf("array: ");
        _rep(i,1,sumArray)
        {
            printf("%d ",array[i]);
        }
        printf("\n");
        printf("differ: ");
        _rep(i,1,sumArray)
        {
            printf("%d ",differ[i]);
        }
    }
};
int a[500010];
void solve()
{
    int t,tot=0;
    scanf("%d",&t);
    while(t--)
    {
        printf("Case %d:\n",++tot);
        int n;
        scanf("%d",&n);
        TreeArray treeArray=TreeArray();
        treeArray.sumArray=n;
        a[0]=0;
        _rep(i,1,n)
        {
            scanf("%d",&a[i]);
            treeArray.update(i,a[i]-a[i-1]);
        }
        char s[100];
        while(~scanf("%s",s) && s[0]!='E')
        {
            if(s[0]=='A')
            {
                int x,y;
                scanf("%d%d",&x,&y);
                treeArray.update(x,x,y);
            }
            else if (s[0]=='S')
            {
                int x,y;
                scanf("%d%d",&x,&y);
                treeArray.update(x,x,-y);
            }
            else if (s[0]=='Q')
            {
                int x,y;
                scanf("%d%d",&x,&y);
                printf("%d\n",treeArray.getSum(x,y));
            }
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