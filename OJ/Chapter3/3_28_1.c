#include <stdio.h>
int main(){
	int str[100];
	int n;
  	scanf("%d", &n);
    int i;
  	for (i = 0; i < n-1; i++)
      	scanf("%d,", &str[i]);
  	scanf("%d", &str[i]);
  	for (i = 0; i < n-1; i++)
      	printf("%d,", str[i]);
  	printf("%d", str[i]);
  	return 0;
}