//Ahlden Brough
//ajbrough
//pa3

#include<stdio.h>
#include<stdlib.h>
#include"List.h"

int main(int argc, char* argv[]){
	List A = newList();
	List B = newList();
	long i;

   	for(i=1; i<=20; i++){
      append(A,i);
      prepend(B,i);
   	}

   	printf("length(A) = %d\n", length(A));
   	printf("length(B) = %d\n", length(B));
   	printf("front(A) = %ld\n", front(A));
   	printf("front(B) = %ld\n", front(B));
   	moveFront(A);
   	moveFront(B);
   	moveNext(A);
   	moveNext(B);
   	printf("get(A) = %ld\n", get(A));
   	printf("get(B) = %ld\n", get(B));
   	moveBack(A);
   	moveBack(B);
   	printf("get(A) = %ld\n", get(A));
   	printf("get(B) = %ld\n", get(B));
   	insertBefore(A, 100);
   	insertAfter(B, 100);
   	deleteFront(A);
   	deleteFront(B);
   	deleteBack(A);
   	deleteBack(A);
   	printf("length(A) = %d\n", length(A));
   	printf("length(B) = %d\n", length(B));
   	printf("front(A) = %ld\n", front(A));
   	printf("front(B) = %ld\n", front(B));
   	printf("back(A) = %ld\n", back(A));
   	printf("back(B) = %ld\n", back(B));

	return(0);
}