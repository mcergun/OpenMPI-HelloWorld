#include <stdio.h>
#include <string.h>
#include <mpi.h>

#define MAX_STRING 100

int main(int argc, char *argv[]) 
{
	char greeting[MAX_STRING];
	int comm_size;
	int comm_rank;

	MPI_Init(NULL, NULL);
	MPI_Comm_size(MPI_COMM_WORLD, &comm_size);
	MPI_Comm_rank(MPI_COMM_WORLD, &comm_rank);

	if(comm_rank != 0) {
		sprintf(greeting, "Greetings from process %d of %d",
			comm_rank, comm_size);
		MPI_Send(greeting, strlen(greeting) + 1, MPI_CHAR,
			0, 0, MPI_COMM_WORLD);
	} else {
		printf("Greetings from process %d of %d\n", comm_rank,
			comm_size);
		for(int i = 0; i < comm_size; i++) {
			printf("Receiving for %d\n", i);
			MPI_Recv(greeting, MAX_STRING, MPI_CHAR, i, 0,
				MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greeting);
		}
	}

	MPI_Finalize();
	return 0;
}

