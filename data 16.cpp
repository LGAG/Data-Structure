#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct BitNode {
	char c;
	BitNode *Lkid, *Rkid;
	int l,r; // -1 -> NULL
}BitNode, *BiTree;

char result1[23]={0};
char result2[23]={0};

void initializeBiTree(BiTree root) {
	root->c = 0;
	root->Lkid = NULL;
	root->Rkid = NULL;
}

int pretraverse1(BiTree T){
	if(T != NULL){
		int len1 = strlen(result1);
		result1[len1]=T->c;
		result1[len1+1]='\0';
		pretraverse1(T->Lkid);
		pretraverse1(T->Rkid);
		return 1;
	}
	else return -1;
}

int pretraverse2(BiTree T){
	if(T != NULL){
		int len2 = strlen(result2);
		result2[len2]=T->c;
		result2[len2+1]='\0';
		pretraverse2(T->Rkid);
		pretraverse2(T->Lkid);
		return 1;
	}
	else return -1;
}

int main(void) {
	int n1, n2,start1,start2;
	BiTree root1[26], root2[26];  //这两个数组为节点数组 
	
	//第一棵树 
	scanf("%d",&n1);
	getchar();
	for(int i=0;i<n1;i++){
		root1[i] = (BitNode*)malloc(sizeof(BitNode));
		char a,tmp1,tmp2,tmp3;
		int b, c;
		int index1=scanf("%c", &a);
		root1[i]->c = a;
		if(a=='A')start1=i;
		int index2=scanf("%d", &b);
		if(index2 == 0){
			b='-';
			root1[i]->l=-1;
			root1[i]->Lkid = NULL;
		}
		else{
			root1[i]->l=b;
		}
		int index3=scanf("%d", &c);
		if(index3 == 0){
			c='-';
			root1[i]->r=-1;
			root1[i]->Rkid = NULL;
		}
		else{
			root1[i]->r=c;
		}
		tmp3=getchar();
	}
	for(int i=0;i<n1;i++){
		if(i==start1) continue;
		for(int j=0;j<n1;j++){
			if(root1[j]->l == i){
				root1[j]->Lkid = root1[i];
			}
			else if(root1[j]->r == i){
				root1[j]->Rkid = root1[i];
			}
		}
	}
	
	
	// 第二棵树 ， 完全复制的第一棵树 ， 不想写函数了 
	scanf("%d",&n2);
	getchar();
	for(int i=0;i<n2;i++){
		root2[i] = (BitNode*)malloc(sizeof(BitNode));
		char a,tmp1,tmp2,tmp3;
		int b, c;
		int index1=scanf("%c", &a);
		root2[i]->c = a;
		if(a=='A')start2=i;
		int index2=scanf("%d", &b);
		if(index2 == 0){
			b='-';
			root2[i]->l=-1;
			root2[i]->Lkid = NULL;
		}
		else{
			root2[i]->l=b;
		}
		int index3=scanf("%d", &c);
		if(index3 == 0){
			c='-';
			root2[i]->r=-1;
			root2[i]->Rkid = NULL;
		}
		else{
			root2[i]->r=c;
		}
		tmp3=getchar();
	}
	for(int i=0;i<n2;i++){
		if(i==start2) continue;
		for(int j=0;j<n2;j++){
			if(root2[j]->l == i){
				root2[j]->Lkid = root2[i];
			}
			else if(root2[j]->r == i){
				root2[j]->Rkid = root2[i];
			}
		}
	}
	if(root1[start1]==NULL || root2[start2]==NULL){
		printf("Yes.\n");
		return 1;
	}
	//pretraverse1(root1[start1]);
	//pretraverse2(root2[start2]);
	
	
	// 从这里我开始遍历判断每个节点是否左右子都相同 
	int flag=0;
	for(int i=0;i<n1;i++){
		for(int j=0;j<n2;j++){
			if(root2[j]->c == root1[i]->c){
				int i1=0,i2=0,i3=0,i4=0,I=0,J=0;
				if(root1[i]->Lkid == NULL) i1=1;
				if(root1[i]->Rkid == NULL) i2=1;
				if(root2[j]->Lkid == NULL) i3=1;
				if(root2[j]->Rkid == NULL) i4=1;
				I = i1 + i2;
				J = i3 + i4;
				if(I != J){
					flag = 1;
					break;
				}
				else if(I == 1 && J == 1){
					if(root1[i]->Lkid != NULL){
						if(root2[j]->Lkid != NULL){
							if(root1[i]->Lkid->c != root2[j]->Lkid->c){
								flag = 1;
								break;
							}
						}
						else if(root2[j]->Rkid != NULL){
							if(root1[i]->Lkid->c != root2[j]->Rkid->c){
								flag = 1;
								break;
							}
						}
					}
					else if(root1[i]->Rkid != NULL){
						if(root2[j]->Lkid != NULL){
							if(root1[i]->Rkid->c != root2[j]->Lkid->c){
								flag = 1;
								break;
							}
						}
						else if(root2[j]->Rkid != NULL){
							if(root1[i]->Rkid->c != root2[j]->Rkid->c){
								flag = 1;
								break;
							}
						}
					}
				}
				else if(I == 0 && J == 0){
					if(root1[i]->Lkid->c == root2[j]->Lkid->c && root1[i]->Rkid->c == root2[j]->Rkid->c);
					else if(root1[i]->Rkid->c == root2[j]->Lkid->c && root1[i]->Lkid->c == root2[j]->Rkid->c);
					else{
						flag = 1;
						break;
					}
				}
			}
		}
	}
	if(flag==1) printf("No.\n");
	else printf("Yes.\n");
}
