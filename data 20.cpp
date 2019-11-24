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

ע����Ĵ�����һλѧ����Ҳ�����Ǹ�ѧ��...���Ĵ��룬��֮���ҵ�ǿ�����Ը���ش����������ݣ��Ҿ����Ҿ����ˣ���Ϊ���ǵĵ�ȷȷʹ��������д�ġ� 

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
	int TreeP, TreeNum = 2;//TreeP:point for H_Tree ��ָ�룩 TreeNum:the nums of H_Tree node ����չ����
	int Flag = 0;//0-YES,1-NO
	scanf("%d", &num);
	for (int i = 0; i < num; i++)
	{
		scanf("%s", str);
		if (Flag == 1) //���FlagΪ1��˵����һ�γ���
			continue;
		StrLen = strlen(str);
		TreeP = 1;//��1��ʼ��0��Ϊ��
		for (int j = 0; j < StrLen; j++)
		{
			if (H_Tree[TreeP].flag == 1)//˵���������Լ���ǰ׺
			{
				Flag = 1;
				printf("%s\n", str);
				break;
			}

			if (j < StrLen - 1) //����
			{
				//������
				if (str[j] == '0')
				{
					if (H_Tree[TreeP].lson == 0)//��ڵ�Ϊ��
					{
						H_Tree[TreeP].lson = TreeNum;//��չ��ڵ�
						TreeP = TreeNum++;//ָ���ƶ�����չ������
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].lson;
						continue;
					}
				}
				//������
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
					if (H_Tree[TreeP].lson == 0) //Ϊ��
					{
						H_Tree[TreeP].lson = TreeNum;
						H_Tree[TreeNum].flag = 1;//������ս������
						TreeNum++;
						continue;
					}
					else
					{
						TreeP = H_Tree[TreeP].lson;
						if (H_Tree[TreeP].lson == 0 && H_Tree[TreeP].rson == 0)//�ж��Ƿ����ظ������
							H_Tree[TreeP].flag = 1;
						else //�Ǳ��˵�ǰ׺
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
