#include<stdio.h>
#include<stdlib.h>
#include<fcntl.h>

void main()
{
	FILE *fd;
	//fd = open("/home/dmjoshy/mydisk/hmm/a", "w");
	fd = open("/home/dmjoshy/mydisk/hmm/a",O_WRONLY|O_CREAT);
	//fprintf(fd, "Some meaningless data\n");
	//fd = open("/home/dmjoshy/mydisk/hmm/LOL", O_WRONLY|O_CREAT);
	close(fd);
}