#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
	if (argc != 3) {
		printf("Invalid number of arguments\n");
		exit(-1);
	}

	// Open files
	FILE *fpin = fopen(argv[1], "r");
	FILE *fpout = fopen(argv[2], "w+"); 	// create if it doesn't already exist
	if ((fpin == NULL) || (fpout == NULL)) {
		printf("Error in opening file\n");
		exit(-1);
	}

	// Copy contents
	int c;
	do {
      c = fgetc(fpin);
      if (feof(fpin))
      	break;
      fputc(c, fpout);
   } while(1);

   fclose(fpin);
   fclose(fpout);

	return 0;
}
