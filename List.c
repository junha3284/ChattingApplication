/* Implemented by Junha Choi
   Course: Cmpt 300 */
#include <stdio.h>
#include "List.h"

pNode NodeStack[NodeSize];
List ListStack[HeadSize];

Node NodeMemory[NodeSize];
LIST ListMemory[HeadSize];

int usedNodeStackSize = -1; // Used for index in stack for last put Node
int usedHeadStackSize = -1; // Used for index in stack for last put LIST

int usedNodeSize = 0;
int usedHeadSize = 0;

List LISTCreate(){
    if(usedHeadSize >= HeadSize)
        return NULL;
    else if( 0 <= usedHeadStackSize && usedHeadStackSize < HeadSize) {
        usedHeadStackSize--;
        usedHeadSize ++;
        return ListStack[usedHeadStackSize+1]; // when put in STack, change size to 0, last and first to null
    }
    else {
        List temp = &(ListMemory[usedHeadSize]);
        usedHeadSize++;
        temp->size = 0;
	temp->current = NULL;
	temp->first = NULL;
        temp->last = NULL;
        return temp;
    }
    return NULL;
}

int ListCount(List list){
    return (*list).size;
}

void *ListFirst(List list){
    if((*list).size == 0)
        return NULL;
    (*list).current = (*list).first;
    return (*list).current->item;
}

void *ListLast(List list){
    if((*list).size == 0)
        return NULL;
    (*list).current = (*list).last;
    return (*list).current->item;
}	

void *ListNext(List list){
    if((*list).current == (*list).last){
        (*list).current = (*list).first;
        return NULL;
    }
    (*list).current = (*list).current->next;
    return (*list).current->item;
}

void *ListPrev(List list){
    if((*list).current == (*list).first){
        (*list).current = (*list).last;
        return NULL;
    }
    (*list).current = (*list).current->prev;
    return (*list).current->item;
}

void *ListCurr(List list){
    if((*list).current == NULL)
        return NULL;
    return (*list).current->item;
}

int ListAdd (List list, void* item){
    if(usedNodeSize >= NodeSize)
        return -1;
    if( 0 <= usedNodeStackSize && usedNodeStackSize < NodeSize) { // when Stack is not empty
        
        pNode temp = NodeStack[usedNodeStackSize];
        temp->item = item;
        usedNodeStackSize--;
        usedNodeSize++;
        
        if((*list).last == (*list).current) {
            temp->next = NULL;
            if ((*list).current == NULL ){
            	temp->prev = NULL;
                (*list).first = temp;
            }
            else{
                (*list).current -> next = temp;
		temp->prev = (*list).current;
            }
            (*list).last = temp;
            (*list).current = (*list).last;
            (*list).size++;
            return 1;
        }
        else {
            temp->next = (*list).current->next;
            temp->prev = (*list).current;
            (*list).current->next = temp;
            (temp->next) -> prev = temp;
            (*list).size++;
            return 0;
        }
        return -1;
    }
    
    else { 
	pNode temp = &(NodeMemory[usedNodeSize]);
	usedNodeSize++;
        temp -> item = item;
	if((*list).current == (*list).last) { 
            temp->next = NULL;
            if ((*list).current == NULL ){
            	temp->prev = NULL;
                (*list).first = temp;
            }
            else{
                (*list).current -> next = temp;
		temp->prev = (*list).current;
            }
            (*list).last = temp;
            (*list).current = (*list).last;
            (*list).size++;
            return 0;
        }
        else {
            temp->next = (*list).current->next;
            temp->prev = (*list).current;
            (*list).current->next = temp;
            (temp->next) -> prev = temp;
            (*list).size++;
            return 0;
        }
        return -1;
    }
    return -1;
}

int ListInsert(List list, void* item) {
    if(usedNodeSize >= NodeSize)
        return -1;
    if( 0 <= usedNodeStackSize && usedNodeStackSize < NodeSize) { // when Stack is not empty
        
        pNode temp = NodeStack[usedNodeStackSize];
        temp->item = item;
        usedNodeStackSize--;
        usedNodeSize++;
        
        if((*list).first == (*list).current) {
            temp->prev = NULL;
            if ((*list).current == NULL ){
            	temp->next = NULL;
                temp->prev = NULL;
                (*list).last = temp;
            }
            else { 
                (*list).current -> prev = temp;
		temp->next = (*list).current;
            }
            (*list).first = temp;
            (*list).current = (*list).first;
            (*list).size++;
            return 0;
        }
        else {
            temp->prev = (*list).current->prev;
            temp->next = (*list).current;
            (*list).current->prev = temp;
            (temp->prev) -> next = temp;
            (*list).size++;
            return 0;
        }
        return -1;
    }
    
    else { 
	pNode temp = &(NodeMemory[usedNodeSize]);
	usedNodeSize++;
        temp -> item = item;
	if((*list).first == (*list).current) {
            temp->prev = NULL;
            if ((*list).current == NULL ){
            	temp->next = NULL;
                temp->prev = NULL;
                (*list).last = temp;
            }
            else { 
                (*list).current -> prev = temp;
		temp->next = (*list).current;
            }
            (*list).first = temp;
            (*list).current = (*list).first;
            (*list).size++;
            return 0;
        }
        else {
            temp->prev = (*list).current->prev;
            temp->next = (*list).current;
            (*list).current->prev = temp;
            (temp->prev) -> next = temp;
            (*list).size++;
            return 0;
        }
        return -1;
    }
    return -1;
}

int ListAppend (List list, void* item){
    if(usedNodeSize >= NodeSize)
        return -1;
    if( 0 <= usedNodeStackSize && usedNodeStackSize < NodeSize) { // when Stack is not empty
	   
        pNode temp = NodeStack[usedNodeStackSize];
        temp->item = item;
        usedNodeStackSize--;
        usedNodeSize++;
        
        if( list->size == 0){
            list->current = temp;
            list->first = temp;
            temp->prev = NULL;
        }
	else{
            (list->last)->next = temp;
            temp->prev = (list->last);
        }
        temp->next = NULL;
        list->last = temp;
        list->current = temp;
        (list->size)++;
        return 0;
    }
    
    else { 
	pNode temp = &(NodeMemory[usedNodeSize]);
	usedNodeSize++;
        temp -> item = item;
        
       if( list->size == 0){
            list->current = temp;
            list->first = temp;
            temp->prev = NULL;
        }
	else{
            (list->last)->next = temp;
            temp->prev = (list->last);
        }
        temp->next = NULL;
        list->last = temp;
        list->current = temp;
        (list->size)++;
        return 0;
    
    }
    return -1;
}     


int ListPrepend (List list, void* item){
    if(usedNodeSize >= NodeSize)
        return -1;
    if( 0 <= usedNodeStackSize && usedNodeStackSize < NodeSize) { // when Stack is not empty
	   
        pNode temp = NodeStack[usedNodeStackSize];
        temp->item = item;
        usedNodeStackSize--;
        usedNodeSize++;
        
        if( list->size == 0){
            list->current = temp;
            list->last = temp;
            temp->next = NULL;
        }
	else{
            (list->first)->prev = temp;
            temp->next = (list->first);
        }
        temp->prev = NULL;
        list->first = temp;
        list->current = temp;
        (list->size)++;
        return 0;
    }
    
    else { 
	pNode temp = &(NodeMemory[usedNodeSize]);
	usedNodeSize++;
        temp -> item = item;
	       
        if( list->size == 0){
            list->current = temp;
            list->last = temp;
            temp->next = NULL;  
        }
	else{
            (list->first)->prev = temp;
            temp->next = (list->first);
        }
        temp->prev = NULL;
        list->first = temp;
        list->current = temp;
        (list->size)++;
        return 0;
    
    }
    return -1;
}

void *ListRemove(List list){
    if( list->size == 0)
        return NULL;
    else{
        usedNodeStackSize++;
        usedNodeSize--;
        NodeStack[usedNodeStackSize] = list -> current;
        void* temp = (list->current)->item;
        if( list->size ==1){
            list->current = NULL;
            list->first = NULL;
            list->last = NULL;
        }
        else if( list->current == list->last){
            list->last = (list->last)->prev;
            (list->last)->next = NULL;
            list->current = list->first;
        }
        else if( list->current == list->first){
            list->first = (list->first)->next;
            (list->first)->prev = NULL;
            list->current = list->first;
        }
        else{
            ((list->current)->prev)->next = (list->current)->next;
            ((list->current)->next)->prev = (list->current)->prev;
            list->current = (list->current)->next;
        }
        list->size--;
        NodeStack[usedNodeStackSize]->next = NULL;
        NodeStack[usedNodeStackSize]->prev = NULL;
        NodeStack[usedNodeStackSize]->item = NULL;
        return temp; 
    }
    return NULL;
}

void ListConcat (List list1, List list2){
    usedHeadStackSize ++;
    usedHeadSize--;
    ListStack[usedHeadStackSize] = list2;
    if( list1->size != 0 && list2->size !=0){
        (list1->last)->next = list2->first;
        (list2->first)->prev = list1->last;
        list1->size += list2->size;
        list1->last = list2 ->last;
    }
    else if( list2->size !=0){
        list1->first = list2->first;
        list1->last = list2->last;
        list1->current = list1->first;
        list1->size = list2->size;
    }
    list2->first = NULL;
    list2->current = NULL;
    list2->last = NULL;
    list2->size = 0;
}

void *ListTrim(List list){
    if(list->size == 0)
        return NULL;
  
    usedNodeStackSize++;
    usedNodeSize--;
    NodeStack[usedNodeStackSize] = list -> last;
    
    void* temp = (list->last)->item;
    
    list->current = (list->last)->prev;
    list->last = list->current;
    list->size--;

    if(list->size == 0)
        list->first = NULL;
    else
        list->last->next = NULL;

    NodeStack[usedNodeStackSize]->next = NULL;
    NodeStack[usedNodeStackSize]->prev = NULL;
    NodeStack[usedNodeStackSize]->item = NULL;
    return temp;
}

void itemFreer(pNode pnode){
    usedNodeStackSize++;
    usedNodeSize--;
    NodeStack[usedNodeStackSize] = pnode;
    
    NodeStack[usedNodeStackSize]->next = NULL;
    NodeStack[usedNodeStackSize]->prev = NULL;
    NodeStack[usedNodeStackSize]->item = NULL;
}

void ListFree(List list, void (*itemFree)(pNode pnode)){
    if(list->size != 0){
        pNode temp;
        while((list->first) != NULL) {
            temp = list->first;
            list->first = (list->first)->next;
            (*itemFree)(temp);
        }
    }

    usedHeadStackSize++;
    usedHeadSize--;
    ListStack[usedHeadStackSize] = list;
    
    list->size = 0;
    list->last = NULL;
    list->current = NULL;
}

void *ListSearch (List list, int(*comparator)(const void *a, const void *b), const void *comparisonArg){
    if(list->size ==0)
        return NULL;
    pNode traverser = list->first;
    while(traverser) {
        if((*comparator)(traverser->item,comparisonArg)){
            return traverser->item;
        }
        traverser = traverser->next;
    }
    return NULL;
}

int comparator_for_int (const void *a, const void *b){
    if(*((int*)a) == *((int*)b))
        return 1;
    return 0;
}

void ListPrint(List list){
        if(list==NULL){
            printf("list is NULL");
            return;
        }
	if(list->size !=0){
            pNode current = list->current; 
	    void *temp = ListFirst(list);
	    printf("%d ", *((int*)temp));
            for(int i=0; i < ListCount(list)-1; i ++){
                temp = ListNext(list); 
                printf("%d ",  *((int*)temp));
            }
            printf("\n");
	    list->current = current;
            current = NULL;
       }
       else
           printf("list is empty\n");
}

void ListMemoryStatus(){
    printf("Node Stack Size: %d\n", usedNodeStackSize);
    printf("Node Used Size: %d\n", usedNodeSize);
    
    printf("List Stack Size: %d\n", usedHeadStackSize);
    printf("List Used Size: %d\n\n", usedHeadSize);
    printf("----------------------------------------------\n");
}
