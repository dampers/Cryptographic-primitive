#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"


// ctrl + f5 : 실행
// ctrl + f10 : 커서까지 디버깅 실행
// shift + f5 : 디버깅 종료

int main()
{
	mpz_t a, b, c;

	mpz_init(a);
	mpz_init(b);
	mpz_init(c);

	a->_mp_d[0] = 0xffffffff;
	a->_mp_size = 1;

	b->_mp_d[0] = 0xfffffffe;
	b->_mp_size = 1;

	mpz_mul(c, a, b);


	for (int i = 0; i < c->_mp_size; i++)
		printf("%08x", c->_mp_d[i]);
	
	//mpz_powm()
	//mpz_invert()?
	

	/*mpz_init_set_str(a, "12345678987654321", 10);
	mpz_init_set_str(b, "-98765432123456789", 10);
	
	mpz_swap(a, b);*/

	

	mpz_clear(a);
	mpz_clear(b);

	return 0;
}