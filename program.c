#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main (int argc, char *argv[])
{
int fd[2];
pipe(fd);
int pid;

void *ptr = malloc(sizeof(char));

FILE *plik = fopen(argv[1],"r");
if(plik != NULL)
{
if((pid = fork()) == 0) //Dziecko
{
	close(0);
	dup(fd[0]);
	close(fd[1]);
	execlp("display","display",(char*)NULL);
		
}
else //Rodzic
{
	dup(fd[1]);
	close(fd[0]);
	while (!feof(plik))
	{
		fscanf(plik,"%c",ptr);
		write(fd[1],ptr,sizeof(char));
	}
	fclose(plik);
}
}
else
	printf("Nie ma takiego pliku!!!\n");
return 0;
}
