// https://diveintosystems.org/book/C2-C_depth/advanced_assembly.html
#include <stdio.h>

int main(void)
{
	unsigned int x, y;
	x = 1;
	x = x + 2;
	x = x - 14;
	y = x * 100;
	x = x + y * 6;

	printf("Hello %d\n", x);

	return 0;

}

