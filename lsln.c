#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>
#include <dirent.h>

struct stat attributes;

void printFT(mode_t mode);
void printPrivileges();
void print(char* name);

int main(int argc, char const *argv[]) {
	DIR *d;
	struct dirent *dir;
	d = opendir(".");
	if (d) {
		while ((dir = readdir(d)) != NULL) {
			if(dir->d_name[0] != '.'){
				print(dir->d_name);
			}
		}
	closedir(d);
	}
	return 0;
}

void printFT(mode_t mode) {
	if(S_ISBLK(mode) != 0)
		printf("b");
	else if(S_ISCHR(mode) != 0)
		printf("c");
	else if(S_ISDIR(mode) != 0)
		printf("d");
	else if(S_ISFIFO(mode) != 0)
		printf("f");
	else if(S_ISLNK(mode) != 0)
		printf("Symbolic link\n");
	else if(S_ISREG(mode) != 0)
		printf("-" );
	else if(S_ISSOCK(mode) != 0)
		printf("s" );
}

void printPrivileges() {
	printf( (S_ISDIR(attributes.st_mode)) ? "d" : "-");
	printf( (attributes.st_mode & S_IRUSR) ? "r" : "-");
	printf( (attributes.st_mode & S_IWUSR) ? "w" : "-");
	printf( (attributes.st_mode & S_IXUSR) ? "x" : "-");
	printf( (attributes.st_mode & S_IRGRP) ? "r" : "-");
	printf( (attributes.st_mode & S_IWGRP) ? "w" : "-");
	printf( (attributes.st_mode & S_IXGRP) ? "x" : "-");
	printf( (attributes.st_mode & S_IROTH) ? "r" : "-");
	printf( (attributes.st_mode & S_IWOTH) ? "w" : "-");
	printf( (attributes.st_mode & S_IXOTH) ? "x" : "-");
}

void print(char* name) {
	lstat(name, &attributes);
	printFT(attributes.st_mode);
	printf("\t");
	printPrivileges();
	printf("%5d%5d %9d",attributes.st_uid ,attributes.st_gid, attributes.st_size);
	struct tm * tmp;
	tmp = gmtime(&attributes.st_atim);
	printf("%6d-%2d-%2d-%2d-%2d ", (1990 + tmp->tv_year) , tmp->tv_mon + 1 , tmp->tv_mday, tmp->tv_hour + 1,tmp->tv_min + 1);
	printf("%s\n",name );
}


