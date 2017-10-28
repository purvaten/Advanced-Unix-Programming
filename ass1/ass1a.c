#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
	FILE *fp;
	char filename[15], ch, hello[5];
	int i = 0;

	printf("Enter the name of the file\n");
	scanf("%s", filename);
	fp = fopen(filename, "r+");
	if (fp == NULL) {
		printf("An error was encountered while accessing file!\n");
		return 1;
	}

	/* Reading */
	ch = fgetc(fp);
	while(ch != EOF) {
		i++;
		if (i <= 10)
			printf("%c", ch);
		ch = fgetc(fp);
	}
	printf("\n");

	/* Writing */
	strcpy(hello, "hello");
	for (i = 0; i < 5; i++)
		fputc(hello[i], fp);

	fclose(fp);

	return 0;
}