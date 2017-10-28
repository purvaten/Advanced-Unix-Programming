#include <stdio.h>
#include <string.h>

int truncate (const char *path, off_t len) {
	/* Return 0 on success. Return -1 on error */
	FILE *fp1, *fp2;
	char ch, filename[] = "temp.txt";
	int i;

	fp1 = fopen(path, "r");
	fp2 = fopen(filename, "w+");
	if (fp1 == NULL || fp2 == NULL) {
		printf("An error was encountered while accessing file!\n");
		return -1;
	}

	ch = fgetc(fp1);
	while (ch != EOF) {
		i++;
		if (i > len)
			break;
		fputc(ch, fp2);
		ch = fgetc(fp1);
	}

	fclose(fp1);
	fclose(fp2);

	fp1 = fopen(path, "w+");
	fp2 = fopen(filename, "r");

	ch = fgetc(fp2);
	while(ch != EOF) {
		fputc(ch, fp1);
		ch = fgetc(fp2);
	}

	fclose(fp1);
	fclose(fp2);
	remove(filename);

	return 0;
}

int main() {
	char filename[15], path[100];
	int x;

	printf("\nEnter the directory of the file (eg./home/test/)\n");
	scanf("%s", path);
	printf("\nEnter the name of the file in above directory (eg.filename.txt)\n");
	scanf("%s", filename);
	strcat(path, filename);

	x = truncate(path, 7);

	if (x == 0)
		printf("\nOperation successful!\n");
	else
		printf("\nOops! Error encountered in truncate operation!\n");

	return 0;
}
