#include <stdio.h>
#include <stdlib.h>


#define _DEQUE_TYPE_ int
#define _DEQUE_NAME_ dequeint
#include "deque.h"

//function to print the element
//return void, and one parameter: one element of _DEQUE_TYPE_
void p(int i){
	printf("[%d]\n", i);
}

int main(){
	//the structure `_DEQUE_NAME_`_t
	dequeint_t* D = dequeint_create();

	int i;

	for(i=0; i<5; i++)
		dequeint_enqueue(D, i);
	
	dequeint_print(D, p);
	
	dequeint_destroy(D, NULL);
	return 0;
}
