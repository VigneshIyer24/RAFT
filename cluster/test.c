#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int main()
{
	srand(time(0));
	double timeout=150;
	timeout += rand() % 300;
	printf("%f\n",timeout);
	return 0;
}
