#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "ecc.h"
#include "gmp.h"

#define TEST_SIZE 100000

void test_add_sub()
{
	int i;
	mpz_t a, b, c, p;
	ECC_BN A, B, C, temp;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(p);
	ECC_ecc_bn_to_mpz(p, &prime_p256);

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, a);

		mpz_add(c, a, b);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_add(&C, &A, &B);

		ECC_mpz_to_ecc_bn(&temp, c);
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at addition %d\n", i);
			return;
		}
	}

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, a);

		mpz_sub(c, a, b);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_sub(&C, &A, &B);

		ECC_mpz_to_ecc_bn(&temp, c);
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at subtraction %d\n", i);
			return;
		}
	}

	printf("success test_add_sub\n");
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(p);
	gmp_randclear(state);

}

void test_add_sub_mod()
{
	int i;
	mpz_t a, b, c, p;
	ECC_BN A, B, C, temp;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(p);
	ECC_ecc_bn_to_mpz(p, &prime_p256);

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, p);
		//mpz_set_ui(a, i);
		//mpz_set_ui(b, i);

		mpz_add(c, a, b);
		mpz_mod(c, c, p);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_add_mod(&C, &A, &B, &prime_p256);

		ECC_mpz_to_ecc_bn(&temp, c);
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at modular addition %d\n", i);
			return;
		}
	}

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, p);

		mpz_sub(c, a, b);
		mpz_mod(c, c, p);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_sub_mod(&C, &A, &B, &prime_p256);

		ECC_mpz_to_ecc_bn(&temp, c);
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at modular subtraction %d\n", i);
			return;
		}
	}

	printf("success test_add_sub_mod\n");
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(p);
	gmp_randclear(state);
}

void test_mul()
{
	int i;
	mpz_t a, b, c, p;
	ECC_BN A, B, C, temp;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(p);
	ECC_ecc_bn_to_mpz(p, &prime_p256);

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, p);

		a->_mp_size = a->_mp_d[0] % 9;
		b->_mp_size = b->_mp_d[0] % 9;
		mpz_mul(c, a, b);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_mul(&C, &A, &B);

		ECC_mpz_to_ecc_bn(&temp, c);
		//printf("%d %d\n", C.len, temp.len);
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at multiple %d\n", i);
			return;
		}
	}

	printf("success test_mul\n");
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(p);
	gmp_randclear(state);
}

void test_mod_p256()
{
	int i;
	//int j;
	mpz_t a, b, c, p;
	ECC_BN A, B, C, temp;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(a);
	mpz_init(b);
	mpz_init(c);
	mpz_init(p);
	ECC_ecc_bn_to_mpz(p, &prime_p256);

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_urandomm(b, state, p);

		mpz_mul(c, a, b);
		mpz_mod(c, c, p);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_mpz_to_ecc_bn(&B, b);
		ECC_bn_mul(&C, &A, &B);
		ECC_bn_mod_p256(&C, &C);
		ECC_mpz_to_ecc_bn(&temp, c);
		//printf("%d %d\n", C.len, temp.len);
		//for (j = 0; j < C.len; j++)
		//	printf("%u ", C.dat[j]);
		//printf("\n");

		//for (j = 0; j < C.len; j++)
		//	printf("%u ", temp.dat[j]);
		//printf("\n");
		if (ECC_bn_cmp(&C, &temp))
		{
			printf("fail at mod %d\n", i);
			return;
		}
	}

	printf("success test mod \n");
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(c);
	mpz_clear(p);
	gmp_randclear(state);
}


void validtest_binary_inv()
{
	int i;
	int j;
	mpz_t a, b, p;
	ECC_BN A, B, temp;
	gmp_randstate_t state;
	gmp_randinit_default(state);
	mpz_init(a);
	mpz_init(b);
	mpz_init(p);
	ECC_ecc_bn_to_mpz(p, &prime_p256);

	for (i = 0; i < TEST_SIZE; i++)
	{
		mpz_urandomm(a, state, p);
		mpz_invert(b, a, p);
		ECC_mpz_to_ecc_bn(&A, a);
		ECC_bn_binary_inv(&B, &A);
		ECC_mpz_to_ecc_bn(&temp, b);

		if (ECC_bn_cmp(&B, &temp))
		{
			printf("fail inversion at %d\n", i);
			return;
		}
	}

	printf("success inversion \n");
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(p);
	gmp_randclear(state);
}

 static void performance_test()
{
	/*
	* performance test of 
	* ECC_bn_add_mod
	* ECC_bn_sub_mod
	* ECC_bn_mul
	* ECC_bn_mod_p256
	* ECC_bn_binary_inv
	*/

	clock_t start, end;
	int i;
	ECC_BN A, B, C;
	mpz_t a, b, p;
	gmp_randstate_t state;
	gmp_randinit_default(state);

	mpz_init(a);
	mpz_init(b);
	mpz_init(p);

	ECC_ecc_bn_to_mpz(p, &prime_p256);
	mpz_urandomm(a, state, p);
	mpz_urandomm(b, state, p);
	ECC_mpz_to_ecc_bn(&A, a);
	ECC_mpz_to_ecc_bn(&B, b);

	// ECC_bn_add_mod
	start = clock();
	for (i = 0; i < TEST_SIZE; i++)
	{
		ECC_bn_add_mod(&C, &A, &B, &prime_p256);
	}
	end = clock();
	printf("ECC bn add mod time  : %lf\n", ((double)end - start));
	
	// ECC_bn_sub_mod
	start = clock();
	for (i = 0; i < TEST_SIZE; i++)
	{
		ECC_bn_sub_mod(&C, &A, &B, &prime_p256);
	}
	end = clock();
	printf("ECC bn sub mod time  : %lf\n", ((double)end - start));

	// ECC_bn_add_mul
	start = clock();
	for (i = 0; i < TEST_SIZE; i++)
	{
		ECC_bn_mul(&C, &A, &B);
	}
	end = clock();
	printf("ECC bn mul time : %lf\n", ((double)end - start));

	// ECC_bn_mod p256
	start = clock();
	ECC_bn_mul(&A, &A, &B);
	for (i = 0; i < TEST_SIZE; i++)
	{
		ECC_bn_mod_p256(&C, &A);
	}
	end = clock();
	printf("ECC bn mod p256 time : %lf\n", ((double)end - start));

	// ECC_bn_binary inversion
	start = clock();
	for (i = 0; i < TEST_SIZE; i++)
	{
		ECC_bn_binary_inv(&C, &B);
	}
	end = clock();
	printf("ECC bn binary inversion time : %lf\n", ((double)end - start));
	
	mpz_clear(a);
	mpz_clear(b);
	mpz_clear(p);
	gmp_randclear(state);
}

int main()
{
	test_add_sub();
	/*test_add_sub();
	test_add_sub_mod();*/
	//test_mul();
	//test_mod_p256();
	validtest_binary_inv();
	performance_test();
	return 0;
}