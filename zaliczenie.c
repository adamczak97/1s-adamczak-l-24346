#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <stdlib.h>
int main(int argc, char *argv[])
{
	if (argc != 2)
	{
		printf("\nPass command line argument as your filename.\n");
		return 1;
	}
	// tworzymy zmienną procesu dziecko
	pid_t pid;
	// przypisujemy do zmiennej nowy proces dziecko
	pid = fork();
	// jeśli pid == 0 to jest to proces dziecko
	if (pid == 0)
	{
		// tworzymy bufor pliku
		FILE *stream;
		// tworzymy zmienną iteracyjną
		int i;
		// otwieramy plik
		stream = fopen(argv[1], "w");
		
		// sprawdzamy czy plik się otworzył prawidłowo, jeśli nie - zamyka program
		if (!stream)
		{
			printf("\nError while opening file\n");
			return 1;	
		}
		else
		{
			for ( i = 1; i <= 50; i++)
			{	
				if(i % 3 == 0)
					fprintf(stream, "%d\n", i);
			}
			fclose(stream);
		}
	}
	// jeśli pid != 0 to jest to proces rodzica
	if (pid != 0)
	{	
		// czekamy aż proces dziecka zakończy się i odeśle sygnał do rodzica
		int *wstatus;
		wait(wstatus);
		
		// pokazujemy PID rodzica
		printf("\nPARENT PID: %d", getpid());
		// PID child processu
		printf("\nCHILD PID: %d", pid);

		// informacje że program się zakończył razem z informacją o kodzie
		printf("\nChild process ended with code ");
		printf("%d\n", WIFEXITED(*wstatus));
	}
	
	int fd = open(argv[1], O_RDONLY);
	// sprawdzamy rozmiar pliku, SEEK_END i 0 gwanantują nam że będzie na końcu pliku
	int size = lseek(fd, 0, SEEK_END);

	//rozmiar
	printf("\nSize of the file is ");
	printf("%d\n", size);

	close(fd);
	
	return 0;
}