//Copy on Write


#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <stdlib.h>
#include <math.h>
#include <pthread.h>

#define ui unsigned int

ui a = 4;

void nothing(){return;}

int main(){
	pthread_t t;
	nothing();
	int *arr = malloc(1000*4);
	if(fork() == 0){
		printf("child %d\n",a);
		a = a+1;
		printf("child %d\n",a);
		//sqrt(a);
		exit(0);
	}
	nothing();
	wait(0);
	printf("%d\n", a);
	
	
}
