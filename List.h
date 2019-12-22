//Ahlden Brough
//ajbrough
//pa3

#ifndef _LIST_H_INCLUDE_
#define _LIST_H_INCLUDE_
#include<stdio.h>


// Exported type --------------------------------------------------------------
typedef struct ListObj* List;


// Constructors-Destructors ---------------------------------------------------

// newList()
// Returns reference to new empty List object. 
List newList(void);

// freeList()
// Frees all heap memory associated with List *pL, and sets *pL to NULL.
void freeList(List* pL);


// Access functions -----------------------------------------------------------

// length()
// Returns the length of L.
int length(List L);

// index()
// Returns index of cursor element if defined, -1 otherwise
int index(List L);

// front()
// Returns the value at the front of L.
// Pre: !isEmpty(L)
long front(List L);

// back ()
// Returns the value at the back of L.
// Pre: !isEmpty(L)
long back(List L);

// get()
// Returns cursor element of L. 
// Pre: length()>0, index()>=0
long get(List L);

// isEmpty()
// Returns true (1) if L is empty, otherwise returns false (0)
int isEmpty(List L);


// Manipulation procedures ----------------------------------------------------

// clear()
// Resets L to its original empty state
void clear(List L);

// moveFront()
// If L is non-empty, sets cursor under the front element, otherwise does nothing.
void moveFront(List L);

// moveBack()
// If L is non-empty, sets cursor under the back element, otherwise does nothing.
void moveBack(List L);

// movePrev()
// If cursor is defined and not at front, move cursor one step toward the front of L; 
// if cursor is defined and at front, cursor becomes undefined; if cursor is undefined do nothing
void movePrev(List L);

// moveNext()
// If cursor is defined and not at front, move cursor one step toward the back of L; 
// if cursor is defined and at back, cursor becomes undefined; if cursor is undefined do nothing
void moveNext(List L);

// prepend()
// Insert new element into L. If L is non-empty, insertion takes place before front element.
void prepend(List L, long data);

// append()
// Insert new element into L. If L is non-empty, insertion takes place after back element.
void append(List L, long data);

// insertBefore
// insert new element before cursor.
// Pre: length() > 0, index() >= 0
void insertBefore(List L, long data);

// insertAfter
// insert new element after cursor.
// Pre: length() > 0
void insertAfter(List L, long data);

// deleteFront()
// Delete the front element. Pre: length() > 0
void deleteFront(List L);

// deleteBack()
// Delete the back element. Pre: length() > 0
void deleteBack(List L);

// delete()
// Delete cursor element, making cursor undefined.
// Pre: length() > 0, index() >= 0
void delete(List L);

// set()
// Overwrites the cursor element with x. Pre: length()>0, index()>=0 
void set(List L, long x);


// Other Functions ------------------------------------------------------------

// printList()
// Prints to the file pointed to by out, a string representation of L consisting of a space separated sequence of integers, with front on left.
void printList(FILE* out, List L);

// copyList()
// returns a new List representing the same integer sequence as L. 
// The cursor in the new list is undefined, regardless of the state of the cursor in L. The state of L is unchanged
List copyList(List L);

#endif

