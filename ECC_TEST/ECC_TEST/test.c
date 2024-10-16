#include <stdio.h>
#include <stdlib.h>
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

int main()
{
	test_add_sub();
	test_add_sub_mod();
	return 0;
}