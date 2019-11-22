#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <queue>

using namespace std;

typedef struct BiNode {
	char elem;
	BiNode *Lkid, *Rkid;
}BiNode, *BiTree;

int recover(BiTree T, char *s1, char *s2, int n) {
	int len1, len2, len;
	char root;  //当前树的根的字符 
	len = strlen(s1);
	if (len == 1) {
		T->elem = s1[0];
		T->Lkid = NULL;
		T->Rkid = NULL;
		return 1;
	}
	else if (len == 0) {
		T = NULL;
		return -1;
	}
	T->elem = s2[len - 1];
	root = s2[len - 1];
	for (int i = 0; i < len; i++) {
		if (s1[i] == root) {
			len1 = i; 
			break;
		}
	} //在中序表达式中找到这棵树的根字符 
	if (len1 == 0) {
		T->Lkid = NULL;
	}
	else {
		char tmp1[1000] = { 0 }, tmp2[1000] = { 0 };  //这个1000是随便设的，猜想字符串不会超过这个长度 
		for (int i = 0; i < len1; i++) {
			tmp1[i] = s1[i];
			tmp2[i] = s2[i];
		} //这里是从中序表达式和后序表达式中提取出子树的中序表达式和后序表达式 
		tmp1[len1] = '\0';
		tmp2[len1] = '\0';
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp->elem = 'A';
		tmp->Lkid = NULL;
		tmp->Rkid = NULL;  //我在想这个初始化应该是不必要的 
		recover(tmp, tmp1, tmp2, -1);
		T->Lkid = tmp;
	}
	if (len1 == len - 1) {
		T->Rkid = NULL;
	}
	else {
		char tmp1[1000] = { 0 }, tmp2[1000] = { 0 };
		for (int i = len1 + 1; i < len; i++) {
			tmp1[i - len1 - 1] = s1[i];
			tmp2[i - len1 - 1] = s2[i - 1];
		}
		tmp1[len - len1 - 1] = '\0';
		tmp2[len - len1 - 1] = '\0';
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp->elem = 'A';
		tmp->Lkid = NULL;
		tmp->Rkid = NULL;
		recover(tmp, tmp1, tmp2, -1);
		T->Rkid = tmp;
	}   //右子树直接复制的左子树代码 
	return 2;
}



int main(void) {
	char str1[1000] = { 0 }, str2[1000] = { 0 };  // str1是中序 ， str2是后序。 
	int count = 0;
	while (1) {
		char tmp;
		scanf("%c", &tmp);
		if (tmp == '\n') {
			break;
		}
		str1[count] = tmp;
		count++;
	}
	str1[count] = '\0';
	count = 0;
	while (1) {
		char tmp;
		scanf("%c", &tmp);
		if (tmp == '\n') {
			break;
		}
		str2[count] = tmp;
		count++;
	}
	str2[count] = '\0';  //因为之前在VS中貌似scanf_s("%s",str)这样读字符串会报错，所以我就很傻傻的这么读取了 
	queue <BiTree> que;  //利用这个队列顺序输出二叉树 
	BiTree T, t;
	T = (BiNode*)malloc(sizeof(BiNode));
	T->Lkid = NULL;
	T->Rkid = NULL;
	recover(T, str1, str2, count);
	que.push(T);
	while (1) {
		BiTree tmp;
		tmp = (BiNode*)malloc(sizeof(BiNode));
		tmp = que.front();
		printf("%c", tmp->elem);
		que.pop();
		if (tmp->Lkid != NULL) {
			que.push(tmp->Lkid);
		}
		if (tmp->Rkid != NULL) {
			que.push(tmp->Rkid);
		}
		if (que.empty()) {
			printf("\n");
			break;
		}
	}
}
