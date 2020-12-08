#include<bits/stdc++.h>
const int N=2e6;//字符串个数
using namespace std;
char s[N+10];
char s1[2000010];
//匹配次数，包括重复的
//AC自动机：在Trie树的基础上增加一个fail指针，当模式串失配时直接转移。
int tot;//节点数
int trie[N+10][26];//trie[i][j]表示节点i的第j个儿子
int End[N+10];//有多少单词以i为结尾
int Fail[N+10];//Fail指针
int vis[N+10];
int MAP[N+10];//用来计算重复的模式串
void Trie_init()//初始化
{
    tot++;
    End[tot]=0;
    Fail[tot]=0;
    for(int j=0;j<26;j++)
        trie[tot][j]=0;
    return;
}
void Trie_insert(char str[],int id)//插入
{
    int len=strlen(str);
    int root=0;//表示父节点编号
    for(int i=0;i<len;i++)
    {
        int id=str[i]-'a';
        if(!trie[root][id])//需要添加新节点
        {
            Trie_init();
            trie[root][id]=tot;
        }
        root=trie[root][id];//父节点转移到下一层
    }
    if(!End[root])
        End[root]=id;
    MAP[id]=End[root];
}
void GetFail()
{
    Fail[0]=0;
    queue<int>q;//需要bfs的队列
    for(int i=0;i<26;i++)//遍历第二层bfs,把他们指到根节点
    {
        if(trie[0][i])
        {
            Fail[trie[0][i]]=0;//根节点
            q.push(trie[0][i]);//扔到bfs队列里
        }
    }
    while(!q.empty())
    {
        int now=q.front();//now表示当前正在处理的点
        q.pop();
        for(int i=0;i<26;i++)
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
int AC_automaton(char s[])
{
    int ans=0,now=0;//w是正在处理的点
    int lens=strlen(s);
    for(int i=0;i<lens;i++)
    {
        now=trie[now][s[i]-'a'];//递归处理
        for(int j=now;j;j=Fail[j])
        {
            if(End[j])
                vis[End[j]]++;//累加
        }//j不断递归到Fail,直到已经被扫过或者指向根节点
    }
    return ans;
}
void debug()
{
    for(int i=0;i<=tot;i++)
    {
        printf("id = %3d,fail = %3d,end = %3d,trie = [",i,Fail[i],End[i]);
        for(int j=0;j<26;j++)
            printf("%2d",trie[i][j]);
        puts("]");
    }
}
int main()
{
    int n;
    scanf("%d",&n);
    tot=-1;
    Trie_init();
    for(int i=1;i<=n;i++)
    {
        scanf("%s",s);
        Trie_insert(s,i);
    }
    GetFail();
    scanf("%s",s1);
    AC_automaton(s1);
    for(int i=1;i<=n;i++)
        printf("%d\n",vis[MAP[i]]);
    for(int i=1;i<=n;i++)
    {
        vis[i]=0;
        MAP[i]=0;
    }
}
