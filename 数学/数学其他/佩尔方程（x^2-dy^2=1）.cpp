//x^2-Dy^2=1
//x[n]=x[n-1]*x[1]+D*y[n-1]*y[1]
//y[n]=y[n-1]*x[1]+x[n-1]*y[1]
int x[N],y[N];
void pell(int &a,int &b,int d){//暴力寻找pell方程最小解
    b=1;
    while(true){
        a=(LL)sqrt(d*b*b+1);
        if(a*a-d*b*b==1)
            break;
        b++;
    }
}
int main(){
    int d;
    while(scanf("%d",&d)!=EOF){
        int m=(int)sqrt((double)d);
        if(m*m==d){//d不能为完全平方数
            cout<<"No Solution"<<endl;
            continue;
        }

        int a=0,b=0;
        pell(a,b,d);//暴力找到最小解
        x[1]=a,y[1]=b;//第一组解
        for(int i=2;i<=10;i++){//递推公式
            x[i]=x[i-1]*x[1]+d*y[i-1]*y[1];
            y[i]=x[i-1]*y[1]+y[i-1]*x[1];
        }
        for(int i=1;i<=10;i++)
            cout<<x[i]<<" "<<y[i]<<endl;
    }
    return 0;
}