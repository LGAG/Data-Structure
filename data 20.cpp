#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char prefix[40000]={0};

typedef struct BiNode {
	int elem;
	BiNode *lkid, *rkid;
}BiNode, *BiTree;

int addBiTree(BiTree T, char *str) {
	if (strlen(str) == 0) {
		T->elem=1;
		if (T->lkid == NULL && T->rkid == NULL) {
			return 1;
		}
		else {
			return -1;
		}
	}
	else if (strlen(str) >= 1) {
		if (T->elem == 1) return -1;
		int len=strlen(str);
		char c=str[0];
		for (int i = 0; i < len; i++) {
			str[i] = str[i + 1];
		}
		if (c == '0') {
			if (T->lkid != NULL) {
				return addBiTree(T->lkid, str);
			}
			BiTree tmp;
			tmp = (BiTree)malloc(sizeof(BiNode));
			tmp->lkid = NULL;
			tmp->rkid = NULL;
			int index = addBiTree(tmp, str);
			T->lkid = tmp;
			return index;
		}
		else if (c == '1') {
			if (T->rkid != NULL) {
				return addBiTree(T->rkid, str);
			}
			BiTree tmp;
			tmp = (BiTree)malloc(sizeof(BiNode));
			tmp->lkid = NULL;
			tmp->rkid = NULL;
			int index = addBiTree(tmp, str);
			T->rkid = tmp;
			return index;
		}
	}
}

int main(void) {
	BiTree T;
	T = (BiTree)malloc(sizeof(BiNode));
	T->elem = 0;
	T->lkid = NULL;
	T->rkid = NULL;
	
	char tmp[40000]={0};
	char temp[40000]={0};
	int n = 0;
	int flag = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		
		scanf("%s", temp);
		if(flag == 1) continue;
		for(int g=0;g<=strlen(temp);g++){
			tmp[g]=temp[g];
		}	
		if (addBiTree(T, temp) == -1 && flag == 0) {
			flag = 1;
			for(int m=0;m<=strlen(tmp);m++){
				prefix[m]=tmp[m];
			}
		}
	}
	if (flag == 1) printf("%s\n", prefix);
	else if (flag == 0) printf("YES\n");
}





/*

注释里的代码是一位学长（也可能是个学姐...）的代码，总之比我的强，可以更快地处理更大的数据，我觉得我尽力了，因为我是的的确确使用链表来写的。 

#include<iostream>
#include<cstring>
using namespace std;

struct node
{
	unsigned int flag = 0, lson = 0, rson = 0;
}H_Tree[50000];
char str[100000];

int main()
{
	int num, StrLen;
	int TreeP, TreeNum = 2;//TreeP:point for H_Tree （指针） TreeNum:the nums of H_Tree node （拓展器）
	int Flag = 0;//0-YES,1-NO
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%s", str);
		if (Flag == 1) //如果Flag为1，说明第一次出现
			continue;
		StrLen = strlen(str);
		TreeP = 1;//从1开始，0作为空
		for (int j = 0; j < StrLen; j++)
		{
			if (H_Tree[TreeP].flag == 1)//说明别人是自己的前缀
			{
				Flag = 1;
				printf("%s\n", str);
				break;
			}

			if (j < StrLen - 1) //建树
			{
				//左子树
				if (str[j] == '0')
				{
					if (H_Tree[TreeP].lson == 0)//左节点为空
					{
						H_Tree[TreeP].lson = TreeNum;//拓展左节点
						TreeP = TreeNum++;//指针移动后拓展器自增
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].lson;
						continue;
					}
				}
				//右子树
				else
				{
					if (H_Tree[TreeP].rson == 0)
					{
						H_Tree[TreeP].rson = TreeNum;
						TreeP = TreeNum++;
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].rson;
						continue;
					}
				}
			}
			else
			{
				if (str[j] == '0')
				{
					if (H_Tree[TreeP].lson == 0) //为空
					{
						H_Tree[TreeP].lson = TreeNum;
						H_Tree[TreeNum].flag = 1;//标记最终建树完成
						TreeNum++;
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].lson;
						if (H_Tree[TreeP].lson == 0 && H_Tree[TreeP].rson == 0)//判定是否有重复输入的
							H_Tree[TreeP].flag = 1;
						else //是别人的前缀
						{
							Flag = 1;
							printf("%s\n", str);
							break;
						}
					}
				}
				else
				{
					if (H_Tree[TreeP].rson == 0)
					{
						H_Tree[TreeP].rson = TreeNum;
						H_Tree[TreeNum].flag = 1;
						TreeNum++;
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].rson;
						if (H_Tree[TreeP].lson == 0 && H_Tree[TreeP].rson == 0)
						{
							H_Tree[TreeP].flag = 1;
							break;
						}
						else
						{
							Flag = 1;
							printf("%s\n", str);
							break;
						}
					}
				}
			}
		}
	}
	if (!Flag)
		printf("YES\n");
	system("pause");
	return 0;
}

*/
