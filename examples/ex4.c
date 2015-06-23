/*
*************************************************
*	Example 4 - test all operations		*
*************************************************
*/

#include <stdio.h>
#include <stdlib.h>


#define _DEQUE_TYPE_ int
//when the _DEQUE_NAME_ is not defined, the default name is deque
#include "deque.h"

//function to print the element
//return void, and one parameter: one element of _DEQUE_TYPE_
void p(int i){
	printf("[%d] ", i);
}

void print_deque(deque_t* D){
	printf("D(%lu) = {", D->size);
	deque_print(D, p);
	printf("}\n");
}

int main(){
	//the structure `_DEQUE_NAME_`_t
	deque_t* D = deque_create();

	int i;
	print_deque(D);

	for(i=0; i<5; i++){
		deque_enqueue(D, i);
		printf("Enqueue: %d!\n", i);
		print_deque(D);
	}
	
	
	int e;
	while(deque_dequeue(D, &e)){
		printf("Dequeue: %d!\n", e);
		print_deque(D);
	}
	
		
	deque_destroy(D, NULL);
	return 0;
}
