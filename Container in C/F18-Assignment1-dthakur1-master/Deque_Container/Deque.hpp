/*
 * Implement your functionality here without changing test.cpp
 */
#ifndef DEQUE_H
#define DEQUE_H



///////////////////////////////struct definitions and declarations
#define Deque_DEFINE(t)															\
typedef struct Deque_##t Deque_##t;												\
typedef struct Deque_##t##_Iterator Deque_##t##_Iterator;						\
																				\
																				\
struct Deque_##t 																\
{																				\
	t *array;																	\
	int at_front, at_back; 														\
	size_t current_size, capacity;												\
																				\
	char type_name[strlen("Deque_" #t)+1];										\
																				\
	bool (*comparator)(const t &, const t &);									\
	int (*comparator_reverse)(const void*, const void*);						\
	size_t (*size)(Deque_##t *);												\
	bool (*empty)(Deque_##t *);													\
																				\
	void (*push_back)(Deque_##t *, t);											\
	void (*push_front)(Deque_##t *, t);											\
																				\
	void (*pop_back)(Deque_##t *);												\
	void (*pop_front)(Deque_##t *);												\
																				\
	t & (*back)(Deque_##t *);													\
	t & (*front)(Deque_##t *);													\
	t & (*at)(Deque_##t *, int);												\
																				\
																				\
	void (*sort)(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);		\
																				\
	/*Iterator functions*/														\
	Deque_##t##_Iterator (*begin)(Deque_##t *);									\
	Deque_##t##_Iterator (*end)(Deque_##t *);									\
																				\
	void (*clear)(Deque_##t *);	/*TODO*/										\
	void (*dtor)(Deque_##t *);													\
};																				\
																				\
/*Used for qsort. Fix this to not use any global variable*/						\
Deque_##t *current_##t##_dq;													\
																				\
struct Deque_##t##_Iterator{													\
	int position;																\
	t *array;																	\
																				\
	void (*inc)(Deque_##t##_Iterator *);										\
	void (*dec)(Deque_##t##_Iterator *);										\
	t &(*deref)(Deque_##t##_Iterator *);										\
};																				\
																				\
/*						Function declarations		*/							\
																				\
/*Functions directly called from main*/											\
void Deque_##t##_ctor(Deque_##t *, bool (*)(const t &, const t &)); 			\
bool Deque_##t##_equal(Deque_##t , Deque_##t );									\
bool Deque_##t##_Iterator_equal(Deque_##t##_Iterator, Deque_##t##_Iterator);	\
																				\
/*Deque methods*/																\
int comparator_##t##_reverse(const void*, const void*);							\
size_t size(Deque_##t *);														\
bool empty(Deque_##t *);														\
void push_back(Deque_##t *, t);													\
void push_front(Deque_##t *, t);												\
void pop_back(Deque_##t *);														\
void pop_front(Deque_##t *);													\
t & back(Deque_##t *);															\
t & front(Deque_##t *);															\
t & at(Deque_##t *, int);														\
																				\
void sort(Deque_##t *, Deque_##t##_Iterator, Deque_##t##_Iterator);				\
																				\
Deque_##t##_Iterator begin(Deque_##t *);										\
Deque_##t##_Iterator end(Deque_##t *);											\
void clear(Deque_##t *);														\
void dtor(Deque_##t *);															\
																				\
/*Iterator Functions*/															\
void inc(Deque_##t##_Iterator *);												\
void dec(Deque_##t##_Iterator *);												\
t & deref(Deque_##t##_Iterator *);												\
																				\
/*utilities*/																	\
void extendFront(Deque_##t *);													\
void extendBack(Deque_##t *);													\
																				\
/*					Function definitions	*/									\
																				\
/*		Functions directly called from main */									\
void Deque_##t##_ctor(Deque_##t *dq, bool (* cmp)(const t &o1, const t &o2) )	\
{																				\
	dq->capacity = 2;															\
	dq->at_front = 0;															\
	dq->at_back = 1;															\
	dq->current_size = dq->at_back - dq->at_front - 1;							\
																				\
	dq->array = ( t *)malloc(dq->capacity * sizeof( t ));						\
	assert(dq->array != 0);														\
	strcpy(dq->type_name , "Deque_"#t);											\
	dq->type_name[sizeof(dq->type_name)-1] = '\0';								\
																				\
	dq->comparator = cmp;														\
	dq->comparator_reverse = comparator_##t##_reverse;							\
	dq->size = size;															\
	dq->empty = empty;															\
	dq->push_front = push_front;												\
	dq->push_back = push_back;													\
	dq->pop_front = pop_front;													\
	dq->pop_back = pop_back;													\
	dq->front = front;															\
	dq->back = back;															\
	dq->sort = sort;															\
	dq->at = at;																\
    dq->begin = begin;															\
    dq->end = end;																\
    dq->clear = clear;															\
    dq->dtor = dtor;															\
}																				\
																				\
bool 																			\
Deque_##t##_Iterator_equal(Deque_##t##_Iterator it, Deque_##t##_Iterator end){	\
    return (it.position == end.position);										\
}																				\
																				\
/*Deque methods*/																\
int comparator_##t##_reverse(const void* o1, const void* o2){					\
	if(current_##t##_dq->comparator(*( t *)o2, *( t *)o1) == true)	return 1;	\
	/*Spent 4 hours debugging because typecast was wrong.*/						\
	/*was doing current_dq->comparator((const int &)o1, (const int &)o2) == true)*/\
	/*STUPID*/																	\
	return -1;																	\
}																				\
																				\
size_t size(Deque_##t *thiss){													\
	return (size_t)thiss->at_back - thiss->at_front - 1;						\
}																				\
																				\
bool empty(Deque_##t *thiss){													\
	return (thiss->at_back - thiss->at_front - 1 == 0);							\
}																				\
																				\
void push_back(Deque_##t* thiss, t element){									\
	if((size_t)thiss->at_back >= thiss->capacity)	extendBack(thiss);			\
	/*This is because d->at_back is changed in extendFront.*/					\
	thiss->array[thiss->at_back] = element;										\
	++thiss->current_size;														\
	++thiss->at_back;															\
/*	if(thiss->at_back > thiss->capacity)	{ printf("Overflow at at_back\n"); exit(0); }*/	\
/* 	if(thiss->at_back == thiss->capacity)	extendBack(thiss);*/				\
	return;																		\
}																				\
																				\
void push_front(Deque_##t* thiss, t element){									\
	thiss->array[thiss->at_front] = element;									\
	++thiss->current_size;														\
	if(thiss->at_front - 1 < 0)	extendFront(thiss);								\
	--thiss->at_front;															\
	return;																		\
}																				\
																				\
void pop_back(Deque_##t* thiss){												\
	--thiss->at_back;															\
	--thiss->current_size;														\
	if(thiss->at_front >= thiss->at_back){ printf("Wrap around from at_back\n"); exit(0); }	\
	/*TODO fix this*/															\
	return;																		\
}																				\
																				\
void pop_front(Deque_##t* thiss){												\
	++thiss->at_front;															\
	--thiss->current_size;														\
	if(thiss->at_front >= thiss->at_back){ printf("Wrap around from at_front\n"); exit(0); }	\
	/*TODO fix this*/															\
}																				\
																				\
t & back(Deque_##t * thiss){													\
	return thiss->array[thiss->at_back - 1];									\
}																				\
																				\
t & front(Deque_##t *thiss){													\
	return thiss->array[thiss->at_front + 1];									\
}																				\
																				\
t & at(Deque_##t *thiss, int i){												\
    return thiss->array[thiss->at_front+1+i];									\
}																				\
																				\
																				\
void sort(Deque_##t *thiss, Deque_##t##_Iterator it_a, Deque_##t##_Iterator it_b){	\
	current_##t##_dq = thiss;													\
	int size_for_qs = it_b.position - it_a.position ;							\
	/*Off by one error? NOT ANYMORE*/											\
																				\
	qsort((void*)&(thiss->array[it_a.position]), size_for_qs, sizeof( t ), thiss->comparator_reverse);	\
	return;																		\
}																				\
																				\
Deque_##t##_Iterator begin(Deque_##t *thiss){									\
	Deque_##t##_Iterator it = {thiss->at_front+1 , 								\
							 thiss->array,										\
							 inc, dec, deref};									\
	return it;																	\
}																				\
Deque_##t##_Iterator end(Deque_##t *thiss){										\
	Deque_##t##_Iterator it = {thiss->at_back , 								\
							 thiss->array,										\
							 inc, dec, deref};									\
    return it;																	\
}																				\
																				\
void clear(Deque_##t *){														\
	return;																		\
}																				\
																				\
void dtor(Deque_##t *thiss){													\
	free(thiss->array);															\
	thiss->array = 0;															\
	current_##t##_dq = 0;														\
	return;																		\
}																				\
																				\
/*Iterator functions*/															\
void inc(Deque_##t##_Iterator *it){												\
	++it->position;																\
	return;																		\
}																				\
																				\
void dec(Deque_##t##_Iterator *it){												\
	--it->position;																\
	return;																		\
}																				\
																				\
t & deref(Deque_##t##_Iterator *it){											\
	return it->array[it->position];												\
}																				\
																				\
/*Utilities definition*/														\
void extendBack(Deque_##t *thiss){												\
	t *new_array = ( t *)malloc(2*thiss->capacity*sizeof( t ));					\
	memcpy(new_array, thiss->array, thiss->capacity*sizeof( t ));				\
	thiss->capacity = thiss->capacity * 2;										\
	free(thiss->array);															\
	thiss->array = new_array;													\
}																				\
																				\
void extendFront(Deque_##t *thiss){												\
	t *new_array = ( t *)malloc(2*thiss->capacity*sizeof( t ));					\
	thiss->at_front = thiss->capacity;											\
	thiss->at_back = thiss->at_front + thiss->current_size ;					\
	memcpy(&new_array[thiss->at_front], thiss->array, thiss->current_size*sizeof( t ));	\
																				\
	thiss->capacity = thiss->capacity * 2;										\
	free(thiss->array);															\
	thiss->array = new_array;													\
	new_array = NULL;															\
	return;																		\
}																				\
bool Deque_##t##_equal(Deque_##t a, Deque_##t b){								\
	bool sizeEqual = (a.current_size == b.current_size);						\
	if(!sizeEqual)	{return false;}												\
	for(int i = 1; i<= (int)a.current_size; i++){								\
		if(a.comparator(a.array[a.at_front + i], b.array[b.at_front + i]) ||	\
			a.comparator(b.array[b.at_front + i], a.array[a.at_front + i]) )	\
		{																		\
			return false;														\
		}																		\
	}																			\
	return true;																\
}																				\
																				\


#define DEFINE_EQUAL_int 														\
bool Deque_int_equal(Deque_int a, Deque_int b){									\
	bool sizeEqual = (a.current_size == b.current_size);						\
	if(!sizeEqual)	{return false;}												\
																				\
	for(int i = 1; i<= (int)a.current_size; i++){								\
		if(a.array[a.at_front + i] != b.array[b.at_front + i]){					\
			return false;														\
		}																		\
	}																			\
																				\
	return true;																\
}																				\



#define DEFINE_EQUAL_MyClass 													\
bool Deque_MyClass_equal(Deque_MyClass a, Deque_MyClass b){						\
	bool sizeEqual = (a.current_size == b.current_size);						\
	if(!sizeEqual)	{	return false;	}										\
																				\
	for(int i = 1; i<= (int)a.current_size; i++){								\
		if(a.array[a.at_front + i].id != b.array[b.at_front + i].id ||	(strcmp(a.array[a.at_front + i].name, b.array[b.at_front + i].name) != 0) )		\
		{																		\
			return false;														\
		}																		\
	}																			\
	return true;																\
}																				\


#endif
