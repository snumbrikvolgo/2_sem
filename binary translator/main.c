#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "translator.h"
#include <time.h>
int main ()
{
	translator translator;
	translator.make_input();
	translator.translate ();
	translator.make_output ();
	system ("chmod 777 ./exit");
	clock_t   t = clock();
	//for (int i = 0; i <1000; i++)
	system ("./exit");
	printf("%ld time for binary", clock() - t);
	return 0;
}
