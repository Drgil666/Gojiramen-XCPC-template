//#pragma comment(linker, "/STACK:102400000,102400000")
#include<bits/stdc++.h>
using namespace std;
const long long maxn=2e7;
//ÂíÀ­³µ£º×î´ó»ØÎÄ×Ó´®
char s[2*maxn+10],st[2*maxn+10];
int p[2*maxn+10];
int change()
{
    int len=strlen(st);
    int j=2;
    s[0]='^';
    s[1]='$';
    for (int i=0;i<len;i++)
    {
        s[j++]=st[i];
        s[j++]='$';
    }
    s[j]='&';
    return j;
}
int Manacher(char *s, int *p)
{
    int len=change(),mid=1,mx=1,ans=-1;
    for (int i=1;i<len;i++)
    {
        if (i<mx)
            p[i]=min(mx-i,p[mid*2-i]);
        else
            p[i]=1;
        while (s[i-p[i]]==s[i+p[i]])
            p[i]++;
        if (mx<i+p[i])
        {
            mid=i;
            mx=i+p[i];
        }
        ans=max(ans,p[i]-1);
    }
    return ans;
}
int main()
{
    scanf("%s",st);
    int pos;
    long long ans=Manacher(s,p);
//    char ss[N+10];
//    strncpy(ss,s+pos,ans);
//    printf("%lld %lld %s",pos,ans,ss);
    printf("%lld\n",ans);
}