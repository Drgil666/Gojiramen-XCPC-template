#include<bits/stdc++.h>
using namespace std;
const int maxn=1e5;
#define INF 1e9+7;
inline int Rand()
{
    static unsigned long long r=2333;//static不能少，r的初值可以自己定
    return (r*=233333)%=2147483647;//每次r乘上的数也可以自己定
}
int Size[maxn+10];//子树节点数
int Key[maxn+10];//i的关键字
int Cnt[maxn+10];//i对应的关键字的个数
int Random[maxn+10];//随机值,堆中关键字
int Son[maxn+10][2];//0是左儿子、1是右儿子
int sumNode, root;
void pushUp(int x)
{
    Size[x]=Size[Son[x][0]]+Size[Son[x][1]]+Cnt[x];
}
void Treap_leftRotate(int &x)//以x为根左旋
{
    int i=Son[x][1];
    Son[x][1]=Son[i][0];
    Son[i][0]=x;
    pushUp(x);
    pushUp(i);
    x=i;
}
void Treap_rightRotate(int &x)//以x为根右旋
{
    int i=Son[x][0];
    Son[x][0]=Son[i][1];
    Son[i][1]=x;
    pushUp(x);
    pushUp(i);
    x=i;
}
inline void Treap_add(int &p, int val)//添加一个val
{
    if (!p)//p=0,空节点
    {
        p=++sumNode;
        Size[p]=Cnt[p]=1;
        Key[p]=val;
        Random[p]=Rand();
        return;
    }
    if (Key[p]==val)//与已有的重复
    {
        Cnt[p]++;
        Size[p]++;
        return;
    }
    if (val>Key[p])//在右边
    {
        Treap_add(Son[p][1], val);
        if (Random[p]<Random[Son[p][1]])
            Treap_leftRotate(p);//左旋
    }
    else
    {
        Treap_add(Son[p][0], val);
        if (Random[p]<Random[Son[p][0]])
            Treap_rightRotate(p);//右旋
    }
    pushUp(p);
}
inline void Treap_del(int &p, int val)//删除一个val
{
    if (!p)//空树
        return;
    if (val==Key[p])
    {
        if (!Son[p][0] && !Son[p][1])//叶子节点直接删
        {
            Size[p]--;
            Cnt[p]--;
            if (Cnt[p]==0)
                p=0;//特殊情况
        }
        else if (Son[p][0] && !Son[p][1])//只有左儿子
        {
            Treap_rightRotate(p);
            Treap_del(Son[p][1], val);
        }
        else if (!Son[p][0] && !Son[p][1])//只有右儿子
        {
            Treap_leftRotate(p);
            Treap_del(Son[p][0], val);
        }
        else//左右都有
        {
            if (Random[Son[p][0]]>Random[Son[p][1]])
            {
                Treap_rightRotate(p);
                Treap_del(Son[p][1], val);
            }
            else
            {
                Treap_leftRotate(p);
                Treap_del(Son[p][0], val);
            }
        }
    }
    else if (val>Key[p])
    {
        Treap_del(Son[p][1], val);
    }
    else
    {
        Treap_del(Son[p][0], val);
    }
    pushUp(p);
}
inline int getRank(int p, int val)
{
    if (!p)
        return 0;
    if (Key[p]==val)//中间
        return Size[Son[p][0]]+1;
    if (val>Key[p])//右边
        return Size[Son[p][0]]+Cnt[p]+getRank(Son[p][1], val);
    return getRank(Son[p][0], val);//左边
}
inline int findByRank(int p, int rank)
{
    if (!p)
        return 0;
    if (Size[Son[p][0]]>=rank)//左边
    {
        return findByRank(Son[p][0], rank);
    }
    else if (Size[Son[p][0]]+Cnt[p]<rank)//右边
    {
        return findByRank(Son[p][1], rank-Cnt[p]-Size[Son[p][0]]);
    }
    else
        return Key[p];
}
inline int prev(int p, int x)
{
    if (!p)
        return -INF;
    if (x<=Key[p])//x在左边
        return prev(Son[p][0], x);
    return max(Key[p], prev(Son[p][1], x));//要么前缀是根要么就是在右边
}
inline int next(int p, int x)
{
    if (!p)
        return INF;
    if (x>=Key[p])//右边
        return next(Son[p][1], x);
    return min(Key[p], next(Son[p][0], x));
}
void print()
{
}
void solve()
{
    sumNode=root=0;
    int t;
    scanf("%d", &t);
    while(t--)
    {
        int op, x;
        scanf("%d%d", &op, &x);
        if (op==1)
        {
            Treap_add(root, x);
        }
        if (op==2)
        {
            Treap_del(root, x);
        }
        if (op==3)
        {
            printf("%d\n", getRank(root, x));
        }
        if (op==4)
        {
            printf("%d\n", findByRank(root, x));
        }
        if (op==5)
        {
            printf("%d\n", prev(root, x));
        }
        if (op==6)
        {
            printf("%d\n", next(root, x));
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
        cout<<"------------------"<<endl;
    }
#else
    solve();
#endif
    return 0;
}