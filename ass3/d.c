#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>

int main(int argc, char *argv[]) {
	if (argc != 2) {
		printf("Invalid number of arguments\n");
		return 1;
	}

	struct stat st;
	stat(argv[1], &st);

	// display device number
	printf("Device number:  major = %ld   minor = %ld\n", (long)major(st.st_dev), (long)minor(st.st_dev));

	// check if character/block file and display resp major and minor numbers
	if (S_ISCHR(st.st_mode) || S_ISBLK(st.st_mode))
		printf("Special Device number:  major = %ld   minor = %ld\n",
			(long) major(st.st_rdev), (long) minor(st.st_rdev));

	return 0;
}