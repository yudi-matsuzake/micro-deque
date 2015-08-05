/*
*************************************************
*	Example 6 - test framework		*
*************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_ELEM 1000
#define N_TEST 10
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

	if(D->first!=NULL){
		deque_node_t* i;

		for(i=D->first; i!=NULL; i=i->next)
			p(i->data);
	}
	printf("}\n");
}

int* vec(){
	int* v = (int*)malloc(sizeof(int)*N_ELEM);
	
	int i;
	for(i=0; i<N_ELEM; i++)
		v[i] = rand();

	return v;
}

#define N_MOD 5
#define N_MOD_IN 2
#define N_MOD_RE 3
typedef enum{
	//insert
	ENQUEUE,
	PUSH,
	//remove
	DEQUEUE,
	POP,
	POP_BACK
}MOD;

/*TEST VARIABLES*/
deque_t* D;
int* vector;

const char* tprefix = "----------\nTEST";
const char* tposfix = "\n";

void (*in_functions[N_MOD_IN])(deque_t*,int) = { deque_enqueue, deque_push };
boolean (*out_functions[N_MOD_RE])(deque_t*, int*) = { deque_dequeue, deque_pop, deque_pop_back };

void verify(int i, int MOD){

}

//TESTING with I inserting mod and D deleting mode
void test(MOD I, MOD R){
	vector = vec();
	
	int i;

	for(i=0; i<N_ELEM; i++){
		//inserting...
		in_functions[I](D, vector[i]);

		//verify
	}
	
	for(i=0; i<N_ELEM; i++){
		//removing...
		int removed;
		out_functions[R-N_MOD_IN](D, &removed);
		
		//verify
	}

	free(vector);
}

//returns a random insert MOD type (enqueue or push)
int rmod_in(){
	return rand()%2;
}

//returns a random remove MOD type (dequeue, pop{,_back})
int rmod_out(){
	return (rand()%3)+DEQUEUE; 
}

char* mod_names[N_MOD] = {
"ENQUEUE", "PUSH",
"DEQUEUE", "POP", "POP_BACK"};

char* mod_name(MOD m){
	return mod_names[m];
}

int main(){
	srand(time(NULL));
	
	D = deque_create();

	int i;
	for(i=0; i<N_TEST; i++){
		//Random input and output mod's
		MOD I = rmod_in(), O = rmod_out();
		
		//Print prefix and the test number
		printf("%s [%d]\n====\n", tprefix, i);

		//Print input mod name
		printf("in:	%s\n", mod_name(I));

		//print output mode name
		printf("out:	%s\n", mod_name(O));

		//TEST
		test(I, O);

		//Print posfix
		printf("%s", tposfix);
	}

	deque_destroy(D, NULL);
	return 0;
}
