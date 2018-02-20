/*  Implemnted by Junha Choi
    Course: Cmpt 300 */
#ifndef LIST_H_
#define LIST_H_

#define NodeSize 50
#define HeadSize 5

#include"Node.h"

typedef struct _List LIST;
typedef struct _List *List;

struct _List{; 
	pNode current;
	pNode last;
	pNode first;
	int size;
};


extern pNode NodeStack[];
extern List ListStack[];

extern Node NodeMemory[];
extern LIST ListMemory[];

extern int usedNodeSize;
extern int usedNodeStackSize;

extern int usedHeadSize;
extern int usedHeadStackSize;

// make a new, empty list, and returns its reference on success.
// Return a NULL pointer on failure.
List LISTCreate();

// returns the number of itmes in list.
int ListCount(List list);

// returns a pointer to the first itme in list and makes the first item
// the current item.
void *ListFirst(List list);

// returns a pointer to the last item in list and makes the last item
// the current one.
void *ListLast(List list);

// advances list's current item by one
// and returns a pointer to the new current item.
// if the operation advances the current item beyond the end of the list
// returns NULL pointer instead.
void *ListNext(List list);

// backs up list's current itme by one
// and returns a pointer to the new current item.
// if the operation advances the current item beyond the start of the list
// returns NULL pointer instead.
void *ListPrev(List list);

// returns a pointer to the current item in list.
void *ListCurr(List list);

int ListAdd (List list, void* item);

int ListInsert (List list, void* item);

int ListAppend (List list, void* item);

int ListPrepend (List list, void* item);

void *ListRemove (List list);

void ListConcat (List list1, List list2);

void *ListTrim (List list);

void *ListSearch (List list, int (*comparator)(const void* a, const void* b), const void *comparisonArg);    
void ListFree(List list, void (*itemFree)(pNode pnode));
void itemFreer(pNode pnode);

int comparator_for_int (const void* a, const void* b);

void ListPrint(List list); // use ListCount and ListNext
void ListMemoryStatus(); 

#endif
