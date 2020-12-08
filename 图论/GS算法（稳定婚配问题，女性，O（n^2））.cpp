#include<stdio.h>
#include<string.h>
#include<string>
#include<map>
#include<iostream>
#include<algorithm>
#define maxn 555
using namespace std;
int tot;
int n;
int b[maxn][maxn];///男生i第j个喜欢的女生是几号
int g[maxn][maxn];///女生i男生j的排名
int by[maxn],gl[maxn];///匹配情况
int r[maxn];
char s[100];
string bo[maxn],gi[maxn];///记录第i个男生或者女生的名字
int main()
{
    int bn,gn,t,flag,i,j,f;
    while(scanf("%d",&n)!=EOF)
    {
        f=0;
        getchar();
        gn=1;
        memset(b,0,sizeof(b));
        memset(g,0,sizeof(g));
        for(i=1;i<=n;i++)
            r[i]=1;
        map<string,int>boy,girl;//建立名字与编号的映射
        boy.clear(),girl.clear();
        tot=1;
        for(i=1;i<=n;i++)//男生录入数据，人名编号化、关系数字化处理
        {
            scanf("%s",s);
            boy[s]=i;//将第i个人编号为i
            bo[i]=s;
            for(j=1;j<=n;j++)
            {
                scanf("%s",s);
                if(!girl[s])
                {
                    girl[s]=j;
                    gi[j]=s;
                    b[i][j]=j;//建立优先顺序
                }
                else b[i][j]=girl[s];//已被编号
            }
        }
        for(i=1;i<=n;i++)//女生建立排名
        {
            scanf("%s",s);
            t=girl[s];
            for(j=1;j<=n;j++)
            {
                scanf("%s",s);
                g[t][boy[s]]=j;
            }
        }
        memset(by,0,sizeof(by));
        memset(gl,0,sizeof(gl));
        while(1)
        {
            flag=1;
            for(i=1;i<=n;i++)
                if(!by[i])//男生i未匹配
                {
                    t=b[i][r[i]++];///t是他喜欢的女生且他还没有匹配过
                    if(!gl[t])///如果这个女生刚好没对象，就结成一对
                    {
                        by[i]=t;
                        gl[t]=i;
                    }
                    else if(g[t][gl[t]]>g[t][i])
                        ///如果她有对象了，但是她更喜欢当前这个男生，则女生抛弃之前的男生和这个结成一对
                    {
                        by[gl[t]]=0;
                        gl[t]=i;
                        by[i]=t;
                    }
                    flag=0;
                }
            if(flag)
                break;//所有的都完成匹配则退出
        }
        for(i=1;i<=n;i++)
            cout<<bo[i]<<' '<<gi[by[i]]<<endl;
        printf("\n");
    }
    return 0;
}
