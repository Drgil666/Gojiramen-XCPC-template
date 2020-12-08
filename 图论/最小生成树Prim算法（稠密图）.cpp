#include <stdio.h>
#include <stdlib.h>
#define count 100000//迷宫尺寸
void prim(int a[][count],int u[],int w[],int b[],int n)
{
    int i=0,j=0,m=0,min;//min的10000指代无穷大
    for(i=0;i<count;i++)
    {
        u[i]=0;//初始化0，说明没有访问过
        w[i]=a[0][i];//初始每个顶点最短路径为到0顶点的距离
        b[i]=0;//初始每个顶点都指向0顶点
    }
    u[0]=1;//赋值1，从0顶点开始
    for(i=1;i<n;i++)
    {
        min=10000;
        j=0;
        for(m=1;m<n;m++)
        {
            if(!u[m] && w[m]<min)//很关键，得到到访问顶点到未访问顶点的最短路径以及对应顶点j
            {
                min=w[m];
                j=m;
            }
        }//记录最短的边，同时防止成环
        u[j]=1;//把下一个顶点标为已访问
        printf("%d,%d\n",j+1,b[j]+1);//输出结果
        for(m=1;m<n;m++)
        {
            if(!u[m] && a[j][m]<w[m])//此时，u集合里面多了一个顶点j，要重新更新最短路径以及对应的顶点
            {
                w[m]=a[j][m];//记录最短路径
                b[m]=j;//记录节点
            }
        }
    }
}
int main()
{
    int u[count],w[count],b[count],a[count][count];
    int i=0,j=0;
    for(i=0;i<count;i++)
    {
        for(j=0;j<count;j++)
        {
            a[i][j]=10000;//表示此路不通,即无穷大
        }
    }
    a[0][1]=6,a[0][2]=1,a[0][3]=5;
    a[1][0]=6,a[1][2]=5,a[1][4]=3;
    a[2][0]=1,a[2][1]=5,a[2][3]=5,a[2][4]=6,a[2][5]=4;
    a[3][0]=5,a[3][2]=5,a[3][5]=2;
    a[4][1]=3,a[4][2]=6,a[4][5]=6;
    a[5][3]=2,a[5][2]=4,a[5][4]=6;//矩阵赋值
    /*for(int i=0;i<6;i++)
        {
            for(int j=0;j<6;j++)
                printf("%3d ",a[i][j]);
        printf("\n");
        }*/
    prim(a,u,w,b,count);
    return 0;
}