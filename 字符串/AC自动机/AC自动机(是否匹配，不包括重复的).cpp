#include<bits/stdc++.h>
const int N=1e4+5;//字符串个数
const int length=55;//单个长度
using namespace std;
//是否匹配，不包括重复的的版本
//AC自动机：在Trie树的基础上增加一个fail指针，当模式串失配时直接转移。
int tot;//节点数
int trie[N*length][26];//trie[i][j]表示节点i的第j个儿子
int End[N*length];//有多少单词以i为结尾
int Fail[N*length];//Fail指针
void Trie_init()//初始化
{
    tot++;
    End[tot]=0;
    Fail[tot]=0;
    for(int j=0; j<26; j++)
        trie[tot][j]=0;
    return;
}
void Trie_insert(char *str)//插入
{
    int len=strlen(str);
    int root=0;//表示父节点编号
    for(int i=0; i<len; i++)
    {
        int id=str[i]-'a';
        if (!trie[root][id])//需要添加新节点
        {
            Trie_init();
            trie[root][id]=tot;
        }
        root=trie[root][id];//父节点转移到下一层
    }
    End[root]++;//最后一个字母
}
void GetFail()
{
    //Fail[0]=0;
    queue<int> q;//需要bfs的队列
    for(int i=0; i<26; i++)//遍历第二层bfs,把他们指到根节点
    {
        if (trie[0][i])
        {
            //Fail[trie[0][i]]=0;//根节点
            q.push(trie[0][i]);//扔到bfs队列里
        }
    }
    while(!q.empty())
    {
        int now=q.front();//now表示当前正在处理的点
        q.pop();
        for(int i=0; i<26; i++)
        {
            if (trie[now][i])//如果子节点有字母
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
int AC_automaton(char *s)
{
    int ans=0, now=0;//w是正在处理的点
    int lens=strlen(s);
    for(int i=0; i<lens; i++)
    {
        now=trie[now][s[i]-'a'];//递归处理
        for(int j=now; j && End[j]!=-1; j=Fail[j])
        {
            ans+=End[j];//累加
            End[j]=-1;//扫过的地方处理一下，防止重复
        }//j不断递归到Fail,直到已经被扫过或者指向根节点
    }
    return ans;
}
void debug()
{
    for(int i=0; i<=tot; i++)
    {
        printf("id = %3d,fail = %3d,end = %3d,trie = [", i, Fail[i], End[i]);
        for(int j=0; j<26; j++)
            printf("%2d", trie[i][j]);
        puts("]");
    }
}
char s1[1000010];
int main()
{
    int t;
    scanf("%d", &t);
    while(t--)
    {
        tot=-1;
        Trie_init();
        int n;
        scanf("%d", &n);
        char s[length+10];
        while(n--)
        {
            scanf("%s", s);
            Trie_insert(s);
        }
        GetFail();
        //debug();
        //printf("tot=%lld\n",tot);
        scanf("%s", s1);
        printf("%d\n", AC_automaton(s1));
    }
}
