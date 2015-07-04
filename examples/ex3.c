#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define _DEQUE_TYPE_ double
#define _DEQUE_NAME_ double_deque
#include "deque.h"

#define _DEQUE_TYPE_ int
#define _DEQUE_NAME_ int_deque
#include "deque.h"

void p(double i){
	printf("[%lf]\n", i);
}

void p2(int i){
	printf("[%d]\n", i);
}

double drand(){
	return ((double)rand()) / ((double) RAND_MAX);
}

#define N_ELEM 10
int main(){
	srand(time(NULL));
	double_deque_t* D = double_deque_create();
	int_deque_t* DI = int_deque_create();
	
	int i;
	for( i=0; i<N_ELEM; i++){
		double_deque_enqueue(D, drand()*100 );
		int_deque_enqueue(DI, rand()%100);
	}
	printf("DOUBLE DEQUE: \n");
	double_deque_print(D, p);
	
	printf("----------------\n");
	printf("INT DEQUE: \n");
	int_deque_print(DI, p2);

	double_deque_destroy(D, NULL);
	int_deque_destroy(DI, NULL);
	return 0;
}
