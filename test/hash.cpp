#include <stdio.h>

unsigned long djb2(unsigned char *str)
{
	unsigned long hash = 5381;
	int c;
	while (c = *str++)
	{
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}

unsigned long sdbm(unsigned char *str)
{
	unsigned long hash = 0;
	int c;

	while (c = *str++)
	{
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}

unsigned long hash_i(unsigned char *str, unsigned int i)
{
	return djb2(str) + i * sdbm(str) + i * i;
}

/* 
main to test
*/
int main(int argc, char **argv)
{
	char *s = "Hello World!";
	int i = 0;
	int K = 10;

	printf("djb2   (%s) : %lu \n", s, djb2(s));
	printf("sdbm2  (%s) : %lu \n", s, sdbm(s));

	for (i = 0; i < K; i++)
	{
		printf("hash_%d (%s) : %lu \n", i, s, hash_i(s, i));
	}
}
