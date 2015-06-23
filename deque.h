/*
*
* Micro-deque struct
* ----------------
* Generic compilation-time (or not) method for a deque struct generation
*
*/


/*
_______
|MACROS
------- */

/* _DEQUE_TYPE_ */

//holds the name, i.e., the name of the struct that you'll use. This must to be unique
#ifndef _DEQUE_NAME_
	#define _DEQUE_NAME_ deque
#endif

//holds the type of the struct
#ifndef _DEQUE_TYPE_
	#define _DEQUE_TYPE_ void*
#endif


#define XPAND(X) X

/*This should avoid the reinclude with the same _DEQUE_NAME_ */
#if XPAND(_DEQUE_NAME_) == 0

/*-----------------------------------------------------------------------------------------
___________________________________________
|MACROS OF THE {FUNCTIONS,STRUCTURES} NAME
-------------------------------------------
*/

/* DEQUE */

/*auxx*/
//deque
#define DDDEQUE_FUNC(X, Y) X ## _ ## Y
#define DDEQUE_FUNC(X, Y) DDDEQUE_FUNC(X, Y)
#define DEQUE_FUNC(X) DDEQUE_FUNC(_DEQUE_NAME_, X)
//deque node
#define DDDEQUE_NODE_FUNC(X, Y) X ## _node_ ## Y
#define DDEQUE_NODE_FUNC(X, Y) DDDEQUE_NODE_FUNC(X, Y)
#define DEQUE_NODE_FUNC(X) DDEQUE_NODE_FUNC(_DEQUE_NAME_, X)


/*struct*/
#define DEQUE_STRUCT_NODE DDEQUE_FUNC(_DEQUE_NAME_, node_t)
#define DEQUE_STRUCT DDEQUE_FUNC(_DEQUE_NAME_, t)

/*functions*/

//create
#define DEQUE_CREATE DEQUE_FUNC(create)

//destroy
#define DEQUE_DESTROY DEQUE_FUNC(destroy)

//size
#define DEQUE_SIZE DEQUE_FUNC(size)

//is_empty
#define DEQUE_IS_EMPTY DEQUE_FUNC(is_empty)

//enqueue
#define DEQUE_ENQUEUE DEQUE_FUNC(enqueue)

//dequeue
#define DEQUE_DEQUEUE DEQUE_FUNC(dequeue)

//pop
#define DEQUE_POP DEQUE_FUNC(pop)

//push
#define DEQUE_PUSH DEQUE_FUNC(push)

//print
#define DEQUE_PRINT DEQUE_FUNC(print)

/* DEQUE NODE */
#define DEQUE_NODE_CREATE DEQUE_NODE_FUNC(create)

/*-----------------------------------------------------------------------------------------
_________
|INCLUDES
----------
*/
#include <stdlib.h>
#include "boolean.h"
/*-----------------------------------------------------------------------------------------*/

#define dtype _DEQUE_TYPE_ //dtype it's the type of all this full generic crazyness

/*-----------------------------------------------------------------------------------------
__________
|STRUCTURE
----------
*/

typedef struct DEQUE_STRUCT_NODE {
	struct DEQUE_STRUCT_NODE * next;
	struct DEQUE_STRUCT_NODE * prev;
	
	dtype data;
} DEQUE_STRUCT_NODE ;

typedef struct DEQUE_STRUCT {
	struct DEQUE_STRUCT_NODE * first;
	struct DEQUE_STRUCT_NODE * last;
	
	unsigned long int size;
} DEQUE_STRUCT ;
/*-----------------------------------------------------------------------------------------
____________
|DEFINITIONS
------------
*/

boolean DEQUE_IS_EMPTY ( DEQUE_STRUCT * D);

/*-----------------------------------------------------------------------------------------
______________________________
| DEQUE_STRUCT_NODE FUNCTIONS |
------------------------------
*/

/* DEQUE_NODE_CREATE */
DEQUE_STRUCT_NODE* DEQUE_NODE_CREATE (dtype data){
	DEQUE_STRUCT_NODE* newnode = (DEQUE_STRUCT_NODE*) malloc(sizeof(DEQUE_STRUCT_NODE));
	newnode->prev = newnode->next = NULL;
	newnode->data = data;
	return newnode;
}

/*-------------------------------------------------------------------------------------------
_________________________
| DEQUE_STRUCT FUNCTIONS |
--------------------------
*/


/*CONSTRUCTOR AND DESTRUCTOR*/
//DEQUE_CREATE
DEQUE_STRUCT* DEQUE_CREATE(){
	DEQUE_STRUCT* D = NULL;
	D = (DEQUE_STRUCT*) malloc(sizeof(DEQUE_STRUCT));

	if(D) D->size = (unsigned long int) (D->first = D->last = NULL);
	
	return D;
}

//DEQUE_DESTROY
void DEQUE_DESTROY( DEQUE_STRUCT* D, void (free_elem)( dtype) ){
	DEQUE_STRUCT_NODE * i = D->first;

	while ( i != NULL ){
		DEQUE_STRUCT_NODE* next = i->next;
		if ( free_elem != NULL)
			free_elem(i->data);
		free(i);
		i = next;
	}
	
	free(D);
}

/*MODIFICATORS*/
void DEQUE_ENQUEUE( DEQUE_STRUCT* D, dtype data) {
	DEQUE_STRUCT_NODE* newnode = DEQUE_NODE_CREATE(data);

	if(D->first == NULL){
		D->first = D->last = newnode;
	}else{
		D->last->next = newnode;
		D->last = newnode;
	}
	D->size++;
}

//DEQUE_DEQUEUE
//returns true or false whether was possible removes the first element
boolean DEQUE_DEQUEUE( DEQUE_STRUCT* D, dtype* dequeued){
	if ( DEQUE_IS_EMPTY( D ) ){
		return false;
	}
	
	(*dequeued) = D->first->data;
	
	DEQUE_STRUCT_NODE* old_box = D->first;

	D->first = old_box->next;
	
	if( D->size == 1 )
		D->last = D->first;
	
	D->size--;
	free(old_box);
	return true;
}

/*ATRIBUTES*/
boolean DEQUE_IS_EMPTY( DEQUE_STRUCT* D){
	return (D->size <= 0)?true:false;
}

/*OPERATIONS*/
void DEQUE_PRINT(DEQUE_STRUCT* D, void(print_elem)( dtype )) {
	DEQUE_STRUCT_NODE* i;
	for ( i=D->first ; i!=NULL; i=i->next){
		print_elem(i->data);
	}
}

/*-----------------------------------------------------------------------------------------
__________
|UNDEFINES
----------
*/


#undef dtype
/*auxx*/
//deque
#undef DDDEQUE_FUNC
#undef DDEQUE_FUNC
#undef DEQUE_FUNC
//deque node
#undef DDDEQUE_NODE_FUNC
#undef DDEQUE_NODE_FUNC
#undef DEQUE_NODE_FUNC


/*struct*/
#undef DEQUE_STRUCT_NODE
#undef DEQUE_STRUCT

/*functions*/

//create
#undef DEQUE_CREATE

//destroy
#undef DEQUE_DESTROY

//size
#undef DEQUE_SIZE

//is_empty
#undef DEQUE_IS_EMPTY

//enqueue
#undef DEQUE_ENQUEUE

//unqueue
#undef DEQUE_DEQUEUE

//pop
#undef DEQUE_POP

//push
#undef DEQUE_PUSH

//print
#undef DEQUE_PRINT

/* DEQUE NODE */
#undef DEQUE_NODE_CREATE

#undef _DEQUE_TYPE_
#undef _DEQUE_NAME_

#endif //if XPAND(X)

#undef XPAND
