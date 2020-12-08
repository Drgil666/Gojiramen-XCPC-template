#include <stdio.h>
int a[1000000]={0};
int main()
{
    int n,i,j;
    while(scanf("%d",&n)!=EOF)
    {
        a[0]=1;
        int s,c=0,len=0;
        for(i=2;i<=n;i++)
            for(j=0;j<=len;j++)
            {
                s=a[j]*i+c;
                a[j]=s%10;
                c=s/10;
                if(j==len&&c!=0)
                    len++;
            }
        for(j=len;j>=0;j--)
            printf("%d",a[j]);
        printf("\n");
    }
    return 0;
}