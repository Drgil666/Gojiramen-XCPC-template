#include<cstdio>
#include<string.h>
#include<algorithm>
#include<queue>
const int N=100;
using namespace std;
const long long mod=100000;
char s[N+10];
//AC自动机计数（计算不包含模式串的，如果要改成包含的，让矩阵1变0,0变1）
//AC自动机：在Trie树的基础上增加一个fail指针，当模式串失配时直接转移。
int tot;//节点数
int trie[N+10][4];//trie[i][j]表示节点i的第j个儿子
int End[N+10];//有多少单词以i为结尾
int Fail[N+10];//Fail指针
int change(char x)
{
    if(x=='A')
        return 0;
    if(x=='T')
        return 1;
    if(x=='C')
        return 2;
    if(x=='G')
        return 3;
}
struct Matrix
{
    long long m[110][110];
};
void Trie_init()//初始化
{
    tot++;
    End[tot]=0;
    Fail[tot]=0;
    for(int j=0;j<4;j++)
        trie[tot][j]=0;
    return;
}
void Trie_insert(char str[])//插入
{
    int len=strlen(str);
    int root=0;//表示父节点编号
    for(int i=0;i<len;i++)
    {
        int id=change(str[i]);
        if(!trie[root][id])//需要添加新节点
        {
            Trie_init();
            trie[root][id]=tot;
        }
        root=trie[root][id];//父节点转移到下一层
    }
    End[root]=1;
}
void GetFail()
{
//	Fail[0]=0;
    queue<int>q;//需要bfs的队列
    for(int i=0;i<4;i++)//遍历第二层bfs,把他们指到根节点
    {
        if(trie[0][i])
        {
//			Fail[trie[0][i]]=0;//根节点
            q.push(trie[0][i]);//扔到bfs队列里
        }
    }
    while(!q.empty())
    {
        int now=q.front();//now表示当前正在处理的点
        if(End[Fail[now]])
            End[now]=1;
        q.pop();
        for(int i=0;i<4;i++)
        {
            if(trie[now][i])//如果子节点有字母
            {
                Fail[trie[now][i]]=trie[Fail[now]][i];
                //重点！该子节点的fail指针=父节点fail指针的子节点
                q.push(trie[now][i]);
            }
            else//该节点不存在字母
            {
                trie[now][i]=trie[Fail[now]][i];
                //该节点的子节点=该节点fail指针的子节点
            }

        }
    }
}
Matrix GetMatrix(Matrix A)
{
    memset(A.m,0,sizeof(A.m));
    for(int i=0;i<=tot;i++)
    {
        if(End[i])continue;
        for(int j=0;j<4;j++)
        {
            if(!End[trie[i][j]])
                A.m[i][trie[i][j]]++;
        }
    }
    return A;
}
Matrix Mul(Matrix A,Matrix B)
{
    Matrix C;
    for(int i=0;i<=tot;i++)//枚举行
    {
        if(End[i])continue;
        for(int j=0;j<=tot;j++)//枚举列
        {
            C.m[i][j]=0;
            if(End[j])continue;
            for(int k=0;k<=tot;k++)
                C.m[i][j]=(C.m[i][j]+(A.m[i][k]%mod)*(B.m[k][j]%mod))%mod;
        }
    }
    return C;
}
Matrix Pow(Matrix A,long long n)
{
    Matrix ret;
    memset(ret.m,0,sizeof(ret.m));
    for(int i=0;i<=tot;i++)
    {
        ret.m[i][i]=1;
    }
    while(n)
    {
        if(n&1)
            ret=Mul(ret,A);
        A=Mul(A,A);
        n>>=1;
    }
    return ret;
}
int main()
{
    long long n,m;
    while(~scanf("%lld%lld",&n,&m))
    {
        tot=-1;
        Trie_init();
        for(int i=1;i<=n;i++)
        {
            scanf("%s",s);
            Trie_insert(s);
        }
        GetFail();
        Matrix init;
        init=GetMatrix(init);
        init=Pow(init,m);
        long long ans=0;
        for(int i=0;i<=tot;i++)
            ans=(ans+init.m[0][i])%mod;
        printf("%lld\n",ans);
    }
}