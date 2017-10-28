#include <stdio.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/stat.h>
#include <fcntl.h>

int main() {
	char filename1[15], filename2[15], string[] = "abcdefghij", ch;
	int x;
	FILE *fp1, *fp2;

	/* Writing to file */
	printf("Enter the filename\n");
	scanf("%s", filename1);
	fp1 = fopen(filename1, "w+");
	if (fp1 == NULL) {
		printf("An error was encountered while accessing file!\n");
		return -1;
	}

	fseek(fp1, 10, SEEK_CUR);
	fwrite(string, 1, 10, fp1);

	fseek(fp1, 10, SEEK_CUR);
	fwrite(string, 1, 10, fp1);

	fclose(fp1);

	/* Copying file contents to other file */
	printf("Enter the file to copy to\n");
	scanf("%s", filename2);
	fp1 = fopen(filename1, "r");
	fp2 = fopen(filename2, "w+");
	if (fp1 == NULL || fp2 == NULL) {
		printf("An error was encountered while accessing file!\n");
		return -1;
	}

	x = fread(&ch, 1, 1, fp1);
	while(x != 0) {
		if(ch != '\0')
			fwrite(&ch, 1, 1, fp2);
		x = fread(&ch, 1, 1, fp1);
	}

	printf("\nOperation successful!\n");

	fclose(fp1);
	fclose(fp2);

	return 0;
}