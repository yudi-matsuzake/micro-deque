# micro-deque

Micro generic deque lib in c

# examples

## examples/ex0.c

```c
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
```

## examples/ex1.c

```c
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

```

## examples/ex2.c

```c
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

```

## examples/ex3.c

```c
#include <stdio.h>
#include <stdlib.h>

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

```
