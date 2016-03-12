/*
*************************************************
*	Example 6 - test framework		*
*************************************************
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N_ELEM 100000
#define N_TEST 20
#define _DEQUE_TYPE_ int
//when the _DEQUE_NAME_ is not defined, the default name is deque
#include "deque.h"

/*COLORS*/
#define GREEN	"\033[32;1m"
#define RED	"\033[31;1m"
#define YELLOW	"\033[33;1m"
#define BLUE	"\033[34;1m"
#define NORMAL	"\033[m"
/*-----*/

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

/*MODS----------------*/
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

/*ERRORS-------------*/
#define N_ERRORS 7

typedef enum{
	ERROR_NO,
	ERROR_WRONG_ELEMENT,
	ERROR_WRONG_LINK,
	ERROR_MUST_BE_NULL,
	ERROR_NULL_POINTER,
	ERROR_SIZE_WRONG,
	ERROR_ON_REMOVING
}ERROR;

const char* error_messages[N_ERRORS] =
{
	GREEN"Success, no errors!"NORMAL,
	RED"Wrong element in removed or inserted position!"NORMAL,
	RED"Wrong link, next or prev element not found!"NORMAL,
	RED"The deque begins and ends with a non-null-pointer, expected a null pointer in first or last position!"NORMAL,
	RED"The deque or a node is a null pointer!"NORMAL,
	RED"The size is wrong!"NORMAL,
	RED"Error on removing the element!"NORMAL,
};


void prints_err(ERROR e){
	printf("%s\n", error_messages[e]);
}

/*TEST VARIABLES*/
deque_t* D;
int* vector;

const char* tprefix = "----------\nTEST";
const char* tposfix = "\n";

void (*in_functions[N_MOD_IN])(deque_t*,int) = { deque_enqueue, deque_push };
boolean (*out_functions[N_MOD_RE])(deque_t*, int*) = { deque_dequeue, deque_pop, deque_pop_back };

/*verify's */

void print_progress(int n, boolean is_inserting){
	//show the progress
	//mod... 00%
	printf(BLUE "%s...%3.2lf%%\r"NORMAL, is_inserting?"inserting":"removing", //percentage
	(double)(n+1)/(double)N_ELEM*100); //mod
}

//canonical inserting errors
ERROR canonical_in(size_t n){
	if( D == NULL ) return ERROR_NULL_POINTER;
	if( D->size != n+1 ) return ERROR_SIZE_WRONG;
	if(n == 0 && ( !D->first || !D->last )) return ERROR_NULL_POINTER;
	if(D->first->prev || D->last->next) return ERROR_MUST_BE_NULL;
	return ERROR_NO;
}

ERROR in_front(int n){
	ERROR canonical = canonical_in(n);
	if(canonical) return canonical;

	//The element is there?
	if(D->first->data != vector[n])
		return ERROR_WRONG_ELEMENT;
	
	//The links are right?
	if(n == 0){
		if( D->first != D->last || D->first->prev != NULL || D->first->next != NULL)
			return ERROR_WRONG_LINK;
		else
			return ERROR_NO;
	}
	
	if( D->first->next->data != vector[n-1] )
		return ERROR_WRONG_LINK;
	
	return ERROR_NO;
}


ERROR in_back(int n){
	ERROR canonical = canonical_in(n);
	if(canonical) return canonical;

	//The element is there?
	if(D->last->data != vector[n])
		return ERROR_WRONG_ELEMENT;

	//The links are right?
	if(n==0){
		if( D->first != D->last || D->last->next != NULL || D->last->prev != NULL )
			return ERROR_WRONG_LINK;
		else
			return ERROR_NO;
	}

	if( D->last->prev->data != vector[n-1] )
		return ERROR_WRONG_LINK;
	
	return ERROR_NO;
}

//canonical removing errors
ERROR canonical_re(size_t n){
	if(D == NULL ) return ERROR_NULL_POINTER;
	if(D->size != (N_ELEM-(n+1)) ) return ERROR_SIZE_WRONG;
	if(n != (N_ELEM-1) && (!D->first || !D->last)) return ERROR_NULL_POINTER;
	if(n == (N_ELEM-1) && (D->first || D->last)) return ERROR_MUST_BE_NULL;
	if(n != (N_ELEM-1) && (D->first->prev || D->last->next)) return ERROR_MUST_BE_NULL;
	return ERROR_NO;
}

boolean removed_front_check(int n, int removed){
	return vector[n] == removed;
}

boolean removed_back_check(int n, int removed){
	return vector[N_ELEM-n-1] == removed;
}

boolean link_back_check(int n, int from_deque){
	return (from_deque == vector[N_ELEM-n-1]);
}

boolean link_front_check(int n, int from_deque){
	return (from_deque == vector[n]);
}

ERROR re_front(int n, int removed, MOD in){
	ERROR canonical = canonical_re(n);
	if(canonical) return canonical;
	
	//The element was removed right?
	boolean (*elem_check)(int, int); //pointer to the check function
	boolean (*link_check)(int, int);

	
	if( in == PUSH ){
		elem_check = removed_back_check;
		link_check = link_back_check;
	}
	else // in == ENQUEUE
	{
		elem_check = removed_front_check;
		link_check = link_front_check;
	}
	
	if(!elem_check(n, removed))
		return ERROR_WRONG_ELEMENT;

	//Are the links right?
	if(n < (N_ELEM-1) && link_check(n, D->first->data))
		return ERROR_WRONG_LINK;

	return ERROR_NO;
}

ERROR re_back(int n, int removed, MOD in){
	ERROR canonical = canonical_re(n);
	if(canonical) return canonical;

	//The element was removed right?
	boolean (*elem_check)(int, int); //pointer to the check function
	boolean (*link_check)(int, int); //pointer to the check function

	if( in == PUSH ){
		elem_check = removed_front_check;
		link_check = link_front_check;
	}
	else // in == ENQUEUE
	{
		elem_check = removed_back_check;
		link_check = link_back_check;
	}
	
	if(!elem_check(n, removed))
		return ERROR_WRONG_ELEMENT;

	//Are the links right?
	if(n < (N_ELEM-1) && link_check(n, D->last->data))
		return ERROR_WRONG_LINK;
	
	return ERROR_NO;
}

ERROR verify_in(int n, MOD mod){
	 return ( mod == PUSH )? in_front(n):in_back(n);	
}

ERROR verify_re(int n, int removed, MOD in, MOD re){
	switch(re){
		case DEQUEUE:
		case POP:
			return re_front(n, removed, in);
			break;
		case POP_BACK:
			return re_back(n, removed, in);
			break;
		default:
			return ERROR_NO;
	}
}

//TESTING with I inserting mod and D deleting mode
void test(MOD I, MOD R){
	vector = vec();
	
	int i;
	ERROR ERR = ERROR_NO;

	for(i=0; i<N_ELEM; i++){
		//show progress
		print_progress(i, true);

		//inserting...
		in_functions[I](D, vector[i]);

		//verify
		ERR = verify_in(i, I);
		
		if(ERR){
			prints_err(ERR);
			free(vector);
			return;
		}
	}
	printf("\ndone\n");
	//prints error message
	prints_err(ERR);
	
	for(i=0; i<N_ELEM; i++){
		//show progress
		print_progress(i, false);

		//removing...
		int removed; //stores the removed element 
		if(out_functions[R-N_MOD_IN](D, &removed))
			ERR = verify_re(i, removed, I, R);
		else
			ERR = ERROR_ON_REMOVING;

		if(ERR){
			prints_err(ERR);

			free(vector);
			return;
		}
	}
	printf("\ndone\n");
	//prints error message
	prints_err(ERR);

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
		printf(YELLOW"%s "NORMAL "[%d/%d (with %d elements)]" YELLOW "\n====\n"NORMAL,
			tprefix, i+1, N_TEST, N_ELEM);

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
