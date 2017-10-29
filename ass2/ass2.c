#include <stdio.h>
#include <dirent.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <limits.h>
#include <stdlib.h>

int main (int argc, char * argv[]) {
	struct dirent *dp;
	DIR *dfd;
	char *dir;
	char filename_qfd[100];

	if (argc == 2) {
		dir = argv[1] ;
	}
	else
		dir = ".";

	if ((dfd = opendir(dir)) == NULL) {
  		fprintf(stderr, "Can't open the directory%s\n", dir);
  		return 0;
 	}

	while ((dp = readdir(dfd)) != NULL) {
		struct stat stbuf ;
		sprintf( filename_qfd , "%s/%s",dir,dp->d_name) ;
		if( lstat(filename_qfd,&stbuf ) == -1 ) {
			printf("Unable to stat file: %s\n",filename_qfd) ;
			continue ;
		}
		if ( ( stbuf.st_mode & S_IFMT ) == S_IFDIR ) {
			printf("DIR : %s\n",filename_qfd) ;
		}
		else {
			if ( ( stbuf.st_mode & S_IFMT ) == S_IFLNK ) {
				printf("LINK : %s\n",filename_qfd);
				char rp[PATH_MAX+1];
				realpath(filename_qfd,rp);
				printf("\tREAL PATH : %s\n",rp);
			}
			else
				printf("FILE : %s\n",filename_qfd) ;
		}
	}

	return 0;
}
