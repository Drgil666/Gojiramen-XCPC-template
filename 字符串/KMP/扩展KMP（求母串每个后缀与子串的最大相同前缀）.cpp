#include<bits/stdc++.h>
using namespace std;
#define ll long long
//求母串每个后缀与子串的最大相同前缀
//于原串S1的每一个后缀子串与模式串S2的最长公共前缀。
//next[i]表示为以模式串s2中以i为起点的后缀字符串和模式串s2的最长公共前缀长度.
//extend[i]表示为以字串s1中以i为起点的后缀字符串和模式串s2的最长公共前缀长度.
const int maxn=2e5;
ll Next[maxn+10];
ll Extend[maxn+10];
void GetNext(char p[])
{
    int plen=strlen(p);
    int pos=1, k=0, i=0, j=0;
    Next[0]=strlen(p);//自己和自己的最大前缀长度就是字符串长度本身
    while(p[i]==p[i+1] && i+1<plen)
        i++;
    Next[1]=i;//Next[1]暴力求出
    for(i=2; i<plen; i++)
    {
        if (Next[i-pos]+i<Next[pos]+pos)
            Next[i]=Next[i-pos];
        else
        {
            j=max(Next[pos]+pos-i, 0LL);
            while(i+j<plen && p[i+j]==p[j])
                j++;
            Next[i]=j;
            pos=i;
        }
    }
}
void PrintNext(int lenp)
{
    for(int i=0; i<=lenp; i++)
    {
        printf("i=%d next=%d\n", i, Next[i]);
    }
    printf("\n");
}
void PrintExtend(int lenp)
{
    for(int i=0; i<=lenp; i++)
    {
        printf("i=%d extend=%d\n", i, Extend[i]);
    }
    printf("\n");
}
void GetExtend(char *s, char *p)
{
    int lens=strlen(s);
    int lenp=strlen(p);
    int i=0, j, pos;
    while(i<lens && i<lenp && s[i]==p[i])
        i++;
    Extend[0]=i;//Extend[0]可以暴力求出
    pos=0;
    for(i=1; i<lens; i++)
    {
        if (Next[i-pos]+i<Extend[pos]+pos)
            Extend[i]=Next[i-pos];
        else
        {
            j=max(Extend[pos]+pos-i, 0LL);
            while(i+j<lens && s[i+j]==p[j])
                j++;
            Extend[i]=j;
            pos=i;
        }
    }
}
void EXKMP(char s[],char p[])
{
    GetNext(p);
    GetExtend(s, p);
}