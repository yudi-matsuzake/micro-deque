#include <stdio.h>
#include <stdlib.h>


#define _DEQUE_TYPE_ int
//when the _DEQUE_NAME_ is not defined, the default name is deque
#include "deque.h"

//function to print the element
//return void, and one parameter: one element of _DEQUE_TYPE_
void p(int i){
	printf("[%d]\n", i);
}

int main(){
	//the structure `_DEQUE_NAME_`_t
	deque_t* D = deque_create();

	int i;

	for(i=0; i<5; i++)
		deque_enqueue(D, i);
	
	deque_print(D, p);
	
	deque_destroy(D, NULL);
	return 0;
}
