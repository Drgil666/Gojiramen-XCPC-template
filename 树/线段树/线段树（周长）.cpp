#include <bits/stdc++.h>
using namespace std;
#define eps 1e-8
#define lson rt<<1,left,mid
#define rson rt<<1|1,mid,right
const int maxn = 2e4 + 10;
double X[maxn<<1];
struct edge{
    double x1,x2,y;
    int flag;
    edge(){}
    edge(double x1,double x2,double y,int flag):x1(x1),x2(x2),y(y),flag(flag){}

    bool operator < (const edge &rhs) const{
        if(y == rhs.y)return flag > rhs.flag;
        return y < rhs.y;
    }

}e[maxn << 1];
struct node{
    int cnt;
    int line;
    bool lbd,rbd;
    double m;
}tree[maxn << 2];
void pup(int rt,int left,int right)
{
    if(tree[rt].cnt)
    {
        tree[rt].lbd = tree[rt].rbd = true;
        tree[rt].m = X[right] - X[left];
        //printf("Find :   left = %.2f right = %.2f len = %.2f\n",X[left],X[right],tree[rt].m);
        tree[rt].line = 2;
    }
    else if(left + 1 == right)//叶子节点且没有覆盖
    {
        tree[rt].m = 0.0;
        tree[rt].lbd = tree[rt].rbd = false;
        tree[rt].line = 0;
    }
    else
    {
        tree[rt].lbd = tree[rt<<1].lbd;
        tree[rt].rbd = tree[rt<<1|1].rbd;
        tree[rt].m = tree[rt<<1].m + tree[rt<<1|1].m;
        tree[rt].line = tree[rt<<1].line + tree[rt<<1|1].line;
        if(tree[rt<<1].rbd && tree[rt<<1|1].lbd)tree[rt].line -= 2;
    }
}
void build(int rt,int left,int right)
{
    tree[rt].cnt = 0;
    tree[rt].line = 0;
    tree[rt].m = 0.0;
    tree[rt].lbd = false;
    tree[rt].rbd = false;
    if(left + 1 == right)return;
    int mid = (left + right) >> 1;
    build(lson);
    build(rson);
}
bool Equal(double x,double y)
{
    return abs(x - y) <= eps;
}
void update(double l,double r,int v,int rt,int left,int right)
{
    if(Equal(l,X[left]) && (Equal(r,X[right])))
    {
        tree[rt].cnt += v;
        pup(rt,left,right);
        return;
    }
    if(left + 1 == right)return;
    int mid = (left + right) >> 1;

    if(r <= X[mid] + eps)update(l,r,v,lson);
    else if(l >= X[mid] -eps)update(l,r,v,rson);
    else
    {
        update(l,X[mid],v,lson);
        update(X[mid],r,v,rson);
    }

    pup(rt,left,right);
}
void solve()
{
    int n;
    double x1,y1,x2,y2;
    while(~scanf("%d",&n))
    {
        for(int i = 0;i < n;++i)
        {
            scanf("%lf%lf%lf%lf",&x1,&y1,&x2,&y2);
            e[i] = edge(x1,x2,y1,1);
            e[i + n] = edge(x1,x2,y2,-1);
            X[i] = x1;
            X[i+n] = x2;
        }
        n <<= 1;
        sort(X,X+n);
        sort(e,e+n);

        int N = unique(X,X+n) - X;
        build(1,0,N-1);
        double now = 0.0;
        double last = now;
        for(int i = 0;i < n;++i)
        {
            update(e[i].x1,e[i].x2,e[i].flag,1,0,N-1);
            if(i != n-1)
                now += tree[1].line * (e[i+1].y - e[i].y);
            //cout<<now<<endl;
            now += abs(tree[1].m - last);
            //cout<<now<<endl;
            //printf("now line:  %.2f --- %.2f\n",e[i].x1,e[i].x2);
            //if(i != n-1)
            //printf("last line:  %.2f --- %.2f\n",e[i-1].x1,e[i-1].x2);
            //printf("now len :  %.2f\n",tree[1].m);
            //printf("last len :  %.2f\n",last);
            //cout<<now<<endl;
            //printf("%d : %.2f\n",i+1,abs(tree[1].m - last));
            last = tree[1].m;
        }
        printf("%.0f\n",now);
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