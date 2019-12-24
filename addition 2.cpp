#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#pragma warning(disable:4996)
int nodeNum, edgeNum;
int topo[55], path[100];
struct link
{
    int dir;
    int val;
};
struct
{
    char name[5];
    int inNum = 0; 
    int outNum = 0; 
    int Etv, Ltv;
    link linkTo[300];
    int linkNum = 0;
}node[50];

int cmp1(const void *p1, const void *p2)
{
    struct link *c = (link *)p1;
    struct link *d = (link *)p2;
    return (c->dir) > (d->dir);
}
int cmp2(const void *p1, const void *p2)
{
    struct link *c = (link *)p1;
    struct link *d = (link *)p2;
    return (c->dir) < (d->dir);
}

void CreateGraph()
{
    char str[500] = { '\0' };
    scanf("%s", str);
    int len = strlen(str), q = 0, k = 0;
    for (int i = 0; i < len; i++)
    {
        if (str[i] != ',')
            node[k].name[q++] = str[i];
        else
        {
            node[k].name[q] = '\0';
            k++;
            q = 0;
        }
    }

    int p = 0, k_flag = 0;
    int ch_data[5], cd_p = 0;
    char chs[10] = { '\0' }, ch;
    getchar();
    while ((ch = getchar()))
    {
        if (ch == '\n' || ch == -1)
            break;
        if (ch == '<')
        {
            k_flag = 1;
            continue;
        }
        if (ch == ','&&k_flag == 1)
        {
            ch_data[cd_p] = atoi(chs);
            memset(chs, '\0', sizeof(chs));
            p = 0;
            cd_p++;
            continue;
        }
        if (ch != '<'&&ch != ','&&k_flag == 1 && ch != '>')
        {
            chs[p++] = ch;
            continue;
        }
        if (ch == '>'&&k_flag == 1)
        {
            ch_data[cd_p] = atoi(chs);
            int u = ch_data[0];
            node[u].linkTo[node[u].linkNum].dir = ch_data[1];
            node[u].linkTo[node[u].linkNum].val = ch_data[2];
            node[u].outNum++;
            node[ch_data[1]].inNum++;
            node[u].linkNum++;
            k_flag = 0;
            p = 0;
            cd_p = 0;
            memset(chs, '\0', sizeof(chs));
            continue;
        }
    }
    for (int i = 0; i < nodeNum; i++)
        qsort(node[i].linkTo, node[i].linkNum + 1, sizeof(node[i].linkTo[0]), cmp1);
}

int TopoLogicalSort_DFS()
{
    int *Stack, u, v, top = 0, count = 0;
    Stack = (int*)malloc(sizeof(int) * nodeNum);
    for (int i = 0; i < nodeNum; i++)
    {
        node[i].Etv = 0; 
        if (node[i].inNum == 0)
            Stack[top++] = i;
    }
    while (top > 0)
    {
        u = Stack[--top];
        topo[count++] = u;

        for (int i = 0; i <= node[u].linkNum; i++)
        {
            int v = node[u].linkTo[i].dir;
            if (node[v].Etv < node[u].Etv + node[u].linkTo[i].val)
                node[v].Etv = node[u].Etv + node[u].linkTo[i].val;
            if (--node[v].inNum == 0)
                Stack[top++] = v;
        }
        qsort(Stack, top, sizeof(Stack[0]), cmp2);
    }
    free(Stack);
    return (count == nodeNum);
}

void PrintPath(int top, int end)
{
    int u = path[top - 1];
    if (u == end)
    {
        printf("%s", node[path[0]].name); 
        for (int i = 1; i < top; i++)
            printf("-%s", node[path[i]].name);
        printf("\n");
        return;
    }
    for (int i = 0; i <= node[u].linkNum; i++)
    {
        int v = node[u].linkTo[i].dir;
        if (node[u].Etv + node[u].linkTo[i].val < node[v].Etv)
            continue;
        if (node[v].Etv == node[v].Ltv)
        {
            path[top++] = node[u].linkTo[i].dir;
            PrintPath(top, end);
            top--;
        }
    }
}

void CriticalPath()
{
    if (!TopoLogicalSort_DFS())
    {
        printf("NO TOPOLOGICAL PATH\n");
        return;
    }
    for (int i = 0; i < nodeNum; i++)
    {
        node[i].Ltv = node[nodeNum - 1].Etv;
        if (i)
            printf("-");
        printf("%s", node[topo[i]].name);
    }
    printf("\n");
    for (int i = nodeNum - 2; i >= 0; i--)
    {
        int u = topo[i];
        for (int j = 0; j <= node[u].linkNum; j++)
        {
            int v = node[u].linkTo[j].dir;
            if (node[u].Ltv > node[v].Ltv - node[u].linkTo[j].val) 
                node[u].Ltv = node[v].Ltv - node[u].linkTo[j].val;
        }
    }
    path[0] = topo[0];
    PrintPath(1, topo[nodeNum - 1]);
}

int main()
{
    scanf("%d,%d", &nodeNum, &edgeNum);
    CreateGraph();
    CriticalPath();
    system("pause");
    return 0;
}
