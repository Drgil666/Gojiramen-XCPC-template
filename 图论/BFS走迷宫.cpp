#include <iostream>//C++输入输出头文件
#include <queue>//队列头文件
using namespace std;
typedef struct point
{
    int x;
    int y;//x,y为坐标路径
    point *previous;//指向前一个
    int step;//移动的步数
} point;

point dir[4] =
        {
                {0,1,NULL,0},
                {1,0,NULL,0},
                {0,-1,NULL,0},
                {-1,0,NULL,0},
        };
//代表上下左右四个移动


int map[8][8] =
        {
                { 1, 0, 1, 1, 1, 1, 1, 1 },
                { 1, 0, 0, 0, 0, 0, 0, 1 },
                { 1, 0, 1, 1, 1, 1, 0, 1 },
                { 1, 0, 0, 0, 0, 1, 0, 0 },
                { 1, 1, 1, 1, 0, 0, 1, 1 },
                { 1, 1, 1, 1, 1, 0, 1, 1 },
                { 1, 1, 0, 0, 0, 0, 1, 1 },
                { 1, 1, 0, 1, 1, 1, 1, 1 },
        };//只有0位置可以走，本例为“到数组边缘就是走出迷宫”。
//输出最短的路径和最短步数

void PrintAllPath(point *p)//打印路径
{
    int shortest = p->step;//p所需步数

    cout << "可行短路径为：";
    while (p->previous != NULL)
    {
        cout << "(" << p->x << "," << p->y << ")";
        p = p->previous;
    }//采用回溯的方法，将求出的路径倒序求出
    cout << "(" << p->x << "," << p->y << ")" << endl;//将头（起点）输出，因为第一个指向的为空。
    cout << "路径长度为：" << shortest << endl;
}

void BFS(point startPoint)
{
    queue<point> q;//建立point类型的队列q
    q.push(startPoint);//队尾压入起点
    point cur;

    while (!q.empty())//表不为空时执行，空时表示所有可能都找遍
    {
        cur=q.front();//将队首元素的数据给cur（上一步执行完成的nxt）
        q.pop();//移出队首元素
        map[cur.x][cur.y] = 1;//1表示走过的路径
        for (int i = 0; i < 4; i++)//四次表示“上下左右”四个方位
        {
            point nxt{ cur.x + dir[i].x, cur.y + dir[i].y, NULL, 0 };//nxt代表移动后的坐标
            if (nxt.x >= 0 && nxt.x < 8 && nxt.y >= 0 && nxt.y < 8 && map[nxt.x][nxt.y] == 0)
                //边界测定与“该路是否被走过”
            {
                point *tmp = new point;//new的功能是给指针tmp开动态空间
                memcpy(tmp, &cur, sizeof(point));//memcpy的功能是拷贝，将cur的内容给tmp
                nxt.previous = tmp;//nxt是路径的下一步，将其指向cur
                nxt.step = cur.step + 1;//路径数+1
                map[nxt.x][nxt.y] = 1;//1表示走过的路径
                if (nxt.x == 0 || nxt.x == 7 || nxt.y == 0 || nxt.y == 7)
                {
                    PrintAllPath(&nxt);
                    //这句话注释则输出所有路径，不注释是最短路径，因为BFS是一层一层搜索的，先搜索的必定最短
                    //return;
                }
                //逃脱条件判断 ，成功则输出路径，本例中为“边界逃脱”
                q.push(nxt);//队尾加入已经移动过的nxt，下一次被执行
            }
        }
    }
}//与DFS的区别在于：DFS是顺着一条路一直找下去的，不行就回来,需要递归。
//而BFS则是一开始就向各个方向走，逐渐向四周扩大走过路径，不需要递归（所以路径不需要变回0）。
//对于迷宫问题，BFS这种地毯式搜索更好些。

int main()
{
    point startPoint{ 0, 1, NULL, 0 };//该例子中起点设置为0,1
    BFS(startPoint);
    return 0;
}//
// Created by 25741 on 2020/6/2.
//

