#include <stdio.h>
#include <stdlib.h>

#define _DEQUE_TYPE_ double
#include "deque.h"

void p(double i){
	printf("[%lf]\n", i);
}

double drand(){
	return ((double)rand()) / ((double) RAND_MAX);
}

#define N_ELEM 10
int main(){
	srand(time(NULL));
	deque_t* D = deque_create();
	
	int i;
	for( i=0; i<N_ELEM; i++)
		deque_enqueue(D, drand()*100 );
	
	deque_print(D, p);

	deque_destroy(D);
	return 0;
}
