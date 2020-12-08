double f(double a)
{
}
double SimpleSimpson(double a, double b)
{
    return (b-a)/6.0*(f(a)+f(b)+4*f((a+b)/2.0));
}//基本辛普森积分
double Simpson(double l, double r, double ans)
{
    double mid=(l+r)/2;
    double Simpson_l=SimpleSimpson(l, mid);
    double Simpson_r=SimpleSimpson(mid, r);
    if (fabs(Simpson_l+Simpson_r-ans)<=eps)
        return ans;
    return Simpson(l, mid, Simpson_l)+Simpson(mid, r, Simpson_r);
}//二分区间,使用时Simpson(上界,下界,SimpleSimpson(上界,下界))
void solve()
{
    printf("%.1f\n", Simpson(0, 2*PI, SimpleSimpson(0, 2*PI))
}
