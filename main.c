#include "msgf.h"
#include <stdio.h>
#include <string.h>

int
main(void)
{
	int i;
	int len;
	unsigned char buf[10];

	char a1;
	unsigned char a2;
	short a3;
	unsigned short a4;
	unsigned int a5;

	len = msgf_dump(buf, ">bBhHI", -1, 255, 3, 4, 5);
	len = msgf_load(buf, ">bBhHI", &a1, &a2, &a3, &a4, &a5);

	printf("%d, %d, %d, %d, %d\n", a1, a2, a3, a4, a5);

	for (i = 0; i < sizeof(buf); i++) {
		printf("%02hhx", buf[i]);
	}
	printf("\n");

	return 0;
}
