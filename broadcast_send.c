#include<stdio.h>
#include<string.h>
#include<mpi.h>

int main(void){

	int MAX_STRING = 10;
	char greetings[MAX_STRING];
	int size, rank;

	MPI_Init(NULL, NULL);

	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	if(rank != 0){
		printf("Rank is %d  (should not be 0)\n", rank);
		MPI_Send(greetings, MAX_STRING, MPI_CHAR, 0, 0, MPI_COMM_WORLD);
	}
	else{
		printf("Rank is %d (should be 0)\n", rank);
		for(int id = 1; id < size; id++){
			printf("Receiver in loop is %d \n", id);
			MPI_Recv(greetings, MAX_STRING, MPI_CHAR, id, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			printf("%s\n", greetings);
		}
	}



	MPI_Finalize();

	return 0;
}
