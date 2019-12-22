//Ahlden Brough
//ajbrough
//pa3

#include<stdio.h>
#include<stdlib.h>
#include"BigInteger.h"

int main(int argc, char* argv[]){
	BigInteger A = stringToBigInteger("1000011111");
	BigInteger B = stringToBigInteger("1000011111");
	BigInteger C = stringToBigInteger("11000011111");
	printBigInteger(stdout, A);
	printBigInteger(stdout, B);
	printBigInteger(stdout, C);
	printf("equals(A, B) = %d\n", equals(A, B));
	printf("equals(A, C) = %d\n", equals(A, C));
	printf("compare(A, C) = %d\n", compare(A, C));
	printf("sign(A) = %d\n", sign(A));
	negate(B);
	printf("sign(B) = %d\n", sign(B));
	printf("equals(A, B) = %d\n", equals(A, B));
	printf("compare(A, B) = %d\n", compare(A, B));
	makeZero(B);
	printBigInteger(stdout, B);
	printf("sign(B) = %d\n", sign(B));
	BigInteger D = copy(A);
	printBigInteger(stdout, D);
	printf("equals(A, D) = %d\n", equals(A, D));
	BigInteger E = stringToBigInteger("000000001000000001");
	BigInteger F = stringToBigInteger("000000001000000001");
	BigInteger G = sum(E, F);
	BigInteger H = stringToBigInteger("000000000999999999");
	BigInteger I = sum(E, H);
	printBigInteger(stdout, E);
	printBigInteger(stdout, F);
	printBigInteger(stdout, G);
	printBigInteger(stdout, H);
	printBigInteger(stdout, I);
	add(F, E, H);
	printBigInteger(stdout, F);
	BigInteger J = stringToBigInteger("000000002000000001");
	BigInteger K = stringToBigInteger("000000001000000002");
	BigInteger L = diff(J, K);
	printBigInteger(stdout, L);
	BigInteger M = stringToBigInteger("000000001000000001");
	BigInteger N = stringToBigInteger("000000001000000001");
	BigInteger O = diff(M, N);
	printBigInteger(stdout, O);
	BigInteger AD = newBigInteger();
	subtract(AD, M, N);
	BigInteger P = stringToBigInteger("999999999");
	BigInteger Q = stringToBigInteger("000000000");
	BigInteger R = prod(P, Q);
	printBigInteger(stdout, P);
	printBigInteger(stdout, Q);
	printBigInteger(stdout, R);
	BigInteger S = stringToBigInteger("+111122223333");
	BigInteger T = stringToBigInteger("+222211110000");
	BigInteger U = newBigInteger();
	add(U, S, T);
	printBigInteger(stdout, U);
	printf("sign(U) = %d\n", sign(U));
	BigInteger V = stringToBigInteger("-111122223333");
	add(U, S, V);
	printBigInteger(stdout, U);
	BigInteger W = stringToBigInteger("-110122223333");
	add(U, S, W);
	printBigInteger(stdout, U);
	printf("sign(U) = %d\n", sign(U));


	BigInteger AA = stringToBigInteger("9163574346363325007361058");
    BigInteger AB = stringToBigInteger("+4597814412658653960738664");
    BigInteger AC = diff(AA, AB);
    printBigInteger(stdout, AC);
    printf("sign(AC) = %d\n", sign(AC));
    printf("compare(AA, AB) = %d\n", compare(AA, AB));


	BigInteger X = stringToBigInteger("-111122223333");
    BigInteger Y = stringToBigInteger("-110122223333");
    BigInteger Z = diff(X, Y);
    printBigInteger(stdout, Z);
	printf("sign(Z) = %d\n", sign(Z));
	printf("compare(X, Y) = %d\n", compare(X, Y));

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
	freeBigInteger(&AA);
	freeBigInteger(&AB);
	freeBigInteger(&AC);
	freeBigInteger(&AD);
	return(0);
}