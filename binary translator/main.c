#include <iostream>
#include <cstring>
#include <stdlib.h>
#include "translator.h"

int main ()
{
	translator translator;
	translator.make_input();
    std::cout << "huuuuui111111\n";
	translator.translate ();
    std::cout << "huuu222222\n";
	translator.make_output ();
    std::cout << "huuu3333\n";
	system ("chmod 777 ./exit");
	return 0;
}
