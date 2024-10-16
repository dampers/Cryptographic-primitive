#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"

int main()
{
	mpz_t a, b, c;
	mpz_init_set_str(a, "-11111111222222223333333344444444", 16);

	return 0;
}



/*
#include "KISA_SHA256.h"

int main(void)
{
	BYTE message[5] = {0x01, 0x02, 0x03, 0x04, 0x05};
	BYTE digest1[SHA256_DIGEST_VALUELEN] = { 0, };
	BYTE digest2[SHA256_DIGEST_VALUELEN] = { 0, };
	SHA256_INFO info;

	unsigned int message_len = 5;

	SHA256_Encrpyt(message, message_len, digest1);
	SHA256_Init(&info);
	SHA256_Process(&info, message, message_len);
	SHA256_Close(&info, digest2);


	for (int i = 0; i < SHA256_DIGEST_VALUELEN; i++)
		printf("%02x", digest1[i]);
	printf("\n");

	for (int i = 0; i < SHA256_DIGEST_VALUELEN; i++)
		printf("%02x", digest2[i]);
	printf("\n");

	return 0;
}

*/