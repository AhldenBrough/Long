//Ahlden Brough
//ajbrough
//pa3

#include<stdio.h>
#include<stdlib.h>
#include "BigInteger.h"

int main(int argc, char* argv[]){
	FILE *in, *out;
	int a;
	int b;
	// check command line for correct number of arguments
    if( argc != 3 ){
      printf("Usage: Arithmetic <input file> <output file>\n");
      exit(1);
    }
    //printf("1\n");
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if( in==NULL ){
      printf("Unable to open file %s for reading\n", argv[1]);
      exit(1);
    }
    if( out==NULL ){
      printf("Unable to open file %s for writing\n", argv[2]);
      exit(1);
    }
    //printf("2\n");
    fscanf(in, "%d", &a);
    char a_string[a+2];
    fscanf(in, "%s", &a_string);
    BigInteger A = stringToBigInteger(a_string);
    //printf("3\n");
    fscanf(in, "%d", &b);
    char b_string[b+2];
    fscanf(in, "%s", &b_string);
    BigInteger B = stringToBigInteger(b_string);
    //printf("4\n");
    //A
    printBigInteger(out, A);
    fprintf(out, "\n");
    //printf("5\n");
    //B
    printBigInteger(out, B);
    fprintf(out, "\n");
    //printf("6\n");
    //A + B
    BigInteger C = sum(A, B);
    printBigInteger(out, C);
    fprintf(out, "\n");
    //printf("7\n");
    //A - B
	BigInteger D = diff(A, B);
    printBigInteger(out, D);
    fprintf(out, "\n");
    //printf("8\n");
    //A-A
    BigInteger E = diff(A, A);
    printBigInteger(out, E);
    fprintf(out, "\n");
    //printf("9\n");
    //3A-2B
    BigInteger F = stringToBigInteger("3");
	//printf("-------------\n");
    //printBigInteger(stdout, F);
    BigInteger G = prod(A, F);
    //printBigInteger(stdout, G);
    BigInteger H = stringToBigInteger("2");
    //printBigInteger(stdout, H);
    BigInteger I = prod(B, H);
    //printBigInteger(stdout, I);
    //printf("diff on ");
    //printBigInteger(stdout, G);
    //printf("and ");
    //printBigInteger(stdout, I);
    //printf("sign(F) (2) = %d\n", sign(F));
    //printf("sign(B) = %d\n", sign(B));
    //printf("sign(G) (3A) = %d, sign(I) (2B) = %d\n", sign(G), sign(I));
    BigInteger J = diff(G, I);
    printBigInteger(out, J);
    fprintf(out, "\n");
    //printf("10\n");
    //printf("-------------\n");
    //AB
    //-304146513730276293
    BigInteger K = prod(A, B);
    printBigInteger(out, K);
    fprintf(out, "\n");
    //printf("11\n");
    //A^2
    BigInteger L = prod(A, A);
    printBigInteger(out, L);
    fprintf(out, "\n");
    //printf("12\n");
	//B^2
    BigInteger M = prod(B, B);
    printBigInteger(out, M);
    fprintf(out, "\n");
    //printf("13\n");
    //9A^4 + 16B^5
    BigInteger N = stringToBigInteger("9");
    BigInteger O = prod(L, L);
    BigInteger P = stringToBigInteger("16");
    BigInteger Q = prod(N, O);
    BigInteger R = prod(M, M);
    BigInteger S = prod(B, R);
    BigInteger T = prod(P, S);
    BigInteger U = sum(Q, T);
    printBigInteger(out, U);
    freeBigInteger(&A);
    freeBigInteger(&B);
    freeBigInteger(&C);
    freeBigInteger(&D);
    freeBigInteger(&E);
    freeBigInteger(&F);
    freeBigInteger(&G);
    freeBigInteger(&H);
    freeBigInteger(&I);
    freeBigInteger(&J);
    freeBigInteger(&K);
    freeBigInteger(&L);
    freeBigInteger(&M);
    freeBigInteger(&N);
    freeBigInteger(&O);
    freeBigInteger(&P);
    freeBigInteger(&Q);
    freeBigInteger(&R);
    freeBigInteger(&S);
    freeBigInteger(&T);
    freeBigInteger(&U);
    //printf("14\n");
}