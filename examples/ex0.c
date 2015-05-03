#include <stdio.h>
#include <stdlib.h>


//when the _DEQUE_TYPE_ is not defined, the default type is void*
//when the _DEQUE_NAME_ is not defined, the default name is deque
#include "deque.h"

//function to print the element
//return void, and one parameter: one element of _DEQUE_TYPE_
void p(void* i){
	printf("[%d]\n", *((int*)i));
}

int main(){
	//the structure `_DEQUE_NAME_`_t
	deque_t* D = deque_create();

	int v[5] = {1, 2, 3, 4, 5};
	int i;

	for(i=0; i<5; i++)
		deque_enqueue(D, &v[i]);
	
	deque_print(D, p);
	
	deque_destroy(D, NULL);
	return 0;
}
