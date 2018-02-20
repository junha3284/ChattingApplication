/* Implemented by Junha Choi
   Course: Cmpt 300 */
#include <stdio.h>
#include "List.h"

int main() {
    int a = 1;
    int b = 2;
    int c = 3;
    int d = 4;
    int e = 5; 
    
    void *test;

    ////////////////////////////////////// ListCreate
    printf("\nCase1: when List is created more than capability\n");
    List list1 = LISTCreate();
    List list2 = LISTCreate();
    List list3 = LISTCreate(); 
    List list4 = LISTCreate(); // list 4 should be NULL
    printf("Result: list 4 == NULL is %d\n", list4 == NULL);
    ListMemoryStatus();
   
    ///////////////////////////////////// ListAdd, ListCurr, travelers
    printf("Case2: ListAdd test (expected 1 2 3) and ListCurr, traverling test\n");
    ListAdd(list1, &a);
    ListAdd(list1, &b);
    ListAdd(list1, &c);
    printf("Result: ");
    ListPrint(list1);
    test = ListCurr(list1);
    printf("List current after adding: %d (expected 3)\n", *((int*)test));
    test = ListPrev(list1);
    printf("List current after prev: %d (expected 2)\n", *((int*)test));
    test = ListPrev(list1);
    printf("List current after prev: %d (expected 1)\n", *((int*)test));
    test = ListPrev(list1);
    printf("List returned itema by prev at first is NULl: %d\n", test ==NULL);
    test = ListCurr(list1);
    printf("List current after prev at first: %d (expected 3)\n", *((int*)test)); 
    test = ListFirst(list1);
    printf("List first: %d (expected 1)\n", *((int*)test)); 
    test = ListLast(list1);
    printf("List last: %d (expected 3)\n", *((int*)test));
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case3: ListAppend test with empty (expected 1)\n");
    ListAppend(list2, &a);
    printf("Result: ");
    ListPrint(list2);
    test = ListCurr(list2);
    printf("List current after Append: %d (expected 1)\n", *((int*)test));
    ListMemoryStatus();
    

    ////////////////////////////////////// 
    printf("Case4: ListAppend test with non-empty (expected 1 2 3 4)\n");
    ListAppend(list1, &d);
    printf("Result: ");
    ListPrint(list1);
    test = ListCurr(list1);
    printf("List current after Append: %d (expected 4)\n", *((int*)test));
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case5: ListRemove test with non-empty (From 1)\n");
    test = ListRemove(list2);
    ListPrint(list2);
    printf("Removed item: %d (expected 1)\n", *((int*)test));
    ListMemoryStatus();
     
    //////////////////////////////////////
    printf("Case6: ListRemove test with empty\n");
    test = ListRemove(list2);
    ListPrint(list2);
    printf("Result: removed item is NULL: %d\n", test == NULL);
    ListMemoryStatus();

    //////////////////////////////////////
    printf("Case7: ListInsert test with empty (expected 1)\n");
    ListInsert(list2, &a);
    printf("Result: ");
    ListPrint(list2);
    test = ListCurr(list2);
    printf("List current after Insert: %d (expected 1)\n", *((int*)test));
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case8: ListInsert test with non-empty (expected 2 1)\n");
    ListInsert(list2, &b);
    printf("Result: ");
    ListPrint(list2);
    test = ListCurr(list2);    
    printf("List current after Insert: %d (expected 2)\n", *((int*)test));
    ListMemoryStatus();

    ////////////////////////////////////// 
    printf("Case9: ListPrepend test with non-empty (expected 5 1 2 3 4)\n");
    ListPrepend(list1, &e);
    printf("Result: ");
    ListPrint(list1);
    test = ListCurr(list1);
    printf("List current after Append: %d (expected 5)\n", *((int*)test));
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case10: ListPrepend test with empty (expected 1)\n");
    ListPrepend(list3, &a);
    ListPrint(list3);
    test = ListCurr(list3);
    printf("List current after Append: %d (expected 1)\n", *((int*)test));
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case11: ListTrim test with non-empty(from 1)\n");
    test = ListTrim(list3);
    printf("Result: ");
    ListPrint(list3);
    printf("Trimmed item: %d (expected 1)\n", *((int*)test));
    ListMemoryStatus();
  
    //////////////////////////////////////
    printf("Case12: ListTrim test with empty\n");
    test = ListTrim(list3);
    ListPrint(list3);
    printf("Result: trimmed item is NULL: %d\n", test ==NULL);
    ListMemoryStatus();
   
    //////////////////////////////////////
    printf("Case13: ListConcat test with non-empties(expected 5 1 2 3 4 2 1)\n");
    ListConcat(list1,list2);
    list2 = NULL;
    printf("Result: ");
    ListPrint(list1);
    test = ListCurr(list1);
    printf("List current after concat: %d (expected 5)\n", *((int*)test));
    ListMemoryStatus();
 
    //////////////////////////////////////
    printf("Case14: Concat test with non-empty and empty(expted 5 1 2 3 4 2 1)\n");
    ListConcat(list1, list3);
    list3 = NULL;
    printf("Result: ");
    ListPrint(list1);
    ListMemoryStatus();
   
    /////////////////////////////////////
    printf("Case15: ListConcat test with empty and non-empty(expted 5 1 2 3 4 2 1 || created empty List)\n");
    list3 = LISTCreate();
    ListConcat(list3, list1);
    list1 = NULL;
    printf("Result: ");
    ListPrint(list3);
    ListMemoryStatus();

    //////////////////////////////////////
    printf("Case16: ListSearch for existing value test\n");
    test = ListSearch(list3, comparator_for_int, &b);
    printf("Result: searched Item %d (expected 2)\n", *((int*)test));
    ListMemoryStatus();    

    //////////////////////////////////////
    printf("Case17: ListSearch for non-existing value test\n");
    int f = 6;
    test = ListSearch(list3, comparator_for_int, &f);
    printf("Result: searched Item is NULL: %d\n", test ==NULL);
    ListMemoryStatus();

    //////////////////////////////////////
    printf("Case18: ListFree for non-empty List\n");
    ListFree(list3, itemFreer);
    printf("Result: list1's size after ListFree is %d\n", list3->size);
    list3 = NULL;
    ListMemoryStatus();
    
    //////////////////////////////////////
    printf("Case19: ListFree for empty List (created empty List)\n");
    list2 = LISTCreate();
    ListFree(list2, itemFreer);
    list2 = NULL;
    ListMemoryStatus();
    //////////////////////////////////////
    return 0;
}
