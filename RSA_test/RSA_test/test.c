#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"

int main()
{
	gmp_randstate_t state;
	gmp_randinit_default(state);

	// ���� ����
	mpz_t p, q, n, e, d;
	mpz_init(p); mpz_init(q); mpz_init(n); mpz_init(e); mpz_init(d);

	// Ű ����

	// 1. e=65537
	e->_mp_d[0] = 0x10001;
	e->_mp_size = 1;
	mpz_set_ui(e, 0x10001);

	// 2. p, q�� 1024��Ʈ ���� �Ҽ�
	// 1024 ��Ʈ���� �����ؾ��� -> MSB masking
	// ¦�� �� -> LSB masking
	
	mpz_urandomb(p, state, 1024);
	while (1)
	{
		if (p->_mp_size < 32) continue;
		p->_mp_d[31] |= 0x80000000;
		p->_mp_d[ 0] &= 0xFFFFFFFE;

		mpz_gcd(n, p, e);
		if ((n->_mp_size != 1) || (n->_mp_d[0] != 1)) continue;

		p->_mp_d[ 0] |= 0x00000001;
		if (mpz_probab_prime_p(p, 56)) break;
		mpz_add_ui(p, p, 2);
	}

	// 3. n = p * q

	// 4. d = e^{-1} mod phi(n)

	// 5. �޽��� ���� : m

	// 6. enc

	// 7. dec
	
	// �׽�Ʈ 

	// ���� ����
	mpz_clear(p); mpz_clear(q); mpz_clear(n); mpz_clear(e); mpz_clear(d);
	gmp_randclear(state);

	return 0;
}