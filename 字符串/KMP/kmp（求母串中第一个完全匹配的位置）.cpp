#include<bits/stdc++.h>
#define ll long long
//KMP（求母串中第一个匹配到字符）
const int maxn=1e6;
int Next[maxn+10];
//Next[i]表示在i之前最大相同前后缀的长度
//判断循环节：计算i%(i-Next[i])==0 ,Next[i]!=0,
//循环节长度为i/(i-next[i]) i=1~len
void GetNext(char p[], int lenp)
{
    Next[0]=-1;
    int k=-1;
    int j=0;
    while(j<lenp)
    {
        //p[k]为前缀,p[j]为后缀
        if (k==-1 || p[j]==p[k])
        {
            k++;
            j++;
            Next[j]=k;//如果匹配，说明最大相同前后缀
        }
        else
        {
            k=Next[k];
        }
    }
//	{
//		printf("The Next of %s: ",p);
//		for(int i=1;i<lenp;i++)
//		{
//			printf("%lld ",Next[i]);
//		}
//		printf("\n");
//	}
}
void PrintNext(int lenp)
{
    for(int i=0; i<=lenp; i++)
    {
        printf("i=%d next=%d\n", i, Next[i]);
    }
    printf("\n");
}
ll GetKMP(char s[], char p[], int lens, int lenp)//s是母串，p是模式串
{
    ll ans=0;
    int i=0, j=0;
    while(i<lens && j<lenp)
    {
        if (j==-1 || s[i]==p[j])//匹配成功
        {
            i++;
            j++;
        }
        else
        {
            j=Next[j];
        }
//        if (j==lenp)
//        {
//            ans++;
//            j=Next[j];
//        }//匹配次数
    }
//    return ans;
    if (j==lenp)//匹配成功，即p中每个字符都对上了
        return i-j+1;
    else
        return -1;//未匹配到
}
ll KMP(char s[], char p[], int lens, int lenp)
{
    GetNext(p, lenp);
    return GetKMP(s, p, lens, lenp);
}