#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <ctype.h>

int main(int argc, char **argv) {
	int writefd, readfd, n, d, ret_val, count;
 	char buf[50];
 	ret_val = mkfifo("f1",0666);
 	ret_val = mkfifo("f2",0666);
 	readfd = open("f1",O_RDONLY);
	writefd = open("f2",O_WRONLY);
 	n=read(readfd,buf,50);
 	buf[n]='\0';
 	printf("Full duplex server:read from the pipe: %s\n",buf);
 	count=0;
 	while(count<n) {
 		buf[count]=toupper(buf[count]);
 		count++;
 	}
 	write(writefd,buf,strlen(buf));	
	return 0;
}
