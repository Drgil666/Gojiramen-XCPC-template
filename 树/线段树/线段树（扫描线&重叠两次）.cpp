#include <iostream>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cstdlib>
#include <algorithm>
#include <queue>
#include <stack>
#include <map>
#include <set>
#include <vector>
#include <string>
#define INF 0x3f3f3f3f
#define eps 1e-8
#define MAXN (10000+10)
#define MAXM (200000+10)
#define Ri(a) scanf("%d", &a)
#define Rl(a) scanf("%lld", &a)
#define Rf(a) scanf("%lf", &a)
#define Rs(a) scanf("%s", a)
#define Pi(a) printf("%d\n", (a))
#define Pf(a) printf("%.2lf\n", (a))
#define Pl(a) printf("%lld\n", (a))
#define Ps(a) printf("%s\n", (a))
#define W(a) while(a--)
#define CLR(a, b) memset(a, (b), sizeof(a))
#define MOD 1000000007
#define LL long long
#define lson o<<1, l, mid
#define rson o<<1|1, mid+1, r
#define ll o<<1
#define rr o<<1|1
#define PI acos(-1.0)
using namespace std;
struct Tree{
    int l, r, len;
    double sum1, sum2;
    int cover;
};
Tree tree[MAXN<<2];
struct Node{
    double x1, x2, y;
    int cover;
};
bool cmp(Node a, Node b){
    return a.y < b.y;
}
Node num[MAXN];
void Build(int o, int l, int r)
{
    tree[o].l = l; tree[o].r = r;
    tree[o].len = r-l+1;
    tree[o].sum1 = tree[o].sum2 = tree[o].cover = 0;
    if(l == r)
        return ;
    int mid = (l + r) >> 1;
    Build(lson); Build(rson);
}
double rec[MAXN];
int Find(int l, int r, double val)
{
    while(r >= l)
    {
        int mid = (l + r) >> 1;
        if(rec[mid] == val)
            return mid;
        else if(rec[mid] > val)
            r = mid-1;
        else
            l = mid+1;
    }
}
void PushUp(int o)
{
    //这个原理可以用到被多次覆盖
    //cover表示被重叠的次数
    //如果是0次，sum1 = [lson].sum1 + [rson].sum1, sum2 = [lson].sum2 + [rson].sum2;
    //如果是一次，sum2 = [lson].sum2 + [rson].sum2 + [lson].sum1 + [rson].sum1
    //(原有的+被覆盖一次的)
    //sum1 = 线段len - sum2;
    //cover >= 2，sum1 = 0, sum2 = 线段len
    if(tree[o].cover >= 2)
        tree[o].sum2 = rec[tree[o].r+1] - rec[tree[o].l], tree[o].sum1 = 0;
    else if(tree[o].cover == 1)
    {
        if(tree[o].l == tree[o].r)
            tree[o].sum2 = 0;
        else
            tree[o].sum2 = tree[ll].sum2 + tree[rr].sum2 + tree[ll].sum1 + tree[rr].sum1;
        tree[o].sum1 = rec[tree[o].r+1] - rec[tree[o].l] - tree[o].sum2;
    }
    else
    {
        if(tree[o].l == tree[o].r)
            tree[o].sum2 = tree[o].sum1 = 0;
        else
        {
            tree[o].sum2 = tree[ll].sum2 + tree[rr].sum2;
            tree[o].sum1 = tree[ll].sum1 + tree[rr].sum1;
        }
    }
}
void Update(int o, int L, int R, int v)
{
    if(tree[o].l >= L && tree[o].r <= R)
    {
        tree[o].cover += v;
        PushUp(o);
        return ;
    }
    int mid = (tree[o].l + tree[o].r) >> 1;
    if(R <= mid)
        Update(ll, L, R, v);
    else if(L > mid)
        Update(rr, L, R, v);
    else
    {
        Update(ll, L, mid, v);
        Update(rr, mid+1, R, v);
    }
    PushUp(o);
}
int main()
{
    int t; Ri(t);
    W(t)
    {
        int n; Ri(n);
        int k = 0, len = 1;
        for(int i = 0; i < n; i++)
        {
            double x1, y1, x2, y2;
            Rf(x1); Rf(y1); Rf(x2); Rf(y2);
            num[k].x1 = x1; num[k].x2 = x2;
            num[k].y = y1;
            num[k++].cover = 1;
            rec[len++] = x1;

            num[k].x1 = x1; num[k].x2 = x2;
            num[k].y = y2;
            num[k++].cover = -1;
            rec[len++] = x2;
        }
        sort(num, num+k, cmp);
        sort(rec+1, rec+len);
        int R = 2;
        for(int i = 2; i < len; i++)
            if(rec[i] != rec[i-1])
                rec[R++] = rec[i];
        sort(rec, rec+R); R--;
        Build(1, 1, R); double ans = 0;
        for(int i = 0; i < k-1; i++)
        {
            int x = Find(1, R, num[i].x1);
            int y = Find(1, R, num[i].x2);
            if(i) ans += tree[1].sum2 * (num[i].y - num[i-1].y);
            if(x <= y-1)
                Update(1, x, y-1, num[i].cover);
        }
        printf("%.2lf\n", ans);
    }
    return 0;
}
 