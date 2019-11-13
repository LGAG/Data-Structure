#include <stdio.h> 
#include <string.h>
#include <stdlib.h>

typedef struct stackop{
	char a[2900];
	int top;
}stackop;

int initial(stackop *sta){
	for(int i =0 ;i<2000;i++) sta->a[i] = 0;
	sta->top = 1;
	return 0;
}

int pops(stackop *sta){
	if(sta->top == 0){
		return 0;
	}
	else{
		sta->top--;
		return 1;
	}
}

int pushs(stackop *sta , char x){
	if(sta->top == 1999){
		return 0;
	}
	else{
		sta->a[sta->top] = x;
		sta->top++;
		return 1;
	}
}

int comp(char a, char b){
	if(a == '#') a = 0;
	else if(a == '(') a = 1;
	else if(a == '^') a = 6;
	else if(a == '*' || a == '/' || a == '%') a = 5;
	else if(a == '+' || a == '-') a = 3;
	else if(a == ')') a = 8;
	
	if(b == '#') b = 0;
	else if(b == '(') b = 8;
	else if(b == '^') b = 7;
	else if(b == '*' || b == '/' || b == '%') b = 4;
	else if(b == '+' || b == '-') b = 2;
	else if(b == ')') b = 1;
	
	return a-b;
}

int main(void){
	int n=0;
	scanf("%d",&n);
	getchar();
	while(n--){
		char tmp[2000]={0};
		int temp=0;
		scanf("%s",tmp);
		for(int i=0;i<strlen(tmp);i++){
			if(i == 0 && tmp[0] == '-') tmp[0]=-1;
			if(tmp[i]=='-' && tmp[i-1] == '(') tmp[i] = -1;
		}
		char str[2000] = {0};
		int len = 0;
		stackop *sta = (stackop*)malloc(sizeof(stackop));
		initial(sta);
		pushs(sta, '#');
		char c;
		int count = 0;
		while(1){
			c=tmp[temp];
			temp++;
			if(c == '#'){
				while(1){
					if(sta->top == 0) break;
					if(sta->a[sta->top - 1] != '#'){
						str[len] = sta->a[sta->top - 1];
						len++;
						str[len]='\0';
					}
					sta->top--;
				}
				printf("%s\n",str);
				break;
			}
			else if(c == -1){
				printf("-");
				continue;
			}
			else if(c >= '0' && c <= '9'){
				str[len]=c;
				len++;
				continue;
			}
			else if(c >= 'a' && c <= 'z'){
				str[len]=c;
				len++;
				continue;
			}
			else if(c >= 'A' && c <= 'Z'){
				str[len]=c;
				len++;
				continue;
			}
			else if(c == ' '){
				continue;
			}
			else{
				g: ;
				if(comp(sta->a[sta->top - 1] , c) > 0){
					str[len] = sta->a[sta->top - 1];
					len++;
					sta->top--;
					goto g;
				}
				else if(comp(sta->a[sta->top - 1] , c) < 0){
					pushs(sta,c);
				}
				else{
					sta->top--;
				}
				continue;
			}
		}
	}
}
