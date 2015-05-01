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

/* _DEQUE_DEF_ */
//macro to assist in create the condition to not include or define twice the same structure
#ifndef _DEQUE_DEF_
	#define _DEQUE_DEF_ (X, Y) _ # X # _ # Y # _
#endif

/* _DEQUE_TYPE_ */
//holds the type of the struct
#ifndef _DEQUE_TYPE_
	#define _DEQUE_TYPE_ void*
#endif

//holds the name, i.e., the name of the struct that you'll use. This must to be unique
#ifndef _DEQUE_NAME_
	#define _DEQUE_NAME_ deque
#endif

/*-----------------------------------------------------------------------------------------
___________________________________________
|MACROS OF THE {FUNCTIONS,STRUCTURES} NAME
-------------------------------------------
*/

/*auxx*/
#define DDDEQUE_FUNC(X, Y) X ## _ ## Y
#define DDEQUE_FUNC(X, Y) DDDEQUE_FUNC(X, Y)
#define DEQUE_FUNC(X) DDEQUE_FUNC(_DEQUE_NAME_, X)

/*struct*/
#define DEQUE_STRUCT_NODE DDEQUE_FUNC(_DEQUE_NAME_, _node_t)
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

//unqueue
#define DEQUE_UNQUEUE DEQUE_FUNC(unqueue)

//pop
#define DEQUE_POP DEQUE_FUNC(pop)

//push
#define DEQUE_PUSH DEQUE_FUNC(push)


/*-----------------------------------------------------------------------------------------
_________
|INCLUDES
----------
*/
#include <stdlib.h>
/*-----------------------------------------------------------------------------------------*/

typedef _DEQUE_TYPE_ dtype; //dtype it's the type of all this full generic crazyness

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
/*-----------------------------------------------------------------------------------------*/

//create node
//_deque_name__node_t* _deque_name__create_node(dtype data){
//	_deque_ame__node_t* newnode = (_deque_name__node_t*) malloc(sizeof(_deque_name__node_t));
//	newnode->prev = newnode->next = NULL;
//	newnode->data = data;
//	return newnode;
//}
////constructor and destructor
//STR(_deque_name_)_t* STR(_deque_name_)_create(){
//	STR(_deque_name_)_t* D = NULL;
//	D = (STR(_deque_name_)_t*) malloc(sizeof(STR(_deque_name_)_t));
//
//	if(D) D->size = (unsigned long int) (D->first = D->last = NULL);
//	
//	return D;
//}

//void _deque_destroy(deque_t* D){
//	dequenode_t* i = D->first;
//	
//	if(i!=NULL)
//	do{
//		free(i);
//	}while (i != D->last && i!=NULL);
//
//	free(D);
//}
//
////modificators
//void _deque_append(deque_t* D, dtype data){
//	dequenode_t* newnode = create_node(data);
//
//	if(D->first == NULL){
//		D->first = D->last = newnode;
//		newnode->next = newnode->prev = newnode;
//	}else{
//		D->last->next = newnode;
//		D->last = newnode;
//	}
//	D->size++;
//}

