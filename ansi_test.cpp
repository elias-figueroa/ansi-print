#include <stdio.h>
#include "ansi_print.hpp"


#define ANSI_ESCAPE "\033[%dm"


void show_ansi () {

	int i;
	char tmpBuf[20];

	for (i=0 ; i<256 ; ++i) {

		sprintf (tmpBuf, ANSI_ESCAPE, i);
		printf ("%02d: %sThe text is here\033[0m\n", i, tmpBuf);

	}
}




int main (int argc, char ** argv) {

	printf ("Test: \n");
	printf ("----------------------------------------\n");
	aprintf ("This is <red: sample text   > to the rescue!\n");
	printf ("----------------------------------------\n");

	return 0;
}