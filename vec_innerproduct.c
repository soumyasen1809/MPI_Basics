#include<stdio.h>
#include<mpi.h>

int main(){
	int arr_size = 1024;
	int a[arr_size];
	int b[arr_size];
	int c[arr_size];
	int temp[arr_size];

	int size, rank;
	int local_size;


	/*Filling up arrays a and b*/
	for(int i = 0; i < arr_size; i++){
		a[i] = 10;
		b[i] = 20;
		c[i] = 0;
		temp[i] = 0;
	}

	MPI_Init(NULL, NULL);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	MPI_Comm_size(MPI_COMM_WORLD, &size);

	local_size = arr_size/size;
	int local_a[local_size], local_b[local_size], local_c[local_size];
	for(int i = 0; i < local_size; i++){
		local_a[i] = a[i + (rank*local_size)];
		// printf("local a[i] is %d\n",local_a[i]);
		local_b[i] = b[i + (rank*local_size)];
		// printf("local b[i] is %d\n",local_b[i]);
		local_c[i] = local_a[i] * local_b[i];
		// printf("local c[i] is %d\n", local_c[i]);
	}

	if(rank != 0){
		printf("Sending from rank %d: \n", rank);
		MPI_Send(local_c, local_size, MPI_INT, 0, 0, MPI_COMM_WORLD);
	}
	else{
		for(int i = 0; i < local_size; i++){
			c[i] = local_c[i];
			// printf("c[i] for rank 0 is %d\n", c[i]);
		}
		printf("Receiving into rank %d: \n", rank);
		for(int i = 1; i < size; i++){
			MPI_Recv(local_c, local_size, MPI_INT, i, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);
			for(int j = 0; j < local_size; j++){
				c[j + (i*local_size)] = local_c[j];
				// printf("For j = %d, rank i = %d, size = %d, Wrting in %d\n", j, i, local_size, j + (i*local_size));
				// printf("c[i] for rank others is %d\n", c[j+(i*local_size)]);
			}
		}
	}

	MPI_Reduce(c, temp, arr_size, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
	/*printf("Reduced value is: %d\n", temp[0]);*/


	if(rank == 0){
		// for(int i = 0; i < arr_size; i++){printf("%d \t", c[i]);}
		printf("Reduced value is: %d\n", temp[0]);
	}


	MPI_Finalize();

	return 0;
}
