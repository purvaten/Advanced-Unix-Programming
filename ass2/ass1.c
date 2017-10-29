#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <dirent.h>
#include <time.h>
#include <pwd.h>
#include <grp.h>

void lsminusl(char *temp, char *filename) {
	int sz;
	char date[20], timet[20];
	struct stat fileStat;
	struct passwd *pw;
	struct group *gr;

	if(stat(temp, &fileStat) < 0)
        	return;

	/* File permissions */
    printf( (S_ISDIR(fileStat.st_mode)) ? "d" : "-");
    printf( (fileStat.st_mode & S_IRUSR) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWUSR) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXUSR) ? "x" : "-");
    printf( (fileStat.st_mode & S_IRGRP) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWGRP) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXGRP) ? "x" : "-");
    printf( (fileStat.st_mode & S_IROTH) ? "r" : "-");
    printf( (fileStat.st_mode & S_IWOTH) ? "w" : "-");
    printf( (fileStat.st_mode & S_IXOTH) ? "x" : "-");
    printf(" ");

    /* Number of links/directories */
	printf("%d ", (int)fileStat.st_nlink);

	/* user */
	pw = getpwuid(fileStat.st_uid);
	printf("%s ", pw->pw_name);

	/* group */
	gr = getgrgid(fileStat.st_gid);
	printf("%s ", gr->gr_name);

	/* size in bytes */
	sz = fileStat.st_size;
	printf("%d ", sz);

	/* date */
	strftime(date, 20, "%b %d", localtime(&(fileStat.st_ctime)));
	printf("%s ", date);

	/* time */
	strftime(timet, 20, "%H:%M", localtime(&(fileStat.st_ctime)));
	printf("%s ", timet);

	/* name of file */
	printf("%s\n", filename);
}

int main(int argc, char* argv[]) {
	struct stat st = {0};
	int statchmod, i;
	FILE *fp;
	char filename[2], str[] = "Hello", directory[100], temp[100];
	DIR *dir;
	struct dirent *ent;

	if (argc != 2) {
		printf("Invalid numner of arguments\n");
		return -1;
	}

	strcpy(directory, argv[1]);
	strcat(directory, "/junk");

	/* mkdir junk */
	if (stat(directory, &st) == -1)
	    mkdir(directory, 0700);

	/* for loop */
	for (i = 1; i <= 5; i++) {
		sprintf(filename,"%d", i);
		strcpy(temp, directory);
		strcat(temp, "/");
		strcat(temp, filename);
		fp = fopen(temp, "w+");
		fprintf(fp, "%s", str);
		fclose(fp);
	}

	/* ls -l junk */
	for (i = 1; i <= 5; i++) {
		sprintf(filename,"%d", i);
		strcpy(temp, directory);
		strcat(temp, "/");
		strcat(temp, filename);
		lsminusl(temp, filename);
    }
    printf("\n");

	stat(directory, &st);
	statchmod = st.st_mode & (S_IRWXU | S_IRWXG | S_IRWXO);

    /* chmod -r junk : reset first bit */
    statchmod = statchmod & 0377;
    chmod(directory, statchmod);

	/* ls -l */
	if ((dir = opendir (argv[1])) != NULL) {
		while ((ent = readdir (dir)) != NULL) {
			if ((strcmp(ent->d_name, ".") == 0) || (strcmp(ent->d_name, "..") == 0))
				continue;
			strcpy(temp, argv[1]);
			strcat(temp, "/");
			strcat(temp, ent->d_name);
			lsminusl(temp, ent->d_name);
		}
		closedir (dir);
	}
	else {
	  /* could not open directory */
	  perror ("");
	  return EXIT_FAILURE;
	}
	printf("\n");

	/* chmod +r junk : set first bit */
    statchmod = statchmod | 0400;
    chmod(directory, statchmod);

	/* ls -l junk */
	for (i = 1; i <= 5; i++) {

		sprintf(filename,"%d", i);
		strcpy(temp, directory);
		strcat(temp, "/");
		strcat(temp, filename);

		lsminusl(temp, filename);
    }
    printf("\n");

    /* chmod -x junk */
    statchmod = statchmod & 0677;
    chmod(directory, statchmod);

    /* cd junk */
	i = chdir(directory);
	if (i == -1)
		printf("\nbash: cd: junk: Permission denied\n");

    /* chmod +x junk */
    statchmod = statchmod | 0100;
    chmod(directory, statchmod);

	/* cd junk */
	i = chdir(directory);
	if (i == -1) {
		printf("\nbash: cd: junk: Permission denied\n");
		return -1;
	}

	/* changed working directory to junk */

	return 0;
}