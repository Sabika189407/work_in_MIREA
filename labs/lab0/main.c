#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "check.h"
#include "calc.h"


int main(int argc, char** argv)
{
	if (check_imput(&argc, argv) == 0)
	{
		calc(&argc, argv);
	}
	return 0;
}
