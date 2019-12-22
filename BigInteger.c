//Ahlden Brough
//ajbrough
//pa3

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
#include"BigInteger.h"
#include"List.h"

int POWER = 9;
int BASE = 1000000000;

// Exported type -------------------------------------------------------------
// BigInteger reference type
typedef struct BigIntegerObj{
  int sign;
  List longs;
} BigIntegerObj;

// Constructors-Destructors ---------------------------------------------------
// newBigInteger()
// Returns a reference to a new BigInteger object in the zero state. 
BigInteger newBigInteger(){
  //printf("starts newBigInteger\n");
  BigInteger B;
  B = malloc(sizeof(BigIntegerObj));
  B->sign = 0;
  B->longs = malloc(sizeof(List));
  B->longs = newList();
  return B;
}

// freeBigInteger()
// Frees heap memory associated with *pN, sets *pN to NULL. 
void freeBigInteger(BigInteger* pN){
  if( pN!=NULL && *pN!=NULL ){
      freeList(&(*pN)->longs); //might need more than this
      free(*pN);
      *pN = NULL;
    }
}
//private functions ------------------------------------------------------------
long expo (long x,long n){
    int i;
    long number = 1;

    for (i = 0; i < n; ++i){
      number = number * x;
    }

    return number;
}

//returns a normalize version of 
void normalize(BigInteger A){
  //getting rid of the overflows
  //printf("length(A->longs) = %d\n", length(A->longs));
  moveFront(A->longs);
  while(index(A->longs) > -1){
    if(get(A->longs) > 0){
      break;
    }
    moveNext(A->longs);
  }
  if(index(A->longs) == -1){
    moveFront(A->longs);
    long get_A;
    while(index(A->longs) > -1){
      get_A = get(A->longs);
      set(A->longs, get_A * -1);
      moveNext(A->longs);
    }
    A->sign = -1;
    return;
  }
  moveFront(A->longs);
  while(index(A->longs) > -1){
   // printf("normalize first while loop iterates\n");
    long carry = 0;
    int len = snprintf( NULL, 0, "%ld", get(A->longs));
    //printf("len = %d for index %d\n", len, index(A->longs));
    long get_A = get(A->longs);
    //printf("get_A = %ld\n", get_A);
    //printf("get(A->longs) = %ld\n", get(A->longs));
    if(len > POWER && get(A->longs) > 0){
      //printf("first if get_A = %ld\n", get_A);
      //printf("len = %d\n", len);
      //printf("index %d requires carry\n", index(A->longs));
      carry += get_A/expo(10, POWER);
      //printf("carry = %ld\n", carry);
      // while(len > POWER){
      //   printf("carry = %d\n", carry);
      set(A->longs, get_A % expo(10, POWER));
      //   carry++;
      //   len = snprintf( NULL, 0, "%ld", get(A->longs));
      //   get_A = get(A->longs);
      // }
    }
    else if(get(A->longs) < 0){
      //printf("gets to correct if\n");
      long get_A = get(A->longs);
      if(index(A->longs) != length(A->longs) - 1){
        //printf("get_A = %ld\n", get_A);
        set(A->longs, get_A + expo(10, POWER));
        //printf("adds 10^POWER\n");
      }
      carry = -1;
      //printf("after set = %ld\n", get(A->longs));
    }
    moveNext(A->longs);
    if(index(A->longs) > -1){
      get_A = get(A->longs);
      //printf("get_A = %ld at index = %d\n", get_A, index(A->longs));
      set(A->longs, get_A + carry);
    }
    else if(carry > 0 && index(A->longs) == -1){
      append(A->longs, carry);
    }
    else if(carry == -1 && index(A->longs) == -1){
      A->sign = -1;
      moveBack(A->longs);
      get_A = get(A->longs);
      set(A->longs, get_A * -1);
      break;
    }
  }
  //getting rid of negatives
  moveBack(A->longs);
  while(index(A->longs) > -1){
    //printf("normalize second while loop iterates index = %d\n", index(A->longs));
    if(get(A->longs) < -1){
      long get_A = get(A->longs);
      set(A->longs, get_A + 100);
      //printf("after set = %ld\n", get(A->longs));
    }
    movePrev(A->longs);
  }
  while(back(A->longs) == 0 && length(A->longs) > 1){
    deleteBack(A->longs);
  }
}

BigInteger scalarMult(BigInteger A, long x, int zeros){
  // printf("-----------------\n");
  // printf("starts scalarMult\n");
  BigInteger N = newBigInteger();
  moveFront(A->longs);
  long get_A = 0;
  while(index(A->longs) > -1){
    //printf("scalarMult index(A->longs) = %d\n", index(A->longs));
    get_A = get(A->longs);
    //printf("get_A = %ld\n", get_A);
    append(N->longs, get_A * x);
    //printf("appended\n");
    moveNext(A->longs);
    //printf("moved next\n");
  }
  //printf("exits while loop\n");
  int count = 0;
  while(count < zeros){
    //printf("count = %d\n", count);
    prepend(N->longs, 0);
    count++;
  }
  //printf("finishes adding zeros\n");
  //printBigInteger(stdout, N);

  //moveFront(N->longs);
  // while(index(N->longs) > -1){
  //   //printf("index %d = %ld\n", index(N->longs), get(N->longs));
  //   moveNext(N->longs);
  // }
  normalize(N);
  //printf("normalizes\n");
  //moveFront(N->longs);
  // while(index(N->longs) > -1){
  //   //printf("index %d = %ld\n", index(N->longs), get(N->longs));
  //   moveNext(N->longs);
  // }
  //printBigInteger(stdout, N);
  //printf("-----------------\n");
  return N;

}

// Access functions -----------------------------------------------------------

// sign()
// Returns -1 if N is negative, 1 if N is positive, and 0 if N is in the zero 
// state.
int sign(BigInteger N){
  if(N == NULL){
    printf("BigInteger Error: calling sign() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  return N->sign;
}

// compare()
// Returns -1 if A<B, 1 if A>B, and 0 if A=B. 
int compare(BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling compare() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  int x = 1;
  if(sign(A) > sign(B)){
    return 1;
  }
  else if(sign(A) < sign(B)){
    return -1;
  }
  if(sign(A) == -1 && sign(B) == -1){
    x = -1;
  }
  if(length(A->longs) > length(B->longs)){
    return 1 * x;
  }
  else if(length(A->longs) < length(B->longs)){
    return -1 * x;
  }
  if(length(A->longs) != 0 && length(B->longs) != 0){
    moveBack(A->longs);
    moveBack(B->longs);
  }
  while(index(A->longs) > -1){
    if(get(A->longs) > get(B->longs)){
      return 1 * x;
    }
    else if(get(A->longs) < get(B->longs)){
      return -1 * x;
    }
    else{
      movePrev(A->longs);
      movePrev(B->longs);
    }
  }
  return 0;
}

// equals()
// Return true (1) if A and B are equal, false (0) otherwise. 
int equals(BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling equals() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  int eq = 0;
  eq = ( length(A->longs) == length(B->longs) && sign(A) == sign(B));
  moveFront(A->longs);
  moveFront(B->longs);
  while( eq && index(A->longs) > -1){
    eq = (get(A->longs) == get(B->longs));
    moveNext(A->longs);
    moveNext(B->longs);
  }
  return eq;
}

// Manipulation procedures ----------------------------------------------------
// makeZero()
// Re-sets N to the zero state.
void makeZero(BigInteger N){
  if(N == NULL){
    printf("BigInteger Error: calling makeZero() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  if(length(N->longs) != 0){
    for(int i = 0; i < length(N->longs) - 1; i++){
      deleteFront(N->longs);
    }
    moveFront(N->longs);
    set(N->longs, 0);
  }
  else if(length(N->longs) == 0){
    append(N->longs, 0);
  }
  N->sign = 0;
}

// negate()
// Reverses the sign of N: positive <--> negative. Does nothing if N is in the 
// zero state.
void negate(BigInteger N){
  if(N == NULL){
    printf("BigInteger Error: calling negate() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  N->sign = N->sign * -1;
}

// BigInteger Arithmetic operations -----------------------------------------------

// stringToBigInteger()
// Returns a reference to a new BigInteger object representing the decimal integer
// represented in base 10 by the string s. 
// Pre: s is a non-empty string containing only base ten digits {0,1,2,3,4,5,6,7,8,9}
// and an optional sign {+, -} prefix. 
BigInteger stringToBigInteger(char* s){
  //printf("starts stringToBigInteger\n");
  if(strlen(s) == 0){
    printf("BigInteger Error: calling stringToBigInteger() on an empty string\n");
    exit(EXIT_FAILURE);
  }
  BigInteger N = newBigInteger();
  //printf("starts stringToBigInteger\n");
  
  //finding where the start of the number is
  int start = 0;
  while(s[start] == '+' || s[start] == '-' || s[start] == '0'){
    start++;
  }
  if(start == strlen(s)){
    makeZero(N);
    return N;
  }
  //printf("start = %d\n", start);
  //making a new number that doesn't have any leading zeros or signs
  char copy_s[strlen(s) - (start) + 1]; // +1 bc start is an index and -1 for \0
  //printf("strlen(s) - (start) + 1 = %ld\n", strlen(s) - (start) + 1);
  //memset( copy_s, '\0', sizeof(copy_s) );
  copy_s[strlen(s) - (start)] = '\0';
  //printf("last char in copy_s = %c\n", copy_s[strlen(s) - (start)]);
  //printf("copy_s = %s\n", copy_s);
  int s_index = start;
  for(int b = 0; b < strlen(s) - (start); b++){
    copy_s[b] = s[s_index];
    //printf("s[s_index] = %c\n", s[s_index]);
    s_index++;
  }
  //printf("copy_s = %s\n", copy_s);
  //strncopy(copy_s, s, )
  
  //creating longs for insertion into N->longs
  int location = strlen(copy_s) - 1;
  //printf("location = %d\n", location);
  //printf("strlen(copy_s) = %ld\n", strlen(copy_s));
  //printf("ceiling = %d\n", (int)ceil(strlen(copy_s)/POWER));
  for(int a = 0; a < (int)ceil(strlen(copy_s)/POWER); a++){
    long new_entry = 0;
    //printf("gets inside loop\n");
    char entry[POWER+1];
    for(int i = POWER - 1; i >= 0; i--){
      //printf("starts inside loop\n");
      entry[i] = copy_s[location];
      //printf("---------------\n");
      //printf("i = %d\n", i);
      //printf("location = %d\n", location);
      //printf("entry[i] = %c\n", entry[i]);
      //printf("---------------\n");
      location--;
      //printf("gets past decrementing location\n"); 
      //printf("location = %d\n", location);
    }
    //printf("exits inside loop\n");
    entry[POWER] = '\0';
    //printf("entry[POWER] = %c\n", entry[POWER]);
    //printf("entry = %s\n", entry);
    int char_to_int;

    for(int w = 0; w < POWER; w++){
      //printf("attempts iteration %d\n", w);
      char_to_int = entry[w] - '0';
      new_entry = new_entry + (long)(char_to_int * ( expo(10, ((POWER-1) - w)) ));
      //printf("new_entry = %ld\n", new_entry);
    }
    //printf("new_entry = %ld\n", new_entry);
    append(N->longs, (long)new_entry);
    //printf("gets past appending");
  }

  //getting last numbers that werent included in the previous for loop. example first for loop will get 11/9 which will be the back 9 numbers then second will get 11%9 which will be the remaining 2
  //making entry
  long new_entry = 0;
  if((int)ceil(strlen(copy_s)%POWER) != 0){
    char entry[(int)ceil(strlen(copy_s)%POWER)+1];
    int z;
    for(z = 0; z < (int)ceil(strlen(copy_s)%POWER); z++){
     // printf("location = %d\n", location);
      entry[z] = copy_s[location];
     // printf("entry[%d] = %c\n", z, entry[z]);
      location--;
    }
    //changing entry to long and appending
    int char_to_int;
    for(int w = 0; w < z; w++){
      //printf("attempts iteration %d\n", w);
      char_to_int = entry[w] - '0';
      //printf("new_entry before = %ld\n", new_entry);
      //printf("char_to_int = %d\n", char_to_int);
      //printf("w = %d\n", w);
      new_entry = new_entry + (long)(char_to_int * ( expo(10, w )));
      //printf("new_entry = %ld\n", new_entry);
    }
    //printf("new_entry after for loop = %ld\n", new_entry);
    append(N->longs, (long)new_entry);
    //printf("gets past appending");
  }
  //assigning sign
  if(s[0] == '-'){
    N->sign = -1;
  }
  else if(s[0] == '+'){
    N->sign = 1;
  }
  else{
    int positive = 0;
    moveFront(N->longs);
    while(index(N->longs) > -1){
      if(get(N->longs) != 0){
        positive = 1;
        break;
      }
      moveNext(N->longs);
    }
    if(positive == 1){
      N->sign = 1;
    }
  }
  return N;
}

// copy()
// Returns a reference to a new BigInteger object in the same state as N.
BigInteger copy(BigInteger N){
  if(N == NULL){
    printf("BigInteger Error: calling copy() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  BigInteger B = newBigInteger();
  B->longs = copyList(N->longs);
  B->sign = N->sign;
  return B;
}

// add()
// Places the sum of A and B in the existing BigInteger S, overwriting its 
// current state: S = A + B
void add(BigInteger S, BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  makeZero(S);
  BigInteger N = sum(A, B);
  S->longs = copyList(N->longs);
  S->sign = N->sign;
  freeBigInteger(&N);
}

// sum()
// Returns a reference to a new BigInteger object representing A + B. 
BigInteger sum(BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling add() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  BigInteger N = newBigInteger();
  // if(length(A->longs == 0) && length(B->longs) != 0){
  //   return N;
  // }
  if(sign(A) != -1 && sign(B) == -1){
    negate(B);
    N = diff(A, B);
    negate(B);
    return N;
  }
  else if(sign(A) == -1 && sign(B) != -1){
    //printf("sign(A) == -1 && sign(B) != -1\n");
    negate(A);
    if(compare(A, B) == 1){
      N = diff(A, B);
      N->sign = -1;
    }
    else{
      N = diff(B, A);
    }
    negate(A);
    return N;
  }
  else{
    moveFront(A->longs);
    moveFront(B->longs);
    while(index(A->longs) > -1 && index(B->longs) > -1){
      long A_get = get(A->longs);
      long B_get = get(B->longs);
      append(N->longs, A_get + B_get);
      moveNext(A->longs);
      moveNext(B->longs);
    }
    if(index(A->longs) == -1 && index(B->longs) != -1){
      //printf("case 3\n");
      while(index(B->longs) > -1){
        //printf("case 3 while loop iterates\n");
        long B_get = get(B->longs);
        append(N->longs, B_get);
        moveNext(B->longs);
      }
    }
    else if(index(A->longs) != -1 && index(B->longs) == -1){
      //printf("case 4\n");
      while(index(A->longs) > -1){
        //printf("case 4 while loop iterates\n");
        long A_get = get(A->longs);
        append(N->longs, A_get);
        moveNext(A->longs);
      }
    }
  }
  moveFront(N->longs);
  if(length(N->longs) == 1 && get(N->longs) == 0){
    N->sign = 0;
  }
  else if(sign(A) == 1 && sign(B) == 1){
    N->sign = 1;
  }
  else if(sign(A) == -1 && sign(B) == -1){
    N->sign = -1;
  }
  normalize(N);
  return N;
}

// subtract()
// Places the difference of A and B in the existing BigInteger D, overwriting 
//itscurrentstate: D=A-B
void subtract(BigInteger D, BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling subtract() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  makeZero(D);
  BigInteger N = diff(A, B);
  D->longs = copyList(N->longs);
  D->sign = N->sign;
  freeBigInteger(&N);
}

// diff()
// Returns a reference to a new BigInteger object representing A - B. 
BigInteger diff(BigInteger A, BigInteger B){
  //printf("starts diff");
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling diff() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  BigInteger N = newBigInteger();
  if(A == B){
    makeZero(N);
    return N;
  }
  if(compare(A, B) == 0){
    //printf("compare(A, B) == 0\n");
    makeZero(N);
    return N;
  }
  else if(sign(A) == -1 && sign(B) == -1 && compare(A, B) == 1){ //first is bigger
    //printf("sign(A) == -1 && sign(B) == -1 && compare(A, B) == 1\n");
    negate(A);
    negate(B);
    N = diff(B, A);
    N->sign = 1;
    negate(A);
    negate(B);
    return N;
  }
  else if(sign(A) == -1 && sign(B) == -1 && compare(A, B) == -1){
    //printf("sign(A) == -1 && sign(B) == -1 && compare(A, B) == -1\n");
    negate(A);
    negate(B);
    N = diff(A, B);
    N->sign = -1;
    negate(A);
    negate(B);
    return N;
  }
  else if(sign(A) == 1 && sign(B) == -1){
    //printf("\n");
    //printf("sign(A) == 1 && sign(B) == -1\n");
    negate(B);
    N = sum(A, B);
    negate(B);
    return N;
  }
  else if(sign(A) == -1 && sign(B) == 1){
    //printf("sign(A) == -1 && sign(B) == 1\n");
    negate(A);
    N = sum(A, B);
    negate(A);
    N->sign = -1;
    return N;
  }
  else if(sign(A) == 1 && sign(B) == 1 && compare(A, B) == -1){
    //printf("sign(A) == 1 && sign(B) == 1 && compare(A, B) == -1\n");
    N = diff(B, A);
    N->sign = -1;
    return N;
  }
  //printf("gets past all the ifs\n");
  moveFront(A->longs);
  moveFront(B->longs);
  while(index(A->longs) > -1 && index(B->longs) > -1){
    long A_get = get(A->longs);
    long B_get = get(B->longs);
    append(N->longs, A_get - B_get);
    //printf("appending %ld\n", A_get - B_get);
    moveNext(A->longs);
    moveNext(B->longs);
  }
  if(index(A->longs) == -1 && index(B->longs) != -1){
    //printf("case 3\n");
    while(index(B->longs) > -1){
      //printf("case 3 while loop iterates\n");
      long B_get = get(B->longs);
      append(N->longs, B_get * -1);
      //printf("appending %ld\n", B_get * -1);
      moveNext(B->longs);
    }
  }
  else if(index(A->longs) != -1 && index(B->longs) == -1){
    //printf("case 4\n");
    while(index(A->longs) > -1){
      //printf("case 4 while loop iterates\n");
      long A_get = get(A->longs);
      append(N->longs, A_get);
      //printf("appending %ld\n", A_get);
      moveNext(A->longs);
    }
  }
  N->sign = 1;
  normalize(N); // need to fix the subtracting part of normalize to have a negative carry
  return N;
}

// multiply()
// Places the product of A and B in the existing BigInteger P, overwriting // its current state: P = A*B
void multiply(BigInteger P, BigInteger A, BigInteger B){
  if(A == NULL || B == NULL){
    printf("BigInteger Error: calling multiply() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  makeZero(P);
  BigInteger N = prod(A, B);
  P->longs = copyList(N->longs);
  P->sign = N->sign;
  freeBigInteger(&N);
}

// prod()
// Returns a reference to a new BigInteger object representing A*B 
BigInteger prod(BigInteger A, BigInteger B){
  // printf("running prod on ");
  // printBigInteger(stdout, A);
  // printf("and ");
  // printBigInteger(stdout, B);
  BigInteger N = newBigInteger();
  makeZero(N);
  if(A == B){
    BigInteger C = copy(A);
    N = prod(A, C);
    freeBigInteger(&C);
    return N;
  }
  if(sign(A) == 0 || sign(B) == 0){
    return N;
  }
  BigInteger copy_A = copy(A);
  moveFront(B->longs);
  while(index(B->longs) > -1){
      long B_get = get(B->longs);
      BigInteger help = scalarMult(copy_A, B_get, index(B->longs));
      N = sum(N, help);
      freeBigInteger(&help);
    moveNext(B->longs);
  }
  if((sign(A) == 1 && sign(B) == -1) || (sign(A) == -1 && sign(B) == 1)){
    N->sign = -1;
  }
  else{
    N->sign = 1;
  }
  freeBigInteger(&copy_A);
  normalize(N);
  return N;
}

// Other operations -----------------------------------------------------------
// printBigInteger()
// Prints a base 10 string representation of N to filestream out. 
void printBigInteger(FILE* out, BigInteger N){
  if(N == NULL){
    printf("BigInteger Error: calling printBigInteger() on NULL BigInteger reference\n");
    exit(EXIT_FAILURE);
  }
  moveBack(N->longs);
  if(N->sign == -1){
    fprintf(out, "-");
  }
  for(int i = 0; i < length(N->longs); i++){
    int len = snprintf( NULL, 0, "%ld", get(N->longs));
    if(len != POWER && index(N->longs) != length(N->longs) - 1){
      fprintf(out, "%0*ld", POWER, get(N->longs));
    }
    else{
      fprintf(out, "%0ld", get(N->longs));
    }
    movePrev(N->longs);
  }
  fprintf(out, "\n");
}
