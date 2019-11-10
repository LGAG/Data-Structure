#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#define Nul 0x00
char chinput[200], *p; 	/* 运算式存储字符串 */
					/* 运算式当前读取位置 */
struct t		/* 符号栈 */
{
	char dat[200];
	int top;
}prt;
struct d		/* 数字栈 */
{
	long int dat[200];
	int top;
}prd;

char PRI[9][9] =      /* 优先级表 */
{ {'>','>','<','<','<','<','<','>','>'},
	{'>','>','<','<','<','<','<','>','>'},
	{'>','>','>','>','<','<','<','>','>'},
	{'>','>','>','>','<','<','<','>','>'},
	{'>','>','>','>','>','<','<','>','>'},
	{'>','>','>','>','>','<','<','>','>'},
	{'<','<','<','<','<','<','<','=',Nul},
	{'>','>','>','>','>','>',Nul,'>','>'},
	{'<','<','<','<','<','<','<',Nul,'='}
};

void pushd(long int a)	/* 数字入栈 */
{
	prd.dat[prd.top++] = a;
}
void pusht(char a)		/* 符号入栈 */
{
	prt.dat[prt.top++] = a;
}
long int popd()			/* 数字出栈 */
{
	return prd.dat[--prd.top];
}
char popt()				/* 符号出栈 */
{
	return prt.dat[--prt.top];
}


long int numble()	// 数字整理。有小问题
{
	int flag=0;
	p--;
	if(*p == -1) flag = -1;
//		p--;
//		if(*p <='9' && *p >= '0') {
//			;
//		}
//		else{
//			flag =-1;
//			popt();
//		}
//		p++;
//	}
	//printf("%c , %c\n",prt.dat[prt.top],prt.dat[prt.top+1]);
	p++;
	long int b = 0;
	int count = 0;
	do
	{
		
		count++;
		b = b * 10 + *p - '0';   // 组成整数
		p++;
	} while (*p >= '0' && *p <= '9');
	p--;
	
	if(flag == -1) b = -b;
	printf("b = %d,count = %d\n",b,count);
	if (count == 0) return b / 10;
	else return b;
}

long operation(long int x, long int y, char a)
{
	switch (a)
	{
	case '+': return x + y;
	case '-': return x - y;
	case '*': return x * y;
	case '/': if (y)	return x / y;
			  else { printf("Divide 0.\n"); exit(0); }
	case '%': return (long int)fmod(x, y);
	case '^': if (y >= 0)	return (int)pow(x, y);
			  else     	return 0;
	default:  printf("Error No. 3\n");
		exit(1);
	}
}

int signswitch(char a)	   /* 符号转换。可优化 */
{
	printf("a:%c\n",a);
	switch (a)
	{
	case '+': return 0;   case '-': return 1;
	case '*': return 2;   case '/': return 3;
	case '%': return 4;   case '^': return 5;
	case '(': return 6;   case ')': return 7;
	case '#': return 8;
	default:  printf("Error No. 2\n");  exit(1);
	}
}
char refusal(char a, char b)   /* 判定优先级 */
{
	return PRI[signswitch(a)][signswitch(b)];
}


int main(void)
{
	int nnn;
	scanf("%d",&nnn);
	while(nnn--){
		int i, j, k, l, flag = 0;  // flag=0前一个符号不是)
		char b;
		prt.dat[0] = '#';		// 表达式起始符入栈
		prt.top = 1;
		prd.top = 0;
		printf("Enter Expression=");
		scanf("%s", chinput);  	// 接收运算式字符串
		printf("%s\n",chinput);
		printf("1\n");
		strcat(chinput, "#");	  	// 在运算式结尾加#号
		printf("2\n");
		int len = strlen(chinput);
		for(int i=0;i<len;i++){
			if(i==0){
				if(chinput[i] == '-'){
					if(chinput[i+1] <='9' && chinput[i+1] >='0'){
						//chinput[i+1] = -chinput[i+1];
						chinput[i]=-1;
					}
					//else if(chinput[i+1] != '(')printf("error\n");
				}
				else{
					if(chinput[i] == '-' && !(chinput[i-1] >= '0' && chinput[i-1] <= '9')){
						if(chinput[i+1] <='9' && chinput[i+1] >='0'){
							//chinput[i+1] = -chinput[i+1];
							chinput[i]=-1;
						}
						//else if(chinput[i+1] != '(')printf("error\n");
				}
			}
		}
		p = chinput;
		printf("%s\n",p);
		while (*p != '#' || prt.dat[prt.top - 1] != '#')
		{
			printf("begin loop.\n");
			if(*p == -1) continue;
			if (*p >= '0' && *p <= '9')
			{
				j = numble();  // 若遇数字生成完整整数入栈
				pushd(j);
				p++;
			}
			else       // 如果是符号与栈顶的符号比较并运算
			{
				if (flag == 1 && *p == '(')
				{
					printf("Error No.1:%s\n", p);  exit(0);
				}
				else if (*p == ')')  flag = 1;
				else 	         flag = 0;
				
					switch (refusal(prt.dat[prt.top - 1], *p))
					{
					case '<': pusht(*p++);  /* 高则入栈 */
						break;
					case '=': popt();         /* 脱括号 */
						p++;
						break;
					case '>': b = popt();  /* 低则进行栈顶计算 */
						k = popd();  /* 第二操作数出栈 */
						l = popd();  /* 第一操作数出栈 */
						k = operation(l, k, b);	/* 计算 */
						printf("k=%d\n",k);
						pushd(k);	  /* 计算结果入栈 */
						break;
					case Nul: printf("Error No. 4:%s\n", p);
						exit(1);
					}
	
			}
			printf("end loop.\n");
		}
			printf("%d\n", prd.dat[prd.top - 1]); //输出结果
	}
	
}

