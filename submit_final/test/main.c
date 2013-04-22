#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int n = argc == 2 ? atoi(argv[1]) : 40;

	printf("%d\n",f(n));
	return 0;
}
