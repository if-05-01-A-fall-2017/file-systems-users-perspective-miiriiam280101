#include <sys/stat.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <string.h>
#include <errno.h>
#include <fcntl.h>

#define MAX_BUFFER 255

int main(int argc, char const *argv[]) {
  const char* firstFile = argv[1];
  const char* secondFile = argv[2];

  int fd = open(firstFile,O_RDONLY);
  int fd2 = open(secondFile,O_RDWR);
	if(fd2 < 0){
		fd2 = creat(argv[2], S_IRUSR| S_IWUSR | S_IRGRP | S_IROTH);
		int fd2 = open(secondFile,O_RDWR);
	}

 	char buf[MAX_BUFFER];
  ssize_t bytes_r;
	do
	{
		bytes_r = read(fd,buf,MAX_BUFFER);
  	write(fd2,buf, bytes_r * sizeof(char));
	}
	while(bytes_r == MAX_BUFFER);

  int s = close(fd);
  int s2 = close(fd2);

  return 0;

}
