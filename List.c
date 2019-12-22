//Ahlden Brough
//ajbrough
//pa3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"List.h"


// structs --------------------------------------------------------------------

// private NodeObj type
typedef struct NodeObj{
  long data;
  struct NodeObj* next;
  struct NodeObj* prev;
} NodeObj;

// private Node type
typedef NodeObj* Node;

// private ListObj type
typedef struct ListObj{
  Node front;
  Node back;
  Node cursor;
  int length;
  int index;
} ListObj;


// Constructors-Destructors ---------------------------------------------------

// newNode()
// Returns reference to new Node object. Initializes next, prev, and data fields.
// Private.
Node newNode(long data){
  Node N = malloc(sizeof(NodeObj));
  N->data = data;
  N->next = NULL;
  N->prev = NULL;
  return(N);
}

// freeNode()
// Frees heap memory pointed to by *pN, sets *pN to NULL.
// Private.
void freeNode(Node* pN){
  if( pN!=NULL && *pN!=NULL ){
    free(*pN);
    *pN = NULL;
    }
}

// newList()
// Returns reference to new empty List object.
List newList(void){
  List L;
  L = malloc(sizeof(ListObj));
  L->front = L->back = NULL;
  L->length = 0;
  L->cursor = NULL;
  L->index = -1;
  return(L);
}


// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.S
void freeList(List* pL){
  if(pL!=NULL && *pL!=NULL) { 
    while( !isEmpty(*pL) ) { 
      deleteFront(*pL); 
    }
    free(*pL);
    *pL = NULL;
  }
}

// length()
// Returns the length of L.
int length(List L){
  if(L == NULL){
    printf("List Error: calling length() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->length;
}

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L){
  if(L == NULL){
    printf("List Error: calling index() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->index;
}

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
long front(List L){
  if( L==NULL ){
      fprintf(stderr, "List Error: calling front() on NULL List reference\n");
      exit(EXIT_FAILURE);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling front() on empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->front->data;
}

// back ()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
long back(List L){
  if( L==NULL ){
    fprintf(stderr, "List Error: calling front() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling back() on empty List\n");
    exit(EXIT_FAILURE);
  }
  return L->back->data;
}

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
long get(List L){
  if(L == NULL){
    printf("List Error: calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  if(isEmpty(L)){
    printf("List Error: calling get() on NULL List reference\n");
    exit(EXIT_FAILURE);
  }
  return L->cursor->data;
}

// // equals()
// // Returns true (1) iff Lists A and B are in same state, and returns false (0) otherwise.
// int equals(List A, List B){
//   if( A==NULL || B==NULL ){
//     printf("List Error: calling equals() on NULL List reference\n");
//     exit(EXIT_FAILURE);
//   }
  
//   int eq = 0;
//   Node N = NULL;
//   Node M = NULL;

//   eq = ( A->length == B->length );
//   N = A->front;
//   M = B->front;
//   while( eq && N!=NULL){
//     eq = (N->data==M->data);
//     N = N->next;
//     M = M->next;
//   }
//   return eq;
// }

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L){
  if( L==NULL ){
    printf("List Error: calling isEmpty() on NULL List reference\n");
    exit(1);
  }
  return(L->length==0);
}

// clear()
// Resets L to its original empty state
void clear(List L){
  
  while(L->length > 0){
    deleteFront(L);
  }
  L->cursor = NULL;
  L->front = NULL;
  L->back = NULL;
  L->index = -1;
}

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L){
  if( L==NULL ){
    printf("List Error: calling movefront() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling movefront() on empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor = L->front;
  L->cursor->prev = NULL;
  L->cursor->next = L->front->next;
  L->index = 0;
}

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L){
  if( L==NULL ){
    printf("List Error: calling moveBack() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling moveBack() on empty List\n");
    exit(EXIT_FAILURE);
  }
  L->cursor = L->back;
  L->cursor->prev = L->back->prev;
  L->cursor->next = NULL;
  L->index = L->length - 1;
}

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L){
  if( L==NULL ){
    printf("List Error: calling movePrev() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling movePrev() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor->prev == NULL){
    L->cursor = NULL;    
  }
  else if(L->cursor == NULL){
    return;
  }
  else{
    Node N = L->cursor;
    L->cursor = L->cursor->prev;
    L->cursor->prev = N->prev->prev;
    L->cursor->next = N;
  }
  L->index--;
}

// moveNext()
// If cursor is defined and not at front, move cursor one step toward the back of L; 
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L){
  if( L==NULL ){
    printf("List Error: calling moveNext() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    fprintf(stderr, "List Error: calling moveNext() on empty List\n");
    exit(EXIT_FAILURE);
  }
  if(L->cursor->next == NULL){
    L->cursor = NULL;
    L->index = -1;
    return;
  }
  else if(L->cursor == NULL){
    return;
  }
  else{
    Node N = L->cursor;
    L->cursor = L->cursor->next;
    L->cursor->next = N->next->next;
    L->cursor->prev = N;
    //freeNode(&N);
    //N = NULL;
  }
  L->index++;
}

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, long data){
  if( L==NULL ){
    printf("List Error: calling prepend() on NULL List reference\n");
    exit(1);
  }
  Node N = newNode(data);
  if(isEmpty(L)){
    L->front = L->back = N;
  }
  else{
    N->next = L->front;
    L->front->prev = N;
    L->front = N;
  }
  if(L->index != -1){
    L->index++;
  }
  L->length++;
  // freeNode(&N);
}

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, long data){
  if( L==NULL ){
    printf("List Error: calling append() on NULL List reference\n");
    exit(1);
  }
  Node N = newNode(data);
  if( isEmpty(L) ) { 
    L->front = L->back = N; 
  }
  else{ 
    L->back->next = N; 
    N->prev = L->back;
    L->back = N;
  }
  L->length++;
}

// insertBefore
// insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, long data){
  if( L==NULL ){
    printf("List Error: calling insertBefore() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    printf("List Error: calling insertBefore() on empty List reference\n");
    exit(1);
  }
  if( L->index<0 ){
    printf("List Error: calling insertBefore() when cursor is undefined\n");
    exit(1);
  }
  if(L->front == L->cursor){
    prepend(L, data);
    return;
  }
  Node N = newNode(data);
  N->next = L->cursor;
  N->prev = L->cursor->prev;
  L->cursor->prev->next = N;
  L->cursor->prev = N;
  L->length++;
  L->index++;
}

// insertAfter
// insert new element after cursor.
// Pre: length() > 0
void insertAfter(List L, long data){
  if( L==NULL ){
    printf("List Error: calling insertAfter() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    printf("List Error: calling insertAfter() on empty List reference\n");
    exit(1);
  }
  if( L->index<0 ){
    printf("List Error: calling insertBefore() when cursor is undefined\n");
    exit(1);
  }
  if(L->back == L->cursor){
    append(L, data);
    return;
  }
  Node N = newNode(data);
  N->prev = L->cursor;
  N->next = L->cursor->next;
  L->cursor->next->prev = N;
  L->cursor->next = N;
  L->length++;
}

// deleteFront()
// Delete the front element. Pre: length() > 0
void deleteFront(List L){
  if( L==NULL ){
    printf("List Error: calling deleteFront() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    printf("List Error: calling deleteFront() on empty List reference\n");
    exit(1);
  }
  Node N = NULL;
  N = L->front;
  if(L->index == 0){
    L->index = -1;
    L->cursor = NULL;
  }
  else{
    L->index--;
  }
  if(L->length == 1){
    L->front = L->back = NULL;
  }
  else{
    L->front = L->front->next;
  }
  L->length--;
  freeNode(&N);
}

// deleteBack()
// Delete the back element. Pre: length() > 0
void deleteBack(List L){
  if( L==NULL ){
    printf("List Error: calling deleteBack() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    printf("List Error: calling deleteBack() on empty List reference\n");
    exit(1);
  }
  Node N = NULL;
  N = L->back;
  if(L->index == L->length - 1){
    L->index = -1;
    L->cursor = NULL;
  }
  if(L->length == 1){
    L->front = L->back = NULL;
  }
  else{
    L->back = L->back->prev;
    L->back->next = NULL;
  }
  L->length--;
  freeNode(&N);
}

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L){
  if( L==NULL ){
    printf("List Error: calling delete() on NULL List reference\n");
    exit(1);
  }
  if( isEmpty(L) ){
    printf("List Error: calling delete() on empty List reference\n");
    exit(1);
  }
  if( L->index<0 ){
    printf("List Error: calling delete() when cursor is undefined\n");
    exit(1);
  }
  Node N = L->cursor;
  if(L->index == 0){
    deleteFront(L);
    return;
  }
  if(L->index == (L->length - 1)){
    deleteBack(L);
    return;
  }
  L->cursor->prev->next = L->cursor->next;
  L->cursor->next->prev = L->cursor->prev;
  //N = NULL;
  freeNode(&N);
  N = NULL;
  L->length--;
}

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0 
void set(List L, long x){
  if( L==NULL ){
      printf("List Error: calling set() on NULL List reference\n");
      exit(1);
   }
   L->cursor->data = x;
}


// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L){
  Node N = NULL;
   if( L==NULL ){
      printf("List Error: calling printList() on NULL List reference\n");
      exit(1);
   }
   for(N = L->front; N != NULL; N = N->next){
      fprintf(out, "%ld ", N->data);
   }
}

// copyList()
// returns a new List representing the same integer sequence as L. 
// The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged
List copyList(List L){
  List R = newList();
  Node N = NULL;
  for(N = L->front; N != NULL; N = N->next){
      append(R, N->data);
  }
  return R;
}
