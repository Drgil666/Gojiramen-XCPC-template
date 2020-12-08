const double pi=acos(-1.0);
const double inf=1e100;
const double eps=1e-6;
const double INF=1e20;
int epsCmp(double x, double y)//误差范围内相等
{
    if (fabs(x-y)<eps)
        return 0;
    if (x>y)
        return 1;
    return -1;
}
int sgn(double d)//sgn函数
{
    if (fabs(d)<eps)
        return 0;
    if (d>0)
        return 1;
    return -1;
}
struct Point//点&向量
{
    double x;
    double y;
    Point()
    {
        x=0;
        y=0;
    }
    Point(double _x, double _y)
    {
        x=_x;
        y=_y;
    }
    Point(Point const &p)
    {
        x=p.x;
        y=p.y;
    }
    double module()
    {
        return sqrt(x*x+y*y);
    }
    bool operator==(const Point b) const//相等
    {
        return epsCmp(this->x, b.x)==0 && epsCmp(this->y, b.y)==0;
    }
    bool operator!=(const Point b) const//不等
    {
        return epsCmp(this->x, b.x)!=0 || epsCmp(this->y, b.y)!=0;
    }
    Point operator+(const Point b) const//相加
    {
        Point c;
        c.x=this->x+b.x;
        c.y=this->y+b.y;
        return c;
    }
    Point operator-(const Point b) const//相减
    {
        Point c;
        c.x=this->x-b.x;
        c.y=this->y-b.y;
        return c;
    }
    double operator*(const Point b) const//内积
    {
        return this->x*b.x+this->y*b.y;
    }
    double operator^(const Point b) const//叉积
    {
        return this->x*b.y-this->y*b.x;
    }
    Point rotate(double zeta)//绕原点逆时针旋转
    {
        Point ans=Point(x*cos(zeta)-y*sin(zeta), x*sin(zeta)+y*cos(zeta));
        return ans;
    }
    Point multiply(double k)//与实数相乘
    {
        return Point(this->x*k, this->y*k);
    }
    bool isParallel(Point a)
    {
        return epsCmp(a.y*x, a.x*y)==0;
    }
    bool isVertical(Point a)
    {
        return epsCmp(a.x*x+a.y*y, 0)==0;
    }
    Point changeXY()
    {
        Point a;
        a.x=y;
        a.y=x;
        return a;
    }
    void input()
    {
        scanf("%lf%lf", &x, &y);
    }
    void print()
    {
        printf("%.10f %.10f\n", x, y);
    }
    double getAngle()
    {
        return atan2(y, x);
    }
    double angleWith(Point b)
    {
        return acos((Point(this->x, this->y)*b)/this->module()/b.module());
    }
};
typedef Point vectorPoint;//向量
struct Line//直线与射线
{
    Point p;//线上一点
    vectorPoint v;//方向
    Line()
    {
        p=Point();
        v=Point();
    }
    Line(Point _p, Point _v)
    {
        p=_p;
        v=_v;
    }
    //点到直线距离
    double PointDis(Point x)
    {
        vectorPoint v1=vectorPoint(x-p);
        if (v.module()==0 || epsCmp(0, v1^v)==0 || epsCmp(0, (v1^v)/v.module())==0)
            return 0;
        return fabs(v1^v)/v.module();
    }
    //0重合,1平行,2相交,只有相交才有意义
    bool isSame(Line a)
    {
        return (this->v^a.v)==0 && ((this->p-a.p)^v)==0;
    }
    bool isParallel(Line a)
    {
        return (this->v^a.v)==0 && ((this->p-a.p)^v)!=0;
    }
    bool isInter(Line a)
    {
        return !isSame(a) && !isParallel(a);
    }
    Point InterLine(Line a)
    {
        Point ans;
        if (isInter(a))
        {
            double ansx=-((this->v^this->p)*a.v.x-(a.v^a.p)*this->v.x)/(a.v^this->v);
            double ansy=-((this->v^this->p)*a.v.y-(a.v^a.p)*this->v.y)/(a.v^this->v);
            if (epsCmp(0, ansx)==0)
                ansx=0;
            if (epsCmp(0, ansy)==0)
                ansy=0;
            return Point(ansx, ansy);
        }
        return Point(INF, INF);
    }
    //0重合返回原本点,1不重合返回对称点
    pair<int, Point> SymmetryPoint(Point q)
    {
        vectorPoint v1=vectorPoint(q-p);
        Point ans;
        if ((v1^v)==0)
        {
            return make_pair(0, q);
        }
        double ansx=-(((q^v)+2*(v^p))*v.y-(v*q)*v.x)/(v*v);
        double ansy=(((q^v)+2*(v^p))*v.x+(v*q)*v.y)/(v*v);
        if (epsCmp(ansx, 0)==0)
            ansx=0;
        if (epsCmp(ansy, 0)==0)
            ansy=0;
        return make_pair(1, Point(ansx, ansy));
    }
    //是否垂直
    bool isVertical(Line a)
    {
        return epsCmp(a.v*this->v, 0)==0;
    }
    Point projectPoint(Point p)
    {
        Line l=Line(p, Point(-v.y, v.x));
        return this->InterLine(l);
    }
};
struct LineSeg//线段
{
    Point left, right;
    LineSeg()
    {
        left=Point();
        right=Point();
    }
    LineSeg(Point a, Point b)
    {
        left=Point(a);
        right=Point(b);
    }
    //两线段是否相交
    bool InterLineSeg(LineSeg l1, LineSeg l2)
    {
        return
                max(l1.left.x, l1.right.x)>=min(l2.left.x, l2.right.x) &&
                max(l2.left.x, l2.right.x)>=min(l1.left.x, l1.right.x) &&
                max(l1.left.y, l1.right.y)>=min(l2.left.y, l2.right.y) &&
                max(l2.left.y, l2.right.y)>=min(l1.left.y, l1.right.y) &&
                sgn((l2.left-l1.right)^(l1.left-l1.right))*sgn((l2.right-l1.right)^(l1.left-l1.right))<=0 &&
                sgn((l1.left-l2.right)^(l2.left-l2.right))*sgn((l1.right-l2.right)^(l2.left-l2.right))<=0;
    }
    //点到线段距离
    double PointDis(Point x)
    {
        vectorPoint v1=vectorPoint(x-left);
        vectorPoint v2=vectorPoint(right-left);
        double r=v1*v2/v2.module()/v2.module();
//        printf("r=%lf\n",r);
        if (r>=1)
            return Point(right-x).module();
        else if (r<=0)
            return v1.module();
        else
        {
            Line line=Line(left, v2);
            return line.PointDis(x);
        }
    }
    //点是否在线段上
    bool OnSegment(Point p)
    {
        return epsCmp((p-left)^(right-left), 0)==0
               && epsCmp(min(left.x, right.x), p.x)<=0
               && epsCmp(p.x, max(left.x, right.x))<=0
               && epsCmp(min(left.y, right.y), p.y)<=0
               && epsCmp(p.y, max(left.y, right.y))<=0;
    }
    //0是无交点，1是有交点
    pair<int, Point> InterLine(Line a)
    {
        Line b=Line(left, right-left);
        if (a.isSame(b))
        {
            return make_pair(0, Point());
        }
        vectorPoint v1=vectorPoint(right-a.p);
        vectorPoint v2=vectorPoint(left-a.p);
        if (epsCmp((a.v^v1)*(a.v^v2), 0)<=0)
        {
            return make_pair(1, b.InterLine(a));
        }
        return make_pair(0, Point());
    }
};
struct Triangle//三角形
{
    Point a, b, c;
    Triangle()
    {
        a=b=c=Point();
    }
    Triangle(Point _a, Point _b, Point _c)
    {
        a=_a;
        b=_b;
        c=_c;
    }
    Triangle(vector<Point> points)
    {
        a=points[0];
        b=points[1];
        c=points[2];
    }
    bool isTriangle()
    {
        double aa=a.x-b.x;
        double bb=a.y-b.y;
        double cc=a.x-c.x;
        double dd=a.y-c.y;
        return epsCmp(bb*cc-aa*dd, 0)!=0;
    }
    //外心(外接圆，中垂线交点)
    Point Circumcenter()
    {
        if (isTriangle())
        {
            double aa=a.x-b.x;
            double bb=a.y-b.y;
            double cc=a.x-c.x;
            double dd=a.y-c.y;
            double ee=((a.x*a.x-b.x*b.x)-(b.y*b.y-a.y*a.y))*0.5;
            double ff=((a.x*a.x-c.x*c.x)-(c.y*c.y-a.y*a.y))*0.5;
            double x0=-(dd*ee-bb*ff)/(bb*cc-aa*dd);
            double y0=-(aa*ff-cc*ee)/(bb*cc-aa*dd);
            Point o=Point(x0, y0);
            return o;
        }
        return Point();
    }
    double Area()
    {
        return fabs((c-a)^(b-a))*0.5;
    }
    //重心(中线交点)
    Point Gravity()
    {
        return Point((a+b+c).x/3.0, (a+b+c).y/3.0);
    }
    //内心(角平分线交点)
    Point Incenter()
    {
        double disA=(b-c).module();
        double disB=(a-c).module();
        double disC=(a-b).module();
        double s=disA+disB+disC;
        double x=(disA*a.x+disB*b.x+disC*c.x)/s;
        double y=(disA*a.y+disB*b.y+disC*c.y)/s;
        return Point(x, y);
    }
};
struct Circle//圆形
{
    Point o;
    double r;
    Circle()
    {
        o=Point();
        r=0;
    }
    Circle(Circle const &pp)
    {
        this->o=pp.o;
        this->r=pp.r;
    }
    Circle(Point _o, double _r)
    {
        o=_o;
        r=_r;
    }
    Circle(Point a, Point b, Point c)
    {
        if (isCircle(a, b, c))
        {
            double aa=a.x-b.x;
            double bb=a.y-b.y;
            double cc=a.x-c.x;
            double dd=a.y-c.y;
            double ee=((a.x*a.x-b.x*b.x)-(b.y*b.y-a.y*a.y))*0.5;
            double ff=((a.x*a.x-c.x*c.x)-(c.y*c.y-a.y*a.y))*0.5;
            double x0=-(dd*ee-bb*ff)/(bb*cc-aa*dd);
            double y0=-(aa*ff-cc*ee)/(bb*cc-aa*dd);
            o=Point(x0, y0);
            r=(o-a).module();
        }
    }
    void print()
    {
        printf("circle:%.2f %.2f %.2f\n", o.x, o.y, r);
    }
    bool operator==(const Circle b) const
    {
        return this->o==b.o && this->r==b.r;
    }
    bool operator!=(const Circle b) const
    {
        return !(this->o==b.o && this->r==b.r);
    }
    double isCircle(Point a, Point b, Point c)
    {
        double aa=a.x-b.x;
        double bb=a.y-b.y;
        double cc=a.x-c.x;
        double dd=a.y-c.y;
        return epsCmp(bb*cc-aa*dd, 0)!=0;
    }
    double Area()
    {
        return pi*r*r;
    }
    //点与圆关系,0是外部,1是圆上,2是内部
    int interPoint(Point p)
    {
        double dis=(p-o).module();
        if (epsCmp(dis, r)>0)
            return 0;
        if (epsCmp(dis, r)==0)
            return 1;
        if (epsCmp(dis, r)<0)
            return 2;
    }
    //直线与圆关系,0相交,1相切,2相离
    int interLine(Line l)
    {
        double dis=l.PointDis(o);
        if (epsCmp(dis, r)<0)
            return 0;
        if (epsCmp(dis, r)==0)
            return 1;
        if (epsCmp(dis, r)>0)
            return 2;
    }
    //圆与圆关系,0是相离,1是外切,2是相交,3是内切,4是包含
    int interCircle(Circle circle)
    {
        double dis=(circle.o-o).module();
        if (epsCmp(dis, r+circle.r)>0)
        {
            return 0;
        }
        else if (epsCmp(dis, r+circle.r)==0)
        {
            return 1;
        }
        else if (epsCmp(dis, r+circle.r)<0 && epsCmp(dis, fabs(r-circle.r))>0)
        {
            return 2;
        }
        else if (epsCmp(dis, fabs(r-circle.r))==0)
        {
            return 3;
        }
        else if (epsCmp(dis, fabs(r-circle.r))<0)
        {
            return 4;
        }
    }
    //直线和圆交点
    pair<Point, Point> intersectLine(Line l)
    {
        if (interLine(l)!=2)
        {
            Point project=l.projectPoint(o);
            double base=sqrt(r*r-l.PointDis(o)*l.PointDis(o));
            base/=l.v.module();
            Point ansx=project+Point(l.v.x*base, l.v.y*base);
            Point ansy=project-Point(l.v.x*base, l.v.y*base);
            if (ansx.x>ansy.x || (ansx.x==ansy.x && ansx.y>ansy.y))
                swap(ansx, ansy);
            return make_pair(ansx, ansy);
        }
        return make_pair(Point(), Point());
    }
    //圆与圆交点
    pair<Point, Point> intersectCircle(Circle circle)
    {
        int flag=interCircle(circle);
        if (flag!=0 && flag!=4)
        {
            double d=(o-circle.o).module();
//        printf("d=%f\n",d);
            double a=acos((r*r+d*d-circle.r*circle.r)/(2*r*d));
//        printf("a=%f\n",a);
            double t=atan2((circle.o-o).y, (circle.o-o).x);
//        printf("t=%f\n",t);
            Point ansx=o+Point(r*cos(t+a), r*sin(t+a));
            Point ansy=o+Point(r*cos(t-a), r*sin(t-a));
//        ansx.print();
//        ansy.print();
            if (!(epsCmp(ansx.x, ansy.x)<0 || (epsCmp(ansx.x, ansy.x)==0 && epsCmp(ansx.y, ansy.y)<0)))
                swap(ansx, ansy);
            return make_pair(ansx, ansy);
        }
        return make_pair(Point(), Point());
    }
    //过圆外一点做切线,返回切线(和切点),圆外2条,圆上1条
    vector<Line> tangentLine(Point p)
    {
        vector<Line> ans;
        if (interPoint(p)==2)
        {
            return ans;
        }
        else if (interPoint(p)==1)//在圆上时直接做垂线
        {
            vectorPoint vp=o-p;
            Line line=Line(p, vectorPoint(-vp.y, vp.x));
            ans.push_back(line);
            return ans;
        }
        else
        {
            Point negO=Point(-o.x, -o.y);
            o=o+negO;
            p=p+negO;
            vectorPoint vectorOP=p-o;//OP方向向量
            Point q=Point(vectorOP.x*r/vectorOP.module(), vectorOP.y*r/vectorOP.module());
            //q是OP与圆的交点
//            q.print();
            double base=acos(r/vectorOP.module());//q点旋转两次即可
            Point ansX=q.rotate(base)-negO;
            Point ansY=q.rotate(-base)-negO;
            if (!(epsCmp(ansX.x, ansY.x)<0 || (epsCmp(ansX.x, ansY.x)==0 && epsCmp(ansX.y, ansY.y)<0)))
                swap(ansX, ansY);
            Line x=Line(ansX, p-ansX);
            ans.push_back(x);
            x=Line(ansY, p-ansY);
            ans.push_back(x);
            return ans;
        }
    }
    //过两个圆做公切线(开发中)
    vector<Line> tangentCircle(Circle circle)
    {
        vector<Line> ans;
        return ans;
    }
    double AreaWithCircle(Circle circle)
    {
        int z=this->interCircle(circle);
//        printf("z=%d\n",z);
        if (z==0 || z==1)
        {
            return 0;
        }
        if (z==3 || z==4)
        {
            return min(this->Area(), circle.Area());
        }
        double d=(o-circle.o).module();
        double A1=2*acos((d*d+this->r*this->r-circle.r*circle.r)/(2*d*this->r));
        double A2=2*acos((d*d+circle.r*circle.r-this->r*this->r)/(2*d*circle.r));
        double s1=0.5*this->r*this->r*sin(A1)+0.5*circle.r*circle.r*sin(A2);
        double s2=A1/2*this->r*this->r+A2/2*circle.r*circle.r;
//        printf("%.4f %.4f %.4f\n",S1,S2,S3);
        return s2-s1;
    }
};
struct Polygon//多边形
{
    vector<Point> points;
    int sumPoint=0;
    Polygon(vector<Point> v)
    {
        points.assign(v.begin(), v.end());
        sumPoint=v.size();
    }
    Polygon()
    {
        sumPoint=0;
    }
    double Perimeter()//计算周长，要求是个包,点要有顺序
    {
        double ans=0;
        for(int i=0; i<sumPoint; i++)
        {
            ans+=((points[i]-points[(i+1)%sumPoint]).module());
        }
        return ans;
    }
    static bool CmpAngle(Point a, Point b)//极角排序
    {
        double x=(a^b);
        if (epsCmp(x, 0)>0)
            return 1;
        if (epsCmp(x, 0)==0 && epsCmp(a.module(), b.module())<0)
            return 1;
        return 0;
    }
    static bool CmpXY(Point a, Point b)
    {
        return epsCmp(a.x, b.x)<0 || (epsCmp(a.x, b.x)==0 && epsCmp(a.y, b.y)<0);
    }//x,y顺序升序
    static bool CmpYX(Point a, Point b)
    {
        if (epsCmp(a.y, b.y)!=0)
            return epsCmp(a.y, b.y)<0;
        return (epsCmp(a.y, b.y)==0 && epsCmp(a.x, b.x)<0);
    }//y,x顺序升序
    double Area()
    {
        double ans=0;
        for(int i=0; i<sumPoint; i++)
        {
            ans+=(points[i]^points[(i+1)%sumPoint]);
        }
        return fabs(ans/2.0);
        //TODO:面积公式需要修改
    }
    bool IsConvex()//逆时针点判断凹凸性，顺时针符号相反
    {
        for(int i=1; i<sumPoint; i++)
        {
            vectorPoint a=vectorPoint(points[(i+1)%sumPoint]-points[i]);
            vectorPoint b=vectorPoint(points[(i+2)%sumPoint]-points[(i+1)%sumPoint]);
            if (epsCmp(a^b, 0)==-1)
            {
                return false;
            }
        }
        return true;
    }
    bool CounterClockWise(Point a, Point b, Point c)
    {
        return epsCmp((c.x-a.x)*(b.y-a.y)-(c.y-a.y)*(b.x-a.x), 0)<0;
    }
    //判断点是否在多边形内(0是内，1是边，2是外),点要顺/逆时针
    int Contain(Point p)
    {
        //采用环顾法（射线法），过P点做每条线的平行线
        // 每次转过的角度（带正负）之和为0->外部，为2pi->内部
        //边上特判
        double total=0;
        for(int i=0; i<sumPoint; i++)
        {
            LineSeg lineSeg=LineSeg(points[i], points[(i+1)%sumPoint]);
            if (lineSeg.OnSegment(p))
                return 1;
            vectorPoint v1=vectorPoint(points[i]-p);
            vectorPoint v2=vectorPoint(points[(i+1)%sumPoint]-p);
            if (v1.isParallel(v2))//平行就跳过
                continue;
            if (epsCmp(v1^v2, 0)>=0)
                total+=v1.angleWith(v2);
            else
                total-=v1.angleWith(v2);
        }
        if (epsCmp(total, 2*pi)==0)
            return 0;
        if (epsCmp(total, 0)==0)
            return 2;
    }
    Polygon Graham_ConvexHull()//Graham扫描线凸包(O(nlogn))
    {
        Point ans[sumPoint+1];//存答案
        int tot=0;//凸包点个数
        int indexLower=0;//最下面的
        for(int i=1; i<sumPoint; i++)//找到纵坐标最小的点
        {
            if (epsCmp(points[i].y, points[indexLower].y)<0 ||
                (epsCmp(points[i].y, points[indexLower].y)==0 && epsCmp(points[i].x, points[indexLower].x)<=0))
            {
                indexLower=i;
            }
        }
        Point base=points[indexLower];
        swap(points[indexLower], points[0]);//让base点作为第0个点
        for(int i=0; i<sumPoint; i++)
        {
            points[i]=points[i]-base;//让base点平移到原点
        }
        sort(points.begin()+1, points.end(), CmpAngle);//极角排序
        ans[1]=points[0];
        ans[2]=points[1];
        ans[3]=points[2];//第0,1,2个一定是凸包上的点
        tot=3;
        for(int i=3; i<sumPoint; i++)
        {
            while((epsCmp((vectorPoint(points[i]-ans[tot-1])^vectorPoint(ans[tot]-ans[tot-1])), 0)>=0))
                //这边把>=0改为=0会把共线的也取上(大概吧)
            {
                if (!tot)
                    break;
                tot--;
            }
            ans[++tot]=points[i];
        }
        vector<Point> ans1;
        for(
                int i=1;
                i<=
                tot;
                i++)
        {
            ans[i]=ans[i]+base;//还原
            ans1.push_back(ans[i]);
        }
        return
                Polygon(ans1);
    }
    Polygon Jarvis_ConvexHull()//Jarvis凸包(O(nm),m为凸包定点数)
    {
        int left=0;
        for(int i=1; i<sumPoint; i++)//找到最左边的点
        {
            if (epsCmp(points[i].x, points[left].x)<0 ||
                (epsCmp(points[i].x, points[left].x)==0 && epsCmp(points[i].y, points[left].y)<0))
                left=i;
        }
        int first_point=left;
        int third_point;
        vector<Point> ans;
        do
        {
            ans.push_back(points[first_point]);
            third_point=(first_point+1)%sumPoint;
            for(int i=0; i<sumPoint; i++)
            {
                if (CounterClockWise(points[first_point], points[i], points[third_point]))
                {
                    third_point=i;
                }
            }
            first_point=third_point;
        } while(first_point!=left);
//        for(int i=0;i<ans.size();i++)
//        {
//            ans[i].print();
//        }
        return Polygon(ans);
    }
    Polygon Andrew_ConvexHull()
    //Andrew凸包,比Graham更快更好,会加入原本被Graham丢掉的点(O(nlogn))
    //点按照逆时针排列
    {
        vector<Point> ans;
        sort(points.begin(), points.end(), CmpYX);
        ans.push_back(points[0]);
        ans.push_back(points[1]);
        for(int i=2; i<sumPoint; i++)//下半个凸包
        {
            while(ans.size()>1 &&
                  epsCmp(vectorPoint(ans[ans.size()-1]-ans[ans.size()-2])^vectorPoint(points[i]-ans[ans.size()-2]), 0)
                  <=0)
            {
                ans.pop_back();
            }
            ans.push_back(points[i]);
        }
        int k=ans.size();
        for(int i=sumPoint-2; i>=0; i--)//上半个凸包
        {
            while(ans.size()>k &&
                  epsCmp(vectorPoint(ans[ans.size()-1]-ans[ans.size()-2])^vectorPoint(points[i]-ans[ans.size()-2]), 0)
                  <=0)
            {
                ans.pop_back();
            }
            ans.push_back(points[i]);
        }
        if (sumPoint>1)
            ans.pop_back();
        vector<Point> ans1;
        int index=0;
        for(int i=1; i<ans.size(); i++)
        {
            if (!CmpYX(ans[index], ans[i]))
                index=i;
        }
        for(int i=0; i<ans.size(); i++)
        {
            ans1.push_back(ans[(i+index)%ans.size()]);
        }
        return Polygon(ans1);
    }
    Polygon Melkman_ConvexHull()
    //Melkman凸包,O(nlogn),是半成品！
    // 如果是简单凸边形的凸包就是(O(n))
    {
//        sort(points.begin(), points.end(), CmpXY);//是否需要排序
        int left=sumPoint-1, right=sumPoint;
        Point ans[2*sumPoint+100];
        //维护双端队列,且头尾元素相同
        ans[right++]=points[0];
        ans[right++]=points[1];
        int k=0;
        for(int i=2; i<sumPoint; i++)//寻找第三个不共线的
        {
            if (epsCmp(vectorPoint(ans[right-1]-ans[right-2])^vectorPoint(points[i]-ans[right-2]), 0)!=0)
            {
                points[left--]=points[i];
                points[right++]=points[i];
                k=i;
                break;
            }
            ans[right-1]=points[i];
        }
        if (epsCmp(vectorPoint(ans[sumPoint+1]-ans[sumPoint])^vectorPoint(ans[sumPoint+2]-ans[sumPoint+1]), 0)!=0)
            //保证头三个点逆时针
        {
            swap(ans[sumPoint], ans[sumPoint+1]);
        }
        for(int i=k+1; i<sumPoint; i++)
        {
            if (epsCmp(vectorPoint(points[i]-ans[right-1])^vectorPoint(ans[right-2]-ans[right-1]), 0)>0
                &&
                epsCmp(vectorPoint(ans[left+2]-ans[left+1])^vectorPoint(points[i]-ans[left+1]), 0)>0
                    )
            {
                continue;
            }//点在凸包内
            while(epsCmp(vectorPoint(ans[right-2]-points[i])^vectorPoint(ans[right-1]-points[i]), 0)<=0)
            {
                right--;
            }
            ans[right++]=points[i];
            while(epsCmp(vectorPoint(ans[left+2]-ans[left+1])^vectorPoint(points[i]-ans[left+2]), 0)<=0)
            {
                left++;
            }
            ans[left--]=points[i];
        }
        vector<Point> x;
        for(int i=left+1; i<=right-1; i++)
        {
            x.push_back(ans[i]);
            ans[i].print();
        }
        return Polygon(x);
    }
    Point Gravity()
    //多边形重心
    {
        double ansx=0, ansy=0;
        double s=0;
        for(int i=1; i<sumPoint-1; i++)
        {
            Triangle triangle=Triangle(points[0], points[i], points[i+1]);
            double area=triangle.Area();
            Point g=((points[0]+points[i])+points[i+1]);
            ansx+=(area*g.x);
            ansy+=(area*g.y);
            s+=area;
        }
        return Point(ansx/s/3.0, ansy/s/3.0);
    };
    void print()
    {
        printf("%d\n", sumPoint);
        for(int i=0; i<sumPoint; i++)
        {
            points[i].print();
        }
    }
    double Diameter()
    //多边形直径（凸多边形中距离最远的点，旋转卡壳），复杂度O(n)
    //要先求过凸包，因此可能总复杂度是O(nlogn)
    {
        if (sumPoint==1 || sumPoint==0)
        {
            return 0;
        }
        if (sumPoint==2)
        {
            return (points[0]-points[1]).module();
        }
        double ans=-inf;
        int q=1;
        for(int i=0; i<sumPoint; i++)
        {
            while(epsCmp((points[q]-points[(i+1)%sumPoint])^(points[i]-points[(i+1)%sumPoint]),
                         (points[(q+1)%sumPoint]-points[(i+1)%sumPoint])^(points[i]-points[(i+1)%sumPoint]))<0)
            {
                q=(q+1)%sumPoint;
            }
            ans=max(ans, max((points[q]-points[i]).module(), (points[(q+1)%sumPoint]-points[(i+1)%sumPoint]).module()));
        }
        return ans;
    }
    double Width()
    //多边形宽度（凸多边形中距离最近的点，旋转卡壳），复杂度O(n)
    //    //要先求过凸包，因此可能总复杂度是O(nlogn)
    {
        if (sumPoint==1 || sumPoint==0)
        {
            return 0;
        }
        if (sumPoint==2)
        {
            return (points[0]-points[1]).module();
        }
        double ans=inf;
        int q=1;
        for(int i=0; i<sumPoint; i++)
        {
            while(epsCmp((points[q]-points[(i+1)%sumPoint])^(points[i]-points[(i+1)%sumPoint]),
                         (points[(q+1)%sumPoint]-points[(i+1)%sumPoint])^(points[i]-points[(i+1)%sumPoint]))<0)
            {
                q=(q+1)%sumPoint;
            }
            ans=min(ans, min((points[q]-points[i]).module(), (points[(q+1)%sumPoint]-points[(i+1)%sumPoint]).module()));
        }
        return ans;
    }
    double ClosetPair(int left, int right)
    //n对点中最近的一对，采用二分,一开始调用是（0,n-1）
    //半成品，有bug
    {
        printf("[%d,%d]\n",left,right);
        vector<Point> temp;
        double d=inf;
        if (right-left<=1)//1个点
        {
            return d;
        }
        if (left+1==right)//2个点
        {
            return (points[left]-points[right]).module();
        }
        int mid=(left+right)>>1;
        double d1=ClosetPair(left, mid);
        double d2=ClosetPair(mid+1, right);
        if (epsCmp(d1, d2)<=0)
            d=d1;
        else
            d=d2;
        for(int i=left; i<=right; i++)
        {
            if (epsCmp(points[mid].x-points[i].x, d)<=0)
            {
                temp.push_back(points[i]);
            }
        }
        sort(temp.begin(), temp.end(), CmpYX);
        for(int i=0; i<temp.size(); i++)
        {
            for(int j=i+1; j<temp.size() && epsCmp(temp[j].y-temp[i].y, d)<0; j++)
            {
                double d3=(temp[i]-temp[j]).module();
                if(epsCmp(d3,d)<=0)
                    d=d3;
            }
        }
        return d;
    }
};