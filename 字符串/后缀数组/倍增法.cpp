namespace SA
{
    int SA[maxn+10];//所有后缀排序后第i小的后缀的起始位置的下标;
    int Rank[maxn+10];//Rank[i] 第i个后缀的排名,SA[Rank[i]]=Rank[SA[i]]=i
    int Height[maxn+10];
    //Height[i]=排名为i的后缀与排名为(i-1)的后缀的最长公共前缀
    //Height[i]>=Height[i-1]+1
    //LCP(i,k)=min(LCP(j,j-1)) (1<i<=j<=k<=n)
    //不同子串的个数:n(n+1)/2-(Height[2]+Height[3]+...+Height[n])
    int tax[maxn+10], tp[maxn+10];
    //tax[i] 计数排序辅助数组;
    //tp[i] rk的辅助数组(计数排序中的第二关键字),与SA意义一样。
    int len;
    char s[maxn+10];
    int m;//m当前离散后的排名种类数
    void RSort()
    {
        //rk第一关键字,tp第二关键字
        for(int i=0; i<=m; i++) tax[i]=0;
        for(int i=1; i<=len; i++) tax[Rank[tp[i]]]++;
        for(int i=1; i<=m; i++) tax[i]+=tax[i-1];
        for(int i=len; i>=1; i--) SA[tax[Rank[tp[i]]]--]=tp[i];
        //确保满足第一关键字的同时，再满足第二关键字的要求
    }//计数排序,把新的二元组排序
    int cmp(int *f, int x, int y, int w)
    {
        return f[x]==f[y] && f[x+w]==f[y+w];
    }
    //通过二元组两个下标的比较，确定两个子串是否相同
    void GetSA()
    {
        for(int i=1; i<=len; i++)
        {
            Rank[i]=s[i], tp[i]=i;
        }
        RSort();
        for(int w=1, p=1, i; p<len; w+=w, m=p)
        {
            //把子串长度翻倍,更新rk
            //w 当前一个子串的长度;
            //当前的tp(第二关键字)可直接由上一次的SA的得到
            for(p=0, i=len-w+1; i<=len; i++)
                tp[++p]=i; //长度越界,第二关键字为0
            for(i=1; i<=len; i++)
                if (SA[i]>w)
                    tp[++p]=SA[i]-w;
            //更新SA值,并用tp暂时存下上一轮的rk(用于cmp比较)
            RSort(), swap(Rank, tp), Rank[SA[1]]=p=1;
            //用已经完成的SA来更新与它互逆的rk,并离散rk
            for(i=2; i<=len; i++)
                Rank[SA[i]]=cmp(tp, SA[i], SA[i-1], w) ? p : ++p;
        }
        //离散：把相等的字符串的rk设为相同。
    }
    void GetHeight()
    {
        //LCP
        int j, k=0;
        for(int i=1; i<=len; Height[Rank[i++]]=k)
            for(k=k ? k-1 : k, j=SA[Rank[i]-1]; s[i+k]==s[j+k]; ++k);
        //这个知道原理后就比较好理解程序
    }
    void PrintSA()
    {
        for(int i=1; i<=len; i++)
        {
            printf("%d ", SA[i]);
        }
        printf("\n");
    }
    void PrintHeight()
    {
        for(int i=1; i<=len; i++)
        {
            printf("%d ", Height[i]);
        }
        printf("\n");
    }
    void PrintRank()
    {
        for(int i=1; i<=len; i++)
        {
            printf("%d ", Rank[i]);
        }
        printf("\n");
    }
}
/**
int len=strlen(a+1);
for(int i=1; i<=len; i++)
{
SA::s[i]=a[i];
}
SA::s[len+1]=0;
SA::len=len;
SA::m=200;
SA::GetSA();
SA::GetHeight();
 */