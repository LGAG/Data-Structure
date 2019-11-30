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
	int flag = 0;
	p--;
	if (*p == -1) flag = -1;
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

	if (flag == -1) b = -b;
	//printf("b = %d,count = %d\n",b,count);
	if (count == 0) return b / 10;
	else return b;
}

long operation(long int x, long int y, char a)
{
	switch (a)
	{
	case '+': //printf("%d + %d = %d\n",x,y,x+y); 
		return x + y;
	case '-': //printf("%d - %d = %d\n",x,y,x-y); 
		return x - y;
	case '*': //printf("%d * %d = %d\n",x,y,x*y); 
		return x * y;
	case '/': if (y) {
		//printf("%d * %d = %d\n",x,y,x*y);
		return x / y;
		break;
	}
			  else {
		printf("Divide 0.\n");
		//exit(0); 
		return -20191110;

	}
	case '%': //printf("%d %% %d = %d\n",x,y,x%y); 
	if(y == 0){
		printf("error.\n");
		return -20191110;
	}
		return (long int)fmod(x, y);
	case '^': if (y >= 0) {
		//printf("%d ^ %d = %d\n",x,y,(int)pow(x, y));
		return (int)pow(x, y);
		break;
	}
			  else  {
			  	printf("error.\n");
			  	return -20191110;
			  }   	
	default:  printf("error.\n");
		//exit(1);
		return -20191110;
	}
}

int signswitch(char a)	   /* 符号转换。可优化 */
{
	//printf("a:%c\n",a);
	switch (a)
	{
	case '+': return 0;   case '-': return 1;
	case '*': return 2;   case '/': return 3;
	case '%': return 4;   case '^': return 5;
	case '(': return 6;   case ')': return 7;
	case '#': return 8;
	default:  printf("error.\n"); return -1;
	}
}
char refusal(char a, char b)   /* 判定优先级 */
{
	if (signswitch(a) == -1 || signswitch(b) == -1) return -1;
	return PRI[signswitch(a)][signswitch(b)];
}


int main(void)
{
	int nnn;
	scanf("%d", &nnn);
	while (nnn--) {

		for (int i = 0; i < 200; i++) {
			prt.dat[i] = 0;
			prd.dat[i] = 0;
			chinput[i] = 0;
		}


		int i, j, k, l, flag = 0;  // flag=0前一个符号不是)
		char b;
		prt.dat[0] = '#';		// 表达式起始符入栈
		prt.top = 1;
		prd.top = 0;
		//printf("Enter Expression=");
		scanf("%s", chinput);  	// 接收运算式字符串
		//printf("输入的字符串是:%s\n",chinput);

		strcat(chinput, "#");	  	// 在运算式结尾加#号
		int len = strlen(chinput);
		int ddd = 0;
		for(int i=0;i<len;i++){
			if(chinput[i] =='(' || chinput[i] == ')'){
				if(i-1>=0&&i+1<len){
					if((chinput[i-1] >= '0' && chinput[i-1] <= '9') && (chinput[i+1] >= '0' && chinput[i+1] <= '9')){
					//	printf("error.\n");
						ddd=1;
						break;
					}
				}
				if(chinput[i] == ')'){
					if(i-1>=0){
						if(chinput[i-1]=='+' || chinput[i-1]=='^' || chinput[i-1]=='*' || chinput[i-1]=='/' || chinput[i-1]=='-'){
						//	printf("error.\n");
						ddd=1;
						break;
						}
					}
				}
				if(chinput[i]=='('){
					if(i+1<len){
						if(chinput[i+1]=='+' || chinput[i+1]=='^' || chinput[i+1]=='*' || chinput[i+1]=='/'){
							//printf("error.\n");
						ddd=1;
						break;
						}
						else if(chinput[i+1]=='-'){
							if(i+2<len){
								if(chinput[i+2]>='0'&& chinput[i+2]<='9');
								else{
									ddd=1;
									break;
								}
							}
						}
					}
				}
			}
		}
		if (ddd == 1) {
			printf("error.\n");
			continue;
		}
		ddd=0;
		for (int i = 0; i < len - 1; i++) {
			if (chinput[i] >= '0' && chinput[i] <= '9');
			else {
				ddd = 1;
			}
		}
		if (ddd == 0) {
			printf("error.\n");
			continue;
		}
		for (int i = 0; i < len - 1; i++) {
			if (i == 0) {
				if (chinput[i] == '-') {
					if (chinput[i + 1] <= '9' && chinput[i + 1] >= '0') {
						chinput[i] = -1;
					}
				}
			}
			else {
				if (chinput[i] == '-' && !(chinput[i - 1] >= '0' && chinput[i - 1] <= '9')) {
					if (chinput[i + 1] <= '9' && chinput[i + 1] >= '0') {
						chinput[i] = -1;
					}
					//printf("chinput[%d]=%d\n",i,chinput[i+1]);
				}
			}

		}
		p = chinput;
		//printf("字符串p是:%s\n",p);
		int FF = 0;
		while (*p != '#' || prt.dat[prt.top - 1] != '#')
		{
			//printf("\nbegin loop.\n");
			if (*p++ == -1) {
				//printf("现在的*p: %d  %c\n",*p,*p);
				continue;
			}
			p--;
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
					printf("error.\n");
					//exit(0);
					FF = 1;
					break;
				}
				else if (*p == ')')  flag = 1;
				else 	         flag = 0;
				int FLAG = 0;
				switch (refusal(prt.dat[prt.top - 1], *p))
				{
				case -1:FLAG = 1;
					break;
				case '<': pusht(*p++);  /* 高则入栈 */
					break;
				case '=': popt();         /* 脱括号 */
					p++;
					break;
				case '>': b = popt();  /* 低则进行栈顶计算 */
					k = popd();  /* 第二操作数出栈 */
					l = popd();  /* 第一操作数出栈 */
					k = operation(l, k, b);	/* 计算 */
					if (k == -20191110) {
						FLAG = 1;
						break;
					}

					pushd(k);	  /* 计算结果入栈 */
					break;
				case Nul: printf("error.\n");
					//exit(1);
					FLAG = 1;

				}
				//printf("k=%d\n", k);
				if (FLAG == 1) {
					FF = 1;
					break;
				}
			}
			//printf("end loop.\n\n");
		}
		if (FF == 1) continue;
		printf("%d\n", prd.dat[prd.top - 1]); //输出结果
	}


}












