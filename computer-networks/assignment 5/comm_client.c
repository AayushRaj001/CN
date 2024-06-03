#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>
#include <string.h>
#include <fcntl.h>


int main(int argc, char **argv) {
	
	int readfd, writefd, n; 
	char buff[50], line[50];  
	writefd = open("f1", O_WRONLY); 
	readfd = open("f2", O_RDONLY); 
	printf("Enter the line of text: ");
    gets(line); 
	write(writefd, line, strlen(line)); 
	n = read(readfd, buff, 50); 
	buff[n] = '\n'; 
	printf("Full duplex client: read from the pipe: %s\n", buff); 	

	return 0; 
}
